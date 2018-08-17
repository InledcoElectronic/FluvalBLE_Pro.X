#include "app_ble.h"
#include "app_led.h"
#include "drv_eusart.h"
#include "app_rtc.h"

#define BLE_RST             LATBbits.LATB5
#define BLE_WKP             LATCbits.LATC1
#define BLE_INT             PORTAbits.RA2

#define BLE_CMD_SLAVE       "AT+SET=1\r\n"
#define BLE_CMD_DATA        "AT+MODE=DATA\r\n" 
#define BLE_CMD_GET_ADV     "AT+ADV_MFR_SPC=?\r\n" 
#define BLE_CMD_SET_ADV     "AT+ADV_MFR_SPC=" DEVICE_ID_VERSION "\r\n" 
#define BLE_RESP_OK			"AT+OK\r\n"

#define END_FLASH           8192

#define FRM_HDR             0x68
#define CMD_DATA_MODE       0x02
#define CMD_DATA_ONOFF      0x03
#define CMD_DATA_CTRL       0x04
#define CMD_DATA_READ       0x05
#define CMD_DATA_CUSTOM     0x06
#define CMD_DATA_CYCLE      0x07
#define CMD_DATA_INCREASE   0x08
#define CMD_DATA_DECREASE   0x09
#define CMD_DATA_DYN        0x0A
#define CMD_DATA_PREVIEW    0x0B
#define CMD_DATA_STOPPREV   0x0C
#define CMD_DATA_SYNCTIME   0x0E
#define CMD_DATA_FIND       0x0F
#define CMD_DATA_PRO		0x10
#define CMD_DATA_PERIOD_DYN	0x11
#define CMD_OTA_RESET       0x00

#define RX_BUF_SIZE			80

static uint8_t rx_buf[RX_BUF_SIZE];
static uint8_t index;
static uint8_t checksum;

static void ble_decode();

static bool ble_send_cmd(const char *cmd)
{
	char ack[] = BLE_RESP_OK;
	uint8_t len = strlen(ack);
	uint8_t idx = 0;
	uint8_t cnt = 0;
	uint8_t rev = RCREG;
	while(*cmd != '\0')
	{
		eusart_write(*cmd++);
	}

	while(idx < len)
	{
		if(PIR1bits.RCIF)
		{
			if(RCSTAbits.OERR)
			{
				RCSTAbits.CREN = 0;
				RCSTAbits.CREN = 1;
			}
			rev = RCREG;
			if(rev == ack[idx])
			{
				idx++;
			}
			else
			{
				idx = 0;
			}
		}
		__delay_us(250);
		cnt++;
		if(cnt > 250)
		{
			return false;
		}
	}
	return true;
}

static bool ble_check_devid()
{
	char dev[] = DEVICE_ID_VERSION;
	uint8_t len = strlen(dev);
	uint8_t idx = 0;
	uint16_t cnt = 0;
	uint8_t rev;
	ble_send_cmd(BLE_CMD_GET_ADV);
	while(idx < len)
	{
		if(PIR1bits.RCIF)
		{
			if(RC1STAbits.OERR)
			{
				RC1STAbits.CREN = 0;
				RC1STAbits.CREN = 1;
			}
			rev = RCREG;
			if(rev == dev[idx])
			{
				idx++;
			}
			else
			{
				return false;
			}
		}
		__delay_us(100);
		cnt++;
		if(cnt > 1000)
		{
			return false;
		}
	}
	return true;
}

static void ble_transmit_start()
{
	BLE_WKP = 0;
	__delay_us(800);
}

static void ble_transmit_stop()
{
	while(!TXSTAbits.TRMT);
	__delay_us(200);
	BLE_WKP = 1;
}

bool ble_ready_to_receive()
{
	if((BLE_INT == 0) && BLE_WKP)
	{
		return true;
	}
	return false;
}

void ble_receive_start()
{
	index = 0;
	checksum = 0;
	__delay_us(800);
	BLE_WKP = 0;
}

bool ble_receive_complete()
{
	if(BLE_INT && (BLE_WKP == 0))
	{
		return true;
	}
	return false;
}

void ble_receive_stop()
{
	__delay_us(100);
	BLE_WKP = 1;
}

void ble_process()
{
	if(ble_ready_to_receive())
	{
		ble_receive_start();
	}
	if(ble_receive_complete())
	{
		ble_receive_stop();
		ble_decode();
	}
}

void ble_init()
{
	BLE_WKP = 0;
	BLE_RST = 0;
	__delay_ms(20);
	BLE_RST = 1; //release from reset
	__delay_ms(240); //delay 200ms after power on

	//检查设备id version是否写入蓝牙模块广播数据
	if(ble_check_devid() == false)
	{
		__delay_ms(40);
		ble_send_cmd(BLE_CMD_SET_ADV);
	}
	__delay_ms(40);
	//设置ble从机模式
	ble_send_cmd(BLE_CMD_SLAVE);
	__delay_ms(40);
	//设置ble透传模式
	ble_send_cmd(BLE_CMD_DATA);
	__delay_ms(40);
	BLE_WKP = 1;
}

