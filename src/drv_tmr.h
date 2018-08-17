/* 
 * File:   tmr.h
 * Author: liruya
 *
 * Created on 2018年7月3日, 下午3:24
 */

#ifndef TMR_H
#define	TMR_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"
    
#define tmr0_start()                (T0CON0bits.T0EN = 1)
#define tmr0_stop()                 (T0CON0bits.T0EN = 0)
#define tmr0_interrupt_enable()     (PIE0bits.TMR0IE = 1)
#define tmr0_interrupt_disable()    (PIE0bits.TMR0IE = 0)
    
#define tmr2_start()                (T2CONbits.TMR2ON = 1)
#define tmr2_stop()                 (T2CONbits.TMR2ON = 0)
#define tmr2_interrupt_enable()     (PIE1bits.TMR2IE = 1)
#define tmr2_interrupt_disable()    (PIE1bits.TMR2IE = 0)
    
    typedef void (* tmr_isr_cb_t)();
    
    extern void tmr0_init(tmr_isr_cb_t cb);
    extern void tmr0_isr();
    
    extern void tmr2_init(tmr_isr_cb_t cb);
    extern void tmr2_isr();


#ifdef	__cplusplus
}
#endif

#endif	/* TMR_H */

