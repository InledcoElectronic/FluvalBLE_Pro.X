/* 
 * File:   app_led.h
 * Author: liruya
 *
 * Created on 2018年7月4日, 下午4:21
 */

#ifndef APP_LED_H
#define	APP_LED_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "app_common.h"


#define MARINE_CHANNEL_COUNT            5
#define PLANT_CHANNEL_COUNT             5
#define NANO_MARINE_CHANNEL_COUNT       5
#define NANO_PLANT_CHANNEL_COUNT        5
#define BLUE_CHANNEL_COUNT              4
#define AQUASKY_CHANNEL_COUNT           4

    //#define STRIP_NIGHT_CHANNEL             2
#define MARINE_NIGHT_CHANNEL            2
#define PLANT_NIGHT_CHANNEL             1  
#define NANO_MARINE_NIGHT_CHANNEL       2
#define NANO_PLANT_NIGHT_CHANNEL        1
#define BLUE_NIGHT_CHANNEL              3
#define AQUASKY_NIGHT_CHANNEL           2

    //#define LIGHT_TYPE_STRIP_III            0x0111
#define LIGHT_TYPE_MARINE_REEF_500      0x0121                  //Strip III Marine
#define LIGHT_TYPE_MARINE_REEF_800      0x0122
#define LIGHT_TYPE_MARINE_REEF_1100     0x0123
#define LIGHT_TYPE_MARINE_REEF_1000     0x0124
#define LIGHT_TYPE_PLANT_FRESH_500      0x0131                  //Strip III Plant
#define LIGHT_TYPE_PLANT_FRESH_800      0x0132
#define LIGHT_TYPE_PLANT_FRESH_1100     0x0133
#define LIGHT_TYPE_PLANT_FRESH_1000     0x0134
#define LIGHT_TYPE_NANO_MARINE          0x0151                  //Wing Nano Marine
#define LIGHT_TYPE_NANO_PLANT           0x0152                  //Wing Nano Plant
#define LIGHT_TYPE_BLUE_500             0x0161                  //Strip III Blue
#define LIGHT_TYPE_BLUE_800             0x0162
#define LIGHT_TYPE_BLUE_1100            0x0163
#define LIGHT_TYPE_BLUE_1000            0x0164
#define LIGHT_TYPE_AQUASKY_600          0x0141                  //Aquasky II
#define LIGHT_TYPE_AQUASKY_900          0x0142
#define LIGHT_TYPE_AQUASKY_1200         0x0143
#define LIGHT_TYPE_AQUASKY_380          0x0144
#define LIGHT_TYPE_AQUASKY_530          0x0145
#define LIGHT_TYPE_AQUASKY_835          0x0146
#define LIGHT_TYPE_AQUASKY_990          0x0147
#define LIGHT_TYPE_AQUASKY_750          0x0148
#define LIGHT_TYPE_AQUASKY_1150         0x0149
#define LIGHT_TYPE_AQUASKY_910          0x0150

    //#define LIGHT_ID_STRIP_III              "30313131"            //0111
#define LIGHT_ID_MARINE_REEF_500        "30313231"            //0121    Strip III Marine
#define LIGHT_ID_MARINE_REEF_800        "30313232"            //0122
#define LIGHT_ID_MARINE_REEF_1100       "30313233"            //0123
#define LIGHT_ID_MARINE_REEF_1000       "30313234"            //0124
#define LIGHT_ID_PLANT_FRESH_500        "30313331"            //0131    Strip III Plant
#define LIGHT_ID_PLANT_FRESH_800        "30313332"            //0132
#define LIGHT_ID_PLANT_FRESH_1100       "30313333"            //0133
#define LIGHT_ID_PLANT_FRESH_1000       "30313334"            //0134
#define LIGHT_ID_NANO_MARINE            "30313531"            //0151    Wing Nano Marine
#define LIGHT_ID_NANO_PLANT             "30313532"            //0152    Wing Nano Plant
#define LIGHT_ID_BLUE_500               "30313631"            //0161    Strip III Blue
#define LIGHT_ID_BLUE_800               "30313632"            //0162
#define LIGHT_ID_BLUE_1100              "30313633"            //0163
#define LIGHT_ID_BLUE_1000              "30313634"            //0164
#define LIGHT_ID_AQUASKY_600            "30313431"            //0141    Aquasky II
#define LIGHT_ID_AQUASKY_900            "30313432"            //0142
#define LIGHT_ID_AQUASKY_1200           "30313433"            //0143
#define LIGHT_ID_AQUASKY_380            "30313434"            //0144
#define LIGHT_ID_AQUASKY_530            "30313435"            //0145
#define LIGHT_ID_AQUASKY_835            "30313436"            //0146
#define LIGHT_ID_AQUASKY_990            "30313437"            //0147
#define LIGHT_ID_AQUASKY_750            "30313438"            //0148
#define LIGHT_ID_AQUASKY_1150           "30313439"            //0149
#define LIGHT_ID_AQUASKY_910            "30313530"            //0150

