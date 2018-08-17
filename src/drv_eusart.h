/* 
 * File:   drv_eusart.h
 * Author: liruya
 *
 * Created on 2018年7月3日, 下午5:45
 */

#ifndef DRV_EUSART_H
#define	DRV_EUSART_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"
    
#define eusart_receive_interrupt_enable()       (PIE1bits.RCIE = 1)
#define eusart_receive_interrupt_disable()      (PIE1bits.RCIE = 0)
    
    typedef void (*eusart_rcv_cb_t)(uint8_t rcv);
    
    extern void eusart_init(eusart_rcv_cb_t cb);
    extern uint8_t eusart_write(uint8_t byte);
    extern void eusart_transmit_isr();
    extern void eusart_receive_isr();
    

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_EUSART_H */

