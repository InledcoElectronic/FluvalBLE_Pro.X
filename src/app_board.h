/* 
 * File:   app_board.h
 * Author: liruya
 *
 * Created on 2018年7月3日, 下午3:32
 */

#ifndef APP_BOARD_H
#define	APP_BOARD_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include <pic16f18345.h>
    
#define BLE_RST             LATBbits.LATB5
#define BLE_WKP             LATCbits.LATC1
#define BLE_INT             PORTAbits.RA2
    
#define LEDR                LATBbits.LATB6
#define LEDG                LATAbits.LATA1
#define LEDB                LATBbits.LATB7

#ifdef	__cplusplus
}
#endif

#endif	/* APP_BOARD_H */