#define FIRMWARE_VERSION                "30313033"            //0103
#define DEVICE_ID_VERSION               LIGHT_ID FIRMWARE_VERSION       

#if		LIGHT_TYPE == LIGHT_TYPE_MARINE_REEF_500 ||\
		LIGHT_TYPE == LIGHT_TYPE_MARINE_REEF_800 ||\
		LIGHT_TYPE == LIGHT_TYPE_MARINE_REEF_1100 ||\
		LIGHT_TYPE == LIGHT_TYPE_MARINE_REEF_1000
#define CHANNEL_COUNT   MARINE_CHANNEL_COUNT
#define NIGHT_CHANNEL   MARINE_NIGHT_CHANNEL
#define TOUCH_ENABLE
#elif	LIGHT_TYPE == LIGHT_TYPE_PLANT_FRESH_500 ||\
		LIGHT_TYPE == LIGHT_TYPE_PLANT_FRESH_800 ||\
		LIGHT_TYPE == LIGHT_TYPE_PLANT_FRESH_1100 ||\
		LIGHT_TYPE == LIGHT_TYPE_PLANT_FRESH_1000
#define CHANNEL_COUNT   PLANT_CHANNEL_COUNT
#define NIGHT_CHANNEL   PLANT_NIGHT_CHANNEL 
#define TOUCH_ENABLE
#elif	LIGHT_TYPE == LIGHT_TYPE_NANO_MARINE
#define CHANNEL_COUNT   NANO_MARINE_CHANNEL_COUNT
#define NIGHT_CHANNEL   NANO_MARINE_NIGHT_CHANNEL
#elif	LIGHT_TYPE == LIGHT_TYPE_NANO_PLANT
#define CHANNEL_COUNT   NANO_PLANT_CHANNEL_COUNT
#define NIGHT_CHANNEL   NANO_PLANT_NIGHT_CHANNEL
#elif	LIGHT_TYPE == LIGHT_TYPE_BLUE_500 ||\
		LIGHT_TYPE == LIGHT_TYPE_BLUE_800 ||\
		LIGHT_TYPE == LIGHT_TYPE_BLUE_1100 ||\
		LIGHT_TYPE == LIGHT_TYPE_BLUE_1000
#define CHANNEL_COUNT   BLUE_CHANNEL_COUNT
#define NIGHT_CHANNEL   BLUE_NIGHT_CHANNEL   
#define TOUCH_ENABLE
#elif	LIGHT_TYPE == LIGHT_TYPE_AQUASKY_600 ||\
		LIGHT_TYPE == LIGHT_TYPE_AQUASKY_900 ||\
		LIGHT_TYPE == LIGHT_TYPE_AQUASKY_1200 ||\
		LIGHT_TYPE == LIGHT_TYPE_AQUASKY_380 ||\
		LIGHT_TYPE == LIGHT_TYPE_AQUASKY_530 ||\
		LIGHT_TYPE == LIGHT_TYPE_AQUASKY_835 ||\
		LIGHT_TYPE == LIGHT_TYPE_AQUASKY_990 ||\
		LIGHT_TYPE == LIGHT_TYPE_AQUASKY_750 ||\
		LIGHT_TYPE == LIGHT_TYPE_AQUASKY_1150 ||\
		LIGHT_TYPE == LIGHT_TYPE_AQUASKY_910
#define CHANNEL_COUNT   AQUASKY_CHANNEL_COUNT  
#define NIGHT_CHANNEL   AQUASKY_NIGHT_CHANNEL
#define DYNAMIC_ENABLE
#endif
    
    
#define CUSTOM_COUNT        4
#define POINT_COUNT_MIN     4
#define POINT_COUNT_MAX     10
    
#define BLE_MODE_MANUAL		0
#define BLE_MODE_AUTO		1
#define BLE_MODE_PRO		2
    
