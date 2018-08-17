/* 
 * File:   drv_common.h
 * Author: liruya
 *
 * Created on 2018年7月3日, 下午3:25
 */

#ifndef DRV_COMMON_H
#define	DRV_COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <xc.h>

#define global_interrupt_enable()       (INTCONbits.GIE = 1)
#define global_interrupt_disable()      (INTCONbits.GIE = 0)
#define peripheral_interrupt_enable()   (INTCONbits.PEIE = 1)
#define peripheral_interrupt_disable()  (INTCONbits.PEIE = 0)
    
#define _XTAL_FREQ                      16000000

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_COMMON_H */

