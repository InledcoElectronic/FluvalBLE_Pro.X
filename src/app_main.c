/*
 * File:   app_main.c
 * Author: liruya
 *
 * Created on 2018年7月5日, 下午5:17
 */


#include <xc.h>
#include "app_common.h"
#include "app_board.h"
#include "app_ble.h"
#include "app_led.h"
#ifdef	TOUCH_ENABLE
#include "app_key.h"
#endif
#include "app_rtc.h"
#include "app_util.h"
#include "drv_eusart.h"
#include "drv_tmr.h"
#include "drv_pwm.h"

void osc_init()
{
	// NOSC HFINTOSC; NDIV 1; 
	OSCCON1 = 0x60;
	// CSWHOLD may proceed; SOSCPWR Low power; SOSCBE crystal oscillator; 
	OSCCON3 = 0x00;
	// LFOEN disabled; ADOEN disabled; SOSCEN enabled; EXTOEN disabled; HFOEN enabled; 
	OSCEN = 0x48;
	// HFFRQ 16_MHz; 
	OSCFRQ = 0x06;
	// HFTUN 0; 
	OSCTUNE = 0x00;
	// Set the secondary oscillator 
}

void gpio_init()
{
	/**
	LATx registers
	 */
	LATA = 0x02;
	LATB = 0xD0;
	LATC = 0x00;

	/**
	TRISx registers
	 */
	TRISA = 0x34;
	TRISB = 0x00;
	TRISC = 0x05;

	/**
	ANSELx registers
	 */
	ANSELC = 0x00;
	ANSELB = 0x00;
	ANSELA = 0x00;

	/**
	WPUx registers
	 */
	WPUB = 0x00;
	WPUA = 0x04;
	WPUC = 0x01;

	/**
	ODx registers
	 */
	ODCONA = 0x00;
	ODCONB = 0x00;
	ODCONC = 0x00;

	PPSLOCK = 0x55;
	PPSLOCK = 0xAA;
	PPSLOCKbits.PPSLOCKED = 0x00; // unlock PPS

	RXPPSbits.RXPPS = 0x12; //RC2->EUSART:RX;
	RB4PPSbits.RB4PPS = 0x14; //RB4->EUSART:TX;
	RC5PPSbits.RC5PPS = 0x0C; //RC5->CCP1:CCP1;
	RC4PPSbits.RC4PPS = 0x0D; //RC4->CCP2:CCP2;
	RC3PPSbits.RC3PPS = 0x0E; //RC3->CCP3:CCP3;
	RC6PPSbits.RC6PPS = 0x0F; //RC6->CCP4:CCP4;
	RC7PPSbits.RC7PPS = 0x02; //RC7->PWM5

	PPSLOCK = 0x55;
	PPSLOCK = 0xAA;
	PPSLOCKbits.PPSLOCKED = 0x01; // lock PPS
}

void tmr2_isr_callback()
{
	static uint8_t cnt = 0;
	
	cnt++;
	if((cnt&0x03) == 0)
	{
#ifdef	TOUCH_ENABLE
		if((cnt&0x0F) == 0)
		{
			key_scan();
		}
#endif
		led_process();
	}
}

void app_init()
{
	gpio_init();
	osc_init();
	pwm1_init();
	pwm2_init();
	pwm3_init();
	pwm4_init();
	pwm5_init();
	tmr0_init(rtc_process);
	tmr2_init(tmr2_isr_callback);
	eusart_init(ble_receive);
#ifdef	TOUCH_ENABLE
	key_init(led_touch_cb);
#endif
	
	global_interrupt_enable();
	peripheral_interrupt_enable();
}

void interrupt app_isr()
{
	if(PIE1bits.RCIE && PIR1bits.RCIF)
	{
		eusart_receive_isr();
	}
	else if(PIE0bits.TMR0IE && PIR0bits.TMR0IF)
	{
		tmr0_isr();
	}
	else if(PIE1bits.TMR2IE && PIR1bits.TMR2IF)
	{
		tmr2_isr();
	}
	else if(PIE1bits.TXIE && PIR1bits.TXIF)
	{
		eusart_transmit_isr();
	}
}

void main(void)
{
	app_init();
	ble_init();
	rtc_init();
	led_init();
	eusart_receive_interrupt_enable();
	tmr0_start();
	tmr2_start();
	
	while(1)
	{
		CLRWDT();
		
		ble_process();
		if(rtc_second_ready())
		{
			led_second_cb();
		}
	}
}