static void ble_send_data()
{
	uint8_t i;
	uint8_t len;
	uint8_t xor = 0;
	ble_para_t *p = &m_led_para.ble_para;
	ble_transmit_start();
	xor ^= eusart_write(FRM_HDR);
	xor ^= eusart_write(CMD_DATA_READ);
	xor ^= eusart_write(p->mMode);
	if(p->mMode == BLE_MODE_AUTO)
	{
		len = sizeof(p->auto_para.array);
		for(i = 0; i < len; i++)
		{
			xor ^= eusart_write(p->auto_para.array[i]);
		}
#ifdef	DYNAMIC_ENABLE
		for(i = 0; i < sizeof(p->dynamic_para.array); i++)
		{
			xor ^= eusart_write(p->dynamic_para.array[i]);
		}
#endif
	}
	else if(p->mMode == BLE_MODE_PRO)
	{
		if(p->pro_para.point_count < POINT_COUNT_MIN)
		{
			p->pro_para.point_count = POINT_COUNT_MIN;
		}
		else if(p->pro_para.point_count > POINT_COUNT_MAX)
		{
			p->pro_para.point_count = POINT_COUNT_MAX;
		}
		len = p->pro_para.point_count*(2+CHANNEL_COUNT)+1;
		for(i = 0; i < len; i++)
		{
			xor ^= eusart_write(p->pro_para.array[i]);
		}
#ifdef	DYNAMIC_ENABLE
		for(i = 0; i < sizeof(p->dynamic_para.array); i++)
		{
			xor ^= eusart_write(p->dynamic_para.array[i]);
		}
#endif
	}
	else
	{
		len = sizeof(p->manual_para.array);
		for(i = 0; i < len; i++)
		{
			xor ^= eusart_write(p->manual_para.array[i]);
		}
	}
	eusart_write(xor);
	ble_transmit_stop();
}

static void ble_ota_ack()
{
	ble_transmit_start();
	eusart_write(0x68);
	eusart_write(0x00);
	eusart_write(0x00);
	eusart_write(0x00);
	eusart_write(0x68);
	ble_transmit_stop();
}

void ble_receive(uint8_t rcv)
{
	rx_buf[index++] = rcv;
	checksum ^= rcv;
	if(index >= sizeof(rx_buf))
	{
		index = 0;
		checksum = 0;
	}
}

static void ble_decode()
{
	if(rx_buf[0] != FRM_HDR || checksum != 0)
	{
//		index = 0;
//		checksum = 0;
		return;
	}
	switch(rx_buf[1])
	{
		case CMD_DATA_MODE:
			if(index == 4)
			{
				if(led_set_mode(rx_buf[2]))
				{
					ble_send_data();
				}
			}
			break;
		case CMD_DATA_ONOFF:
			if(index == 4)
			{
				if(led_set_power(rx_buf[2]))
				{
					ble_send_data();
				}
			}
			break;
		case CMD_DATA_CTRL:
			if(index == 3 + 2 * CHANNEL_COUNT)
			{
				led_set_bright(&rx_buf[2]);
			}
			break;
		case CMD_DATA_READ:
			if(index == 3)
			{
				ble_send_data();
			}
			break;
		case CMD_DATA_CUSTOM:
			if(index == 4)
			{
				if(led_set_custom(rx_buf[2]))
				{
					ble_send_data();
				}
			}
			break;
		case CMD_DATA_CYCLE:
			if(index == 2 * CHANNEL_COUNT + 14)
			{
				if(led_set_cycle(&rx_buf[2]))
				{
					ble_send_data();
				}
			}
			break;
		case CMD_DATA_INCREASE:
			if(index == 5)
			{
				led_increase(rx_buf[2], rx_buf[3]);
			}
			break;
		case CMD_DATA_DECREASE:
			if(index == 5)
			{
				led_decrease(rx_buf[2], rx_buf[3]);
			}
			break;
		case CMD_DATA_PREVIEW:
			if(index == 3 + 2 * CHANNEL_COUNT)
			{
				if(led_set_preview(&rx_buf[2]))
				{
					led_start_preview();
				}
			}
			break;
		case CMD_DATA_STOPPREV:
			if(index == 3)
			{
				led_stop_preview();
			}
			break;
		case CMD_DATA_SYNCTIME:
			if(index == 10)
			{
				led_set_time(&rx_buf[2]);
				ble_send_data();
			}
			break;
		case CMD_DATA_FIND:
			if(index == 3)
			{
				led_start_flash();
			}
			break;
		case CMD_DATA_PRO:
			if(rx_buf[2] >= POINT_COUNT_MIN && rx_buf[2] <= POINT_COUNT_MAX && index == rx_buf[2]*(2+CHANNEL_COUNT)+4)
			{
				if(led_set_pro(&rx_buf[2]))
				{
					ble_send_data();
				}
			}
			break;
#ifdef	DYNAMIC_ENABLE
		case CMD_DATA_DYN:
			if(index == 4)
			{
				if(led_set_dynamic(rx_buf[2]))
				{
					ble_send_data();
				}
			}
			break;
		case CMD_DATA_PERIOD_DYN:
			if(index == 9)
			{
				led_set_period_dynamic(&rx_buf[2]);
				ble_send_data();
			}
			break;
#endif
		case CMD_OTA_RESET:
			if(index == 5)
			{
				INTCONbits.GIE = 0;
				NVMADR = END_FLASH - 1;
				NVMCON1 = 0x94;
				NVMCON2 = 0x55;
				NVMCON2 = 0xAA;
				NVMCON1bits.WR = 1;
				NOP();
				NOP();
				while(NVMCON1bits.WR);
				NVMCON1bits.WREN = 0;
				INTCONbits.GIE = 1;
				ble_ota_ack();
				__delay_ms(96);
				RESET();
			}
			break;
		default:
			break;
	}
//	index = 0;
}