#define DYNAMIC_NONE        0
#define DYNAMIC_THUNDER1    1
#define DYNAMIC_THUNDER2    2
#define DYNAMIC_THUNDER3    3
#define DYNAMIC_ALLCOLOR    4
#define DYNAMIC_CLOUD1      5
#define DYNAMIC_CLOUD2      6
#define DYNAMIC_CLOUD3      7
#define DYNAMIC_CLOUD4      8
#define DYNAMIC_MOON1       9
#define DYNAMIC_MOON2       10
#define DYNAMIC_MOON3       11
#define DYNAMIC_SUNRS       12
#define DYNAMIC_PAUSE       13
    
    typedef struct{
        uint8_t hour;
        uint8_t minute;
        uint8_t bright[CHANNEL_COUNT];
    }timer_bright_point_t;
    
    typedef union{
        struct{
            bool mOn;
            uint8_t mDyn;
            uint16_t mBright[CHANNEL_COUNT];
            uint8_t mCustomBright[CUSTOM_COUNT][CHANNEL_COUNT];
        };
        uint8_t array[(CUSTOM_COUNT+2)*CHANNEL_COUNT+2];
    }manual_para_t;
    
    typedef union{
        struct{
            uint8_t sunrise_start_hour;
            uint8_t sunrise_start_minute;
            uint8_t sunrise_end_hour;
            uint8_t sunrise_end_minute;
            uint8_t day_bright[CHANNEL_COUNT];
            uint8_t sunset_start_hour;
            uint8_t sunset_start_minute;
            uint8_t sunset_end_hour;
            uint8_t sunset_end_minute;
            uint8_t night_bright[CHANNEL_COUNT];
            bool turnoff_enabled;
            uint8_t turnoff_hour;
            uint8_t turnoff_minute;
        };
        uint8_t array[2*CHANNEL_COUNT+11];
    }auto_para_t;
    
    typedef union{
        struct{
            uint8_t point_count;
            timer_bright_point_t points[POINT_COUNT_MAX];
        };
        uint8_t array[POINT_COUNT_MAX*(2+CHANNEL_COUNT)+1];
    }pro_para_t;
    
    typedef union{
        struct{
            unsigned sun : 1;
            unsigned mon : 1;
            unsigned tue : 1;
            unsigned wed : 1;
            unsigned thu : 1;
            unsigned fri : 1;
            unsigned sat : 1;
            unsigned enable : 1;
            
            uint8_t start_hour;
            uint8_t start_minute;
            uint8_t end_hour;
            uint8_t end_minute;
            uint8_t dynamic_mode;
        };
        uint8_t array[6];
    }dynamic_para_t;
    
    typedef struct{
        unsigned mMode : 2;
        unsigned : 6;
        manual_para_t manual_para;
        auto_para_t auto_para;
        pro_para_t pro_para;
#ifdef  DYNAMIC_ENABLE
        dynamic_para_t dynamic_para;
#endif
    }ble_para_t;
    
    typedef struct{
        uint8_t save_flag;

#ifdef  TOUCH_ENABLE        
        unsigned mState : 2;
        unsigned last_mode : 2;
        unsigned : 4;        
        uint16_t all_bright;
        uint16_t blue_bright;
#endif
        
        ble_para_t ble_para;
    }led_para_t;
    
    extern led_para_t m_led_para;

#ifdef  TOUCH_ENABLE  
#include "app_key.h"    
    extern void led_touch_cb(key_value_t key, key_state_t state);
#endif
    
    extern void led_init();
    extern void led_process();
    extern void led_second_cb();  
    extern void led_start_flash();
    extern void led_start_preview();
    extern void led_stop_preview();
    extern bool led_set_mode(uint8_t m);
    extern bool led_set_power(bool on);
    extern bool led_set_bright(const uint8_t * const pbuf);
    extern bool led_set_custom(uint8_t idx);
    extern bool led_set_cycle(const uint8_t * const pbuf);
    extern bool led_set_pro(const uint8_t * const pbuf);
    extern bool led_increase(uint8_t chn, uint8_t delt);
    extern bool led_decrease(uint8_t chn, uint8_t delt);
    extern bool led_set_preview(const uint8_t * const pbuf);
    extern void led_set_time(const uint8_t* ptime);
#ifdef	DYNAMIC_ENABLE
    extern bool led_set_dynamic(uint8_t dyn);
    extern void led_set_period_dynamic(const uint8_t * const pbuf);
#endif
    
#ifdef	__cplusplus
}
#endif

#endif	/* APP_LED_H */

