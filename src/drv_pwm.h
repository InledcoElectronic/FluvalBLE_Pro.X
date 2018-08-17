/* 
 * File:   drv_pwm.h
 * Author: liruya
 *
 * Created on 2018年7月3日, 下午4:44
 */

#ifndef DRV_PWM_H
#define	DRV_PWM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"
    
    extern void pwm1_init();
    extern void pwm1_load_duty(uint16_t value);
    
    extern void pwm2_init();
    extern void pwm2_load_duty(uint16_t value);
    
    extern void pwm3_init();
    extern void pwm3_load_duty(uint16_t value);
    
    extern void pwm4_init();
    extern void pwm4_load_duty(uint16_t value);
    
    extern void pwm5_init();
    extern void pwm5_load_duty(uint16_t value);
    
    extern void pwm6_init();
    extern void pwm6_load_duty(uint16_t value);


#ifdef	__cplusplus
}
#endif

#endif	/* DRV_PWM_H */

