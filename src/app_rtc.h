/* 
 * File:   app_rtc.h
 * Author: liruya
 *
 * Created on 2018年7月4日, 上午11:18
 */

#ifndef APP_RTC_H
#define	APP_RTC_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "app_common.h"

    typedef union {

        struct {
            uint8_t year;
            uint8_t month;
            uint8_t day;
            uint8_t week;
            uint8_t hour;
            uint8_t minute;
            uint8_t second;
        };
        uint8_t array[7];
    } date_time_t;

    extern void rtc_init();
    extern bool rtc_second_ready();
    extern void rtc_process();
    extern void rtc_set(const uint8_t * ptime);
    extern uint8_t rtc_get_year();
    extern uint8_t rtc_get_month();
    extern uint8_t rtc_get_day();
    extern uint8_t rtc_get_week();
    extern uint8_t rtc_get_hour();
    extern uint8_t rtc_get_minute();
    extern uint8_t rtc_get_second();

#ifdef	__cplusplus
}
#endif

#endif	/* APP_RTC_H */

