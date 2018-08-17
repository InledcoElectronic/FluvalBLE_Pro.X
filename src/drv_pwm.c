#include "drv_pwm.h"

void pwm1_init()
{
	// CCP1MODE PWM; CCP1EN enabled; CCP1FMT right_aligned; 
	CCP1CON = 0x8F;

	// CCPR1H 0; 
	CCPR1H = 0x00;

	// CCPR1L 0; 
	CCPR1L = 0x00;

	// Selecting Timer 2
	CCPTMRSbits.C1TSEL = 0x1;
}

void pwm1_load_duty(uint16_t value)
{
//	value &= 0x03FF;
	CCPR1H = value>>8;
	CCPR1L = value;
}

void pwm2_init()
{
	// CCP1MODE PWM; CCP1EN enabled; CCP1FMT right_aligned; 
	CCP2CON = 0x8F;

	// CCPR1H 0; 
	CCPR2H = 0x00;

	// CCPR1L 0; 
	CCPR2L = 0x00;

	// Selecting Timer 2
	CCPTMRSbits.C2TSEL = 0x1;
}

void pwm2_load_duty(uint16_t value)
{
//	value &= 0x03FF;
	CCPR2H = value >> 8;
	CCPR2L = value;
}

void pwm3_init()
{
	// CCP1MODE PWM; CCP1EN enabled; CCP1FMT right_aligned; 
	CCP3CON = 0x8F;

	// CCPR1H 0; 
	CCPR3H = 0x00;

	// CCPR1L 0; 
	CCPR3L = 0x00;

	// Selecting Timer 2
	CCPTMRSbits.C3TSEL = 0x1;
}

void pwm3_load_duty(uint16_t value)
{
//	value &= 0x03FF;
	CCPR3H = value >> 8;
	CCPR3L = value;
}

void pwm4_init()
{
	// CCP1MODE PWM; CCP1EN enabled; CCP1FMT right_aligned; 
	CCP4CON = 0x8F;

	// CCPR1H 0; 
	CCPR4H = 0x00;

	// CCPR1L 0; 
	CCPR4L = 0x00;

	// Selecting Timer 2
	CCPTMRSbits.C4TSEL = 0x1;
}

void pwm4_load_duty(uint16_t value)
{
//	value &= 0x03FF;
	CCPR4H = value >> 8;
	CCPR4L = value;
}

void pwm5_init()
{
	PWM5DCH = 0;
	PWM5DCL = 0;
	PWMTMRSbits.P5TSEL = 0X01;
	PWM5CON = 0X80;
}

void pwm5_load_duty(uint16_t value)
{
//	value &= 0x03FF;
	PWM5DCH = value >> 2;
	PWM5DCL = value << 6;
}

void pwm6_init()
{
	PWM6DCH = 0;
	PWM6DCL = 0;
	PWMTMRSbits.P6TSEL = 0X01;
	PWM6CON = 0X80;
}

void pwm6_load_duty(uint16_t value)
{
//	value &= 0x03FF;
	PWM6DCH = value >> 2;
	PWM6DCL = value << 6;
}
