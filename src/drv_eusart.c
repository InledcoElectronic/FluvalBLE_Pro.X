#include "drv_eusart.h"

#define TX_BUF_SIZE				64

uint8_t tx_tail;
uint8_t tx_remain;
uint8_t tx_head;
uint8_t tx_buf[TX_BUF_SIZE];

eusart_rcv_cb_t eusart_rcv_cb;

void eusart_init(eusart_rcv_cb_t cb)
{
	PIE1bits.RCIE = 0;
	PIE1bits.TXIE = 0;

	BAUD1CON = 0x08;
	RC1STA = 0x90;
	TX1STA = 0x24;
	SP1BRGL = 0xA0;
	SP1BRGH = 0x01;
//	PIE1bits.RCIE = 1;

	tx_tail = 0;
	tx_head = 0;
	tx_remain = sizeof(tx_buf);
	eusart_rcv_cb = cb;
}

uint8_t eusart_write(uint8_t byte)
{
	while(0 == tx_remain);

	if(!PIE1bits.TXIE)
	{
		TXREG = byte;
	}
	else
	{
		PIE1bits.TXIE = 0;
		tx_buf[tx_head++] = byte;
		if(sizeof( tx_buf) <= tx_head)
		{
			tx_head = 0;
		}
		tx_remain--;
	}
	PIE1bits.TXIE = 1;
	return byte;
}

void eusart_transmit_isr()
{
	if(sizeof(tx_buf) > tx_remain)
	{
		TXREG = tx_buf[tx_tail++];
		if(sizeof(tx_buf) <= tx_tail)
		{
			tx_tail = 0;
		}
		tx_remain++;
	}
	else
	{
		PIE1bits.TXIE = 0;
	}
}

void eusart_receive_isr()
{
	if(RC1STAbits.FERR || RC1STAbits.OERR)
	{
		RC1STAbits.SPEN = 0;
		RC1STAbits.SPEN = 1;
	}
	uint8_t rcv = RCREG;
	if(eusart_rcv_cb != NULL)
	{
		eusart_rcv_cb(rcv);
	}
}