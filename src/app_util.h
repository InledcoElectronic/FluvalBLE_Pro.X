/* 
 * File:   app_util.h
 * Author: liruya
 *
 * Created on 2018年7月4日, 下午1:46
 */

#ifndef APP_UTIL_H
#define	APP_UTIL_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "app_common.h"
    
    extern void increase(uint16_t * const psrc, const uint8_t delt, const uint16_t max);
    extern void decrease(uint16_t * const psrc, const uint8_t delt, const uint16_t min);


#ifdef	__cplusplus
}
#endif

#endif	/* APP_UTIL_H */

