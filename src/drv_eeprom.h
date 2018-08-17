/* 
 * File:   drv_eeprom.h
 * Author: liruya
 *
 * Created on 2018年7月3日, 下午5:27
 */

#ifndef DRV_EEPROM_H
#define	DRV_EEPROM_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"
    
    extern void eeprom_write(uint8_t addr, uint8_t byte);
    extern uint8_t eeprom_read(uint8_t addr);
    extern void eeprom_write_buffer(uint8_t addr, uint8_t *pbuf, uint8_t len);
    extern void eeprom_read_buffer(uint8_t addr, uint8_t *pbuf, uint8_t len);

#ifdef	__cplusplus
}
#endif

#endif	/* DRV_EEPROM_H */

