/* 
 * File:   app_key.h
 * Author: liruya
 *
 * Created on 2018年7月4日, 上午10:44
 */

#ifndef APP_KEY_H
#define	APP_KEY_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "app_common.h"
    
    /* RC0 -> Touch */
#define KEY_PORT                PORTC
#define KEY_MASK                0x01
#define KEY_NONE                0x00
#define KEY_TOUCH               0x01
    
#define LONG_PRESS_THRESHOLD    32
#define CONT_PRESS_INTERVAL     1
    
    typedef uint8_t key_value_t;
    
    typedef enum _key_state{
        KEY_STATE_SHORT_PRESS,
        KEY_STATE_LONG_PRESS,
        KEY_STATE_CONT_PRESS,
        KEY_STATE_RELEASE
    } key_state_t;
    
    typedef void (* key_func_t)(key_value_t key, key_state_t state);
    
    extern void key_init(key_func_t cb);
    extern void key_scan();

#ifdef	__cplusplus
}
#endif

#endif	/* APP_KEY_H */

