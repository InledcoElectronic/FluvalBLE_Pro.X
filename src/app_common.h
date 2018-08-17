/* 
 * File:   app_common.h
 * Author: liruya
 *
 * Created on 2018年7月3日, 下午3:25
 */

#ifndef APP_COMMON_H
#define	APP_COMMON_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "drv_common.h"
    
#ifdef  APP_DEBUG_ENABLED
#define app_printi( value )     printf( "\n[%s] @%d: " #value "=%d", __FILE__, __LINE__, value )
#define app_printd( value )     printf( "\n[%s] @%d: " #value "=%f", __FILE__, __LINE__, value )
#define app_printc( value )     printf( "\n[%s] @%d: " #value "=%c", __FILE__, __LINE__, value )
#define app_prints( str )       printf( "\n[%s] @%d: " str "\n", __FILE__, __LINE__ )
#define app_printf( format )    printf( "\n[%s] @%d: ", __FILE__, __LINE__ );\
                                printf format
#else
#define app_printi( value )
#define app_printd( value )
#define app_printc( value )
#define app_prints( str )
#define app_printf( format )
#endif
    
#ifdef	__cplusplus
}
#endif

#endif	/* APP_COMMON_H */

