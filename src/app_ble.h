/* 
 * File:   app_ble.h
 * Author: liruya
 *
 * Created on 2018年7月4日, 下午1:54
 */

#ifndef APP_BLE_H
#define	APP_BLE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "app_common.h"

    extern void ble_init();
    extern void ble_process();
    extern void ble_receive(uint8_t rcv);

#ifdef	__cplusplus
}
#endif

#endif	/* APP_BLE_H */

