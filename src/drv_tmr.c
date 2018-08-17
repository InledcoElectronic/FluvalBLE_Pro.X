#include "drv_tmr.h"

tmr_isr_cb_t tmr0_isr_cb;
tmr_isr_cb_t tmr2_isr_cb;

void tmr0_init(tmr_isr_cb_t cb)
{
	// T0OUTPS 1:1; T0EN disabled; T016BIT 8-bit; 
	T0CON0 = 0x00;

	// T0CS SOSC; T0CKPS 1:128; T0ASYNC not_synchronised; 
	T0CON1 = 0xD7;

	// TMR0H 255; 
	TMR0H = 0xFF;

	// TMR0L 0; 
	TMR0L = 0x00;

	// Clear Interrupt flag before enabling the interrupt
	PIR0bits.TMR0IF = 0;

	// Enabling TMR0 interrupt.
	PIE0bits.TMR0IE = 1;
	
	tmr0_isr_cb = cb;
}

void tmr0_isr()
{
	PIR0bits.TMR0IF = 0;
	if(tmr0_isr_cb != NULL)
	{
		tmr0_isr_cb();
	}
}

void tmr2_init(tmr_isr_cb_t cb)
{
	// T2CKPS 1:1; T2OUTPS 1:16; TMR2ON off; 
	T2CON = 0x78;

	// PR2 249; 
	PR2 = 0xF9;

	// TMR2 0; 
	TMR2 = 0x00;

	// Clearing IF flag before enabling the interrupt.
	PIR1bits.TMR2IF = 0;

	// Enabling TMR2 interrupt.
	PIE1bits.TMR2IE = 1;
	
	tmr2_isr_cb = cb;
}

void tmr2_isr()
{
	PIR1bits.TMR2IF = 0;
	if(tmr2_isr_cb != NULL)
	{
		tmr2_isr_cb();
	}
}
