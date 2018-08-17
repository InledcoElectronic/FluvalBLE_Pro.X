#include "app_led.h"
#include "drv_pwm.h"
#include "drv_eeprom.h"
#include "app_rtc.h"
#include "app_util.h"
#include "app_board.h"

#define PARA_SAVED_FLAG		0x55

#define FIND_FLASH_COUNT    3
#define PREVIEW_COUNT       3
#define MIN_LED_BRIGHT      10
#define MAX_LED_BRIGHT      1000
#define DELTA_LED_BRIGHT    200
#define STEP_NORMAL_BRIGHT  4

#define ADDR_LED_PARA       0x10            //led para saved offset addr
#define PARA_SAVE_DELAY     3               //para saved delay if there is no para changed

#define LED_STEP_TOUCH      2
#define LED_DELTA_TOUCH     10   

#define LED_STATUS_OFF      0
#define LED_STATUS_DAY      1
#define LED_STATUS_NIGHT    2
#define LED_STATUS_BLE      3

#define ledr_on()			(LEDR = 0)
#define ledr_off()			(LEDR = 1)
#define ledg_on()			(LEDG = 0)
#define ledg_off()			(LEDG = 1)
#define ledb_on()			(LEDB = 0)
#define ledb_off()			(LEDB = 1)

typedef struct {
	unsigned mFind : 1;
	unsigned mPrev : 1;
	unsigned mSave : 1;
	unsigned mDr : 1;
	unsigned mNr : 1;
	unsigned : 3;

	uint8_t flash_count;
	uint8_t prev_count;
	uint8_t save_delay_count;
} led_run_para_t;

#ifdef DYNAMIC_ENABLE
#define THUNDER1_STATE_MAX  10
#define THUNDER2_STATE_MAX  74
#define THUNDER3_STATE_MAX  16
#define ALLCOLOR_STATE_MAX  4

typedef void (* dynamic_func_t)();

volatile uint8_t dynamic_chn;
volatile uint8_t dynamic_rise;
uint8_t dynamic_min[CHANNEL_COUNT];
uint8_t dynamic_max[CHANNEL_COUNT];
volatile uint16_t dynamic_period;
volatile uint16_t dynamic_count;
volatile uint8_t dynamic_state;
volatile bool dynamic_run_pause;
volatile uint8_t dynamic_run_mode;

static void led_thunder1_init();
static void led_thunder2_init();
static void led_thunder3_init();
static void led_allcolor_init();
static void led_cloud1_init();
static void led_cloud2_init();
static void led_cloud3_init();
static void led_cloud4_init();
static void led_moon1_init();
static void led_moon2_init();
static void led_moon3_init();
static void led_sunrs_init();
static void led_thunder1_process();
static void led_thunder2_process();
static void led_thunder3_process();
static void led_allcolor_process();
static void led_dynamic_process();
static void led_dynamic_init(uint8_t dyn);
dynamic_func_t dynamic_func_init[] = {  led_thunder1_init, led_thunder2_init, led_thunder3_init, led_allcolor_init, 
										led_cloud1_init, led_cloud2_init, led_cloud3_init, led_cloud4_init, 
										led_moon1_init, led_moon2_init, led_moon3_init };
#endif

led_para_t m_led_para;
led_run_para_t led_run_para;
uint16_t target_bright[CHANNEL_COUNT];
uint16_t current_bright[CHANNEL_COUNT];

#ifdef TOUCH_ENABLE
static void led_indicate_off();
static void led_indicate_day();
static void led_indicate_night();
static void led_indicate_ble();
static void led_update_day_bright();
static void led_update_day_status();
static void led_update_night_bright();
static void led_update_night_status();
static void led_state_off_cb(uint8_t key, key_state_t state);
static void led_state_day_cb(uint8_t key, key_state_t state);
static void led_state_night_cb(uint8_t key, key_state_t state);
static void led_state_ble_cb(uint8_t key, key_state_t state);
key_func_t led_state_cb[4] = {led_state_off_cb, led_state_day_cb, led_state_night_cb, led_state_ble_cb};
#endif

static void led_turnon_ramp();
static void led_turnoff_ramp();
static void led_turnoff();
static void led_prepare_to_save();

typedef void (*led_load_duty_func_t)(uint16_t);
#if		LIGHT_TYPE == LIGHT_TYPE_MARINE_REEF_500 ||\
		LIGHT_TYPE == LIGHT_TYPE_MARINE_REEF_800 ||\
		LIGHT_TYPE == LIGHT_TYPE_MARINE_REEF_1100 ||\
		LIGHT_TYPE == LIGHT_TYPE_MARINE_REEF_1000
static led_load_duty_func_t led_load_duty[CHANNEL_COUNT] = {pwm2_load_duty,
	pwm4_load_duty,
	pwm5_load_duty,
	pwm3_load_duty,
	pwm1_load_duty};
#elif	LIGHT_TYPE == LIGHT_TYPE_PLANT_FRESH_500 ||\
		LIGHT_TYPE == LIGHT_TYPE_PLANT_FRESH_800 ||\
		LIGHT_TYPE == LIGHT_TYPE_PLANT_FRESH_1100 ||\
		LIGHT_TYPE == LIGHT_TYPE_PLANT_FRESH_1000
static led_load_duty_func_t led_load_duty[CHANNEL_COUNT] = {pwm2_load_duty,
	pwm5_load_duty,
	pwm3_load_duty,
	pwm1_load_duty,
	pwm4_load_duty};
#elif	LIGHT_TYPE == LIGHT_TYPE_NANO_MARINE
static led_load_duty_func_t led_load_duty[CHANNEL_COUNT] = {pwm2_load_duty,
	pwm1_load_duty,
	pwm3_load_duty,
	pwm4_load_duty,
	pwm5_load_duty};
#elif	LIGHT_TYPE == LIGHT_TYPE_NANO_PLANT
static led_load_duty_func_t led_load_duty[CHANNEL_COUNT] = {pwm3_load_duty,
	pwm2_load_duty,
	pwm1_load_duty,
	pwm5_load_duty,
	pwm4_load_duty};
#elif	LIGHT_TYPE == LIGHT_TYPE_BLUE_500 ||\
		LIGHT_TYPE == LIGHT_TYPE_BLUE_800 ||\
		LIGHT_TYPE == LIGHT_TYPE_BLUE_1100 ||\
		LIGHT_TYPE == LIGHT_TYPE_BLUE_1000
/* 400num 440nm 420nm 460nm */
static led_load_duty_func_t led_load_duty[CHANNEL_COUNT] = {pwm4_load_duty,
	pwm1_load_duty,
	pwm3_load_duty,
	pwm5_load_duty};
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
static led_load_duty_func_t led_load_duty[CHANNEL_COUNT] = {pwm1_load_duty,
	pwm2_load_duty,
	pwm3_load_duty,
	pwm4_load_duty};
#endif

static void led_para_default()
{
	memset(&m_led_para, 0, sizeof(m_led_para));
	
#ifdef	TOUCH_ENABLE
//	m_led_para.mState = LED_STATUS_OFF;
	m_led_para.last_mode = BLE_MODE_AUTO;
	m_led_para.all_bright = MAX_LED_BRIGHT;
	m_led_para.blue_bright = MAX_LED_BRIGHT;
#endif

//	m_led_para.ble_para.mMode = BLE_MODE_MANUAL;

	m_led_para.ble_para.auto_para.sunrise_start_hour = 7;
//	m_led_para.ble_para.auto_para.sunrise_start_minute = 0;
	m_led_para.ble_para.auto_para.sunrise_end_hour = 8;
//	m_led_para.ble_para.auto_para.sunrise_end_minute = 0;
	for(uint8_t i = 0; i < CHANNEL_COUNT; i++)
	{
		m_led_para.ble_para.auto_para.day_bright[i] = 100;
	}
	m_led_para.ble_para.auto_para.sunset_start_hour = 17;
//	m_led_para.ble_para.auto_para.sunset_start_minute = 0;
	m_led_para.ble_para.auto_para.sunset_end_hour = 18;
//	m_led_para.ble_para.auto_para.sunset_end_minute = 0;
	m_led_para.ble_para.auto_para.night_bright[NIGHT_CHANNEL] = 5;
	m_led_para.ble_para.auto_para.turnoff_enabled = true;
	m_led_para.ble_para.auto_para.turnoff_hour = 22;
//	m_led_para.ble_para.auto_para.turnoff_minute = 0;

	m_led_para.ble_para.manual_para.mOn = 1;
	for(uint8_t i = 0; i < CHANNEL_COUNT; i++)
	{
		m_led_para.ble_para.manual_para.mBright[i] = MAX_LED_BRIGHT;
		for(uint8_t j = 0; j < CUSTOM_COUNT; j++)
		{
			m_led_para.ble_para.manual_para.mCustomBright[j][i] = 100;
		}
	}
	
	m_led_para.ble_para.pro_para.point_count = 6;
	m_led_para.ble_para.pro_para.points[0].hour = 7;
//	m_led_para.ble_para.pro_para.points[0].minuite = 0;
	m_led_para.ble_para.pro_para.points[1].hour = 8;
//	m_led_para.ble_para.pro_para.points[1].minuite = 0;
	m_led_para.ble_para.pro_para.points[2].hour = 17;
//	m_led_para.ble_para.pro_para.points[2].minuite = 0;
	m_led_para.ble_para.pro_para.points[3].hour = 18;
//	m_led_para.ble_para.pro_para.points[3].minuite = 0;
	m_led_para.ble_para.pro_para.points[4].hour = 22;
//	m_led_para.ble_para.pro_para.points[4].minuite = 0;
	m_led_para.ble_para.pro_para.points[5].hour = 22;
	m_led_para.ble_para.pro_para.points[5].minute = 30;
	for(uint8_t i = 0; i < CHANNEL_COUNT; i++)
	{
//		m_led_para.ble_para.pro_para.points[0].bright[i] = 0;
		m_led_para.ble_para.pro_para.points[1].bright[i] = 100;
		m_led_para.ble_para.pro_para.points[2].bright[i] = 100;
//		m_led_para.ble_para.pro_para.points[3].bright[i] = 0;
//		m_led_para.ble_para.pro_para.points[4].bright[i] = 0;
//		m_led_para.ble_para.pro_para.points[5].bright[i] = 0;
	}
	m_led_para.ble_para.pro_para.points[3].bright[NIGHT_CHANNEL] = 5;
	m_led_para.ble_para.pro_para.points[4].bright[NIGHT_CHANNEL] = 5;
}

static void led_para_init()
{
	uint8_t i, j;
	eeprom_read_buffer(ADDR_LED_PARA, (uint8_t *) &m_led_para, sizeof(m_led_para));
	if(m_led_para.save_flag != PARA_SAVED_FLAG)
	{
		led_para_default();
	}
	
#ifdef	TOUCH_ENABLE
	/* touch para check */
	if(m_led_para.last_mode != BLE_MODE_AUTO && m_led_para.last_mode != BLE_MODE_PRO)
	{
		m_led_para.last_mode = BLE_MODE_AUTO;
	}
	if(m_led_para.all_bright > MAX_LED_BRIGHT)
	{
		m_led_para.all_bright = MAX_LED_BRIGHT;
	}
	if(m_led_para.all_bright < MIN_LED_BRIGHT)
	{
		m_led_para.all_bright = MIN_LED_BRIGHT;
	}
	if(m_led_para.blue_bright > MAX_LED_BRIGHT)
	{
		m_led_para.blue_bright = MAX_LED_BRIGHT;
	}
	if(m_led_para.blue_bright < MIN_LED_BRIGHT)
	{
		m_led_para.blue_bright = MIN_LED_BRIGHT;
	}
#endif
	
	if(m_led_para.ble_para.mMode > BLE_MODE_PRO)
	{
		m_led_para.ble_para.mMode = BLE_MODE_MANUAL;
	}
	
	/* manual para check */
	for(i = 0; i < CHANNEL_COUNT; i++)
	{
		if(m_led_para.ble_para.manual_para.mBright[i] > MAX_LED_BRIGHT)
		{
			m_led_para.ble_para.manual_para.mBright[i] = MAX_LED_BRIGHT;
		}
		for(j = 0; j < CUSTOM_COUNT; j++)
		{
			if(m_led_para.ble_para.manual_para.mCustomBright[j][i] > 100)
			{
				m_led_para.ble_para.manual_para.mCustomBright[j][i] = 100;
			}
		}
	}
	
	/* auto para check */
	if(m_led_para.ble_para.auto_para.sunrise_start_hour > 23)
	{
		m_led_para.ble_para.auto_para.sunrise_start_hour = 0;
	}
	if(m_led_para.ble_para.auto_para.sunrise_start_minute > 59)
	{
		m_led_para.ble_para.auto_para.sunrise_start_minute = 0;
	}
	if(m_led_para.ble_para.auto_para.sunrise_end_hour > 23)
	{
		m_led_para.ble_para.auto_para.sunrise_end_hour = 0;
	}
	if(m_led_para.ble_para.auto_para.sunrise_end_minute > 59)
	{
		m_led_para.ble_para.auto_para.sunrise_end_minute = 0;
	}
	if(m_led_para.ble_para.auto_para.sunset_start_hour > 23)
	{
		m_led_para.ble_para.auto_para.sunset_start_hour = 0;
	}
	if(m_led_para.ble_para.auto_para.sunset_start_minute > 59)
	{
		m_led_para.ble_para.auto_para.sunset_start_minute = 0;
	}
	if(m_led_para.ble_para.auto_para.sunset_end_hour > 23)
	{
		m_led_para.ble_para.auto_para.sunset_end_hour = 0;
	}
	if(m_led_para.ble_para.auto_para.sunset_end_minute > 59)
	{
		m_led_para.ble_para.auto_para.sunset_end_minute = 0;
	}
	if(m_led_para.ble_para.auto_para.turnoff_hour > 23)
	{
		m_led_para.ble_para.auto_para.turnoff_hour = 0;
	}
	if(m_led_para.ble_para.auto_para.turnoff_minute > 59)
	{
		m_led_para.ble_para.auto_para.turnoff_minute = 0;
	}
	for(i = 0; i < CHANNEL_COUNT; i++)
	{
		if(m_led_para.ble_para.auto_para.day_bright[i] > 100)
		{
			m_led_para.ble_para.auto_para.day_bright[i] = 100;
		}
		if(m_led_para.ble_para.auto_para.night_bright[i] > 100)
		{
			m_led_para.ble_para.auto_para.night_bright[i] = 100;
		}
	}
	
	/* pro para check */
	if(m_led_para.ble_para.pro_para.point_count < POINT_COUNT_MIN || m_led_para.ble_para.pro_para.point_count > POINT_COUNT_MAX)
	{
		m_led_para.ble_para.pro_para.point_count = 6;
	}
	for(i = 0; i < POINT_COUNT_MAX; i++)
	{
		if(m_led_para.ble_para.pro_para.points[i].hour > 23)
		{
			m_led_para.ble_para.pro_para.points[i].hour = 0;
		}
		if(m_led_para.ble_para.pro_para.points[i].minute > 59)
		{
			m_led_para.ble_para.pro_para.points[i].minute = 0;
		}
		for(j = 0; j < CHANNEL_COUNT; j++)
		{
			if(m_led_para.ble_para.pro_para.points[i].bright[j] > 100)
			{
				m_led_para.ble_para.pro_para.points[i].bright[j] = 100;
			}
		}
	}
	
	/* dynamic para check */
#ifdef	DYNAMIC_ENABLE
	if(m_led_para.ble_para.manual_para.mDyn >= DYNAMIC_SUNRS)
	{
		m_led_para.ble_para.manual_para.mDyn = DYNAMIC_NONE;
	}
	if(m_led_para.ble_para.dynamic_para.dynamic_mode >= DYNAMIC_SUNRS)
	{
		m_led_para.ble_para.dynamic_para.dynamic_mode = DYNAMIC_NONE;
	}
	if(m_led_para.ble_para.dynamic_para.start_hour > 23)
	{
		m_led_para.ble_para.dynamic_para.start_hour = 0;
	}
	if(m_led_para.ble_para.dynamic_para.start_minute > 59)
	{
		m_led_para.ble_para.dynamic_para.start_minute = 0;
	}
	if(m_led_para.ble_para.dynamic_para.end_hour > 23)
	{
		m_led_para.ble_para.dynamic_para.end_hour = 0;
	}
	if(m_led_para.ble_para.dynamic_para.end_minute > 59)
	{
		m_led_para.ble_para.dynamic_para.end_minute = 0;
	}
#endif

#ifdef	TOUCH_ENABLE
	switch(m_led_para.mState)
	{
		case LED_STATUS_OFF:
			led_turnoff();
			led_indicate_off();
			break;
		case LED_STATUS_DAY:
			led_update_day_bright();
			led_indicate_day();
			break;
		case LED_STATUS_NIGHT:
			led_update_night_bright();
			led_indicate_night();
			break;
		case LED_STATUS_BLE:
			if(m_led_para.ble_para.mMode == BLE_MODE_MANUAL)
			{
				if(m_led_para.ble_para.manual_para.mOn)
				{
					led_turnon_ramp();
				}
				else
				{
					led_turnoff_ramp();
				}
			}
			led_indicate_ble();
			break;
		default:
			break;
	}
#else
	if(m_led_para.ble_para.mMode == BLE_MODE_MANUAL)
	{
		if(m_led_para.ble_para.manual_para.mOn)
		{
#ifdef	DYNAMIC_ENABLE
			if(m_led_para.ble_para.manual_para.mDyn > DYNAMIC_NONE && m_led_para.ble_para.manual_para.mDyn < DYNAMIC_SUNRS )
			{
				led_dynamic_init(m_led_para.ble_para.manual_para.mDyn);
			}
			else
			{
#endif
				led_turnon_ramp();
#ifdef	DYNAMIC_ENABLE
			}
#endif
		}
		else
		{
			led_turnoff_ramp();
		}
	}	
#endif
}

void led_init()
{
	led_para_init();
}

static uint16_t led_calc_bright(uint8_t sbrt, uint8_t ebrt, uint16_t duration, uint32_t dt)
{
	uint8_t dbrt;
	uint16_t result;
	uint16_t vs = sbrt*10u;
	uint16_t period = duration*6u;
	if(sbrt <= ebrt)
	{
		dbrt = ebrt - sbrt;
		result = vs + dbrt*dt/period;
	}
	else
	{
		dbrt = sbrt - ebrt;
		result = vs - dbrt*dt/period;
	}
	return result;
}

void led_ramp()
{
	for(uint8_t i = 0; i < CHANNEL_COUNT; i++)
	{
		if(current_bright[i] + STEP_NORMAL_BRIGHT < target_bright[i])
		{
			current_bright[i] += STEP_NORMAL_BRIGHT;
		}
		else if(current_bright[i] > target_bright[i] + STEP_NORMAL_BRIGHT)
		{
			current_bright[i] -= STEP_NORMAL_BRIGHT;
		}
		else
		{
			current_bright[i] = target_bright[i];
		}
		led_load_duty[i](current_bright[i]);
	}
}

void led_process()
{
#ifdef	DYNAMIC_ENABLE
	if(dynamic_run_mode > DYNAMIC_NONE && dynamic_run_mode < DYNAMIC_PAUSE)
	{
		led_dynamic_process();
	}
	else
	{
#endif
		led_ramp();
#ifdef	DYNAMIC_ENABLE
	}
#endif
}

static void led_auto_process(uint16_t ct, uint8_t sec)
{
	uint8_t i, j, k;
	uint16_t st;
	uint16_t et;
	uint16_t duration;
	uint32_t dt;
	uint8_t count = 4;
	auto_para_t *p = &m_led_para.ble_para.auto_para;
	uint16_t tr[6];
	tr[0] = p->sunrise_start_hour * 60u + p->sunrise_start_minute;
	tr[1] = p->sunrise_end_hour * 60u + p->sunrise_end_minute;
	tr[2] = p->sunset_start_hour * 60u + p->sunset_start_minute;
	tr[3] = p->sunset_end_hour * 60u + p->sunset_end_minute;
	tr[4] = p->turnoff_hour * 60u + p->turnoff_minute;
	tr[5] = tr[4];
	uint8_t val[6][CHANNEL_COUNT];
	for(i = 0; i < CHANNEL_COUNT; i++)
	{
		if(p->turnoff_enabled)
		{
			val[0][i] = 0;
		}
		else
		{
			val[0][i] = p->night_bright[i];
		}
		val[1][i] = p->day_bright[i];
		val[2][i] = p->day_bright[i];
		val[3][i] = p->night_bright[i];
		val[4][i] = p->night_bright[i];
		val[5][i] = 0;
	}
	if(p->turnoff_enabled)
	{
		count = 6;
	}
	for(i = 0; i < count; i++)
	{
		j = (i + 1) % count;
		st = tr[i];
		et = tr[j];
		if(et >= st)
		{
			if(ct >= st && ct < et)
			{
				duration = et - st;
				dt = (ct - st) * 60ul + sec;
			}
			else
			{
				continue;
			}
		}
		else
		{
			if(ct >= st || ct < et)
			{
				duration = 1440u - st + et;
				if(ct >= st)
				{
					dt = (ct - st) * 60ul + sec;
				}
				else
				{
					dt = (1440u - st + ct) * 60ul + sec;
				}
			}
			else
			{
				continue;
			}
		}
		for(k = 0; k < CHANNEL_COUNT; k++)
		{
			target_bright[k] = led_calc_bright(val[i][k], val[j][k], duration, dt );
//			current_bright[k] = target_bright[k];
		}
	}
}

static void led_pro_process(uint16_t ct, uint8_t sec)
{
	if(m_led_para.ble_para.pro_para.point_count < POINT_COUNT_MIN)
	{
		m_led_para.ble_para.pro_para.point_count = POINT_COUNT_MIN;
	}
	else if(m_led_para.ble_para.pro_para.point_count > POINT_COUNT_MAX)
	{
		m_led_para.ble_para.pro_para.point_count = POINT_COUNT_MAX;
	}
	uint8_t point_count = m_led_para.ble_para.pro_para.point_count;
	uint8_t i, j;
	uint8_t index[POINT_COUNT_MAX];
	for(i = 0; i < POINT_COUNT_MAX; i++)
	{
		index[i] = i;
	}
	for(i = point_count - 1; i > 0; i--)
	{
		for(j = 0; j < i; j++)
		{
			timer_bright_point_t *p1 = &m_led_para.ble_para.pro_para.points[index[j]];
			timer_bright_point_t *p2 = &m_led_para.ble_para.pro_para.points[index[j+1]];
			uint16_t t1 = p1->hour*60u + p1->minute;
			uint16_t t2 = p2->hour*60u + p2->minute;
			if(t1 > t2)
			{
				uint8_t tmp = index[j];
				index[j] = index[j+1];
				index[j+1] = tmp;
			}
		}
	}
	uint16_t start = index[point_count-1];
	uint16_t end = index[0];
	timer_bright_point_t *sp = &m_led_para.ble_para.pro_para.points[start];
	timer_bright_point_t *ep = &m_led_para.ble_para.pro_para.points[end];
	uint16_t st = sp->hour * 60u + sp->minute;
	uint16_t et = ep->hour * 60u + ep->minute;
	uint16_t duration = 1440u - st + et;
	uint32_t dt;
	bool flag = false;
	if(ct >= st)
	{
		dt = (ct-st)*60u + sec;
		flag = true;
	}
	else if(ct < et)
	{
		dt = (1440u-st+ct)*60u + sec;
		flag = true;
	}
	else
	{
		for(i = 0; i < point_count-1; i++)
		{
			start = index[i];
			end = index[i+1];
			sp = &m_led_para.ble_para.pro_para.points[start];
			ep = &m_led_para.ble_para.pro_para.points[end];
			st = sp->hour*60u + sp->minute;
			et = ep->hour*60u + ep->minute;
			if(ct >= st && ct < et)
			{
				duration = et - st;
				dt = (ct - st)*60u+sec;
				flag = true;
				break;
			}
		}
	}
	if(flag)
	{
		for(i = 0; i < CHANNEL_COUNT; i++)
		{
			target_bright[i] = led_calc_bright(sp->bright[i], ep->bright[i], duration, dt);
//			current_bright[i] = target_bright[i];
		}
	}
}

static void led_turnon_ramp()
{
	for(uint8_t i = 0; i < CHANNEL_COUNT; i++)
	{
		target_bright[i] = m_led_para.ble_para.manual_para.mBright[i];
	}
}

static void led_turnoff_ramp()
{
	for(uint8_t i = 0; i < CHANNEL_COUNT; i++)
	{
		target_bright[i] = 0;
	}
}

static void led_turnon_max()
{
	for(uint8_t i = 0; i < CHANNEL_COUNT; i++)
	{
		target_bright[i] = MAX_LED_BRIGHT;
		current_bright[i] = MAX_LED_BRIGHT;
	}
}

static void led_turnoff()
{
	for(uint8_t i = 0; i < CHANNEL_COUNT; i++)
	{
		target_bright[i] = 0;
		current_bright[i] = 0;
	}
}

#ifdef	TOUCH_ENABLE
static void led_indicate_off()
{
	ledr_on();
	ledg_off();
	ledb_off();
}

static void led_indicate_day()
{
	ledr_on();
	ledg_on();
	ledb_on();
}

static void led_indicate_night()
{
	ledr_off();
	ledg_off();
	ledb_on();
}

static void led_indicate_ble()
{
	ledr_off();
	ledg_on();
	ledb_off();
}

static void led_update_day_bright()
{
	for(uint8_t i = 0; i < CHANNEL_COUNT; i++)
	{
		current_bright[i] = m_led_para.all_bright;
		target_bright[i] = m_led_para.all_bright;
		m_led_para.ble_para.manual_para.mBright[i] = m_led_para.all_bright;
	}
}

static void led_update_day_status()
{
	if(m_led_para.all_bright > MAX_LED_BRIGHT - DELTA_LED_BRIGHT)
	{
		led_run_para.mDr = 0;
	}
	else if(m_led_para.all_bright < DELTA_LED_BRIGHT)
	{
		led_run_para.mDr = 1;
	}
}

static void led_update_night_bright()
{
	for(uint8_t i = 0; i < CHANNEL_COUNT; i++)
	{
		if(i == NIGHT_CHANNEL)
		{
			current_bright[i] = m_led_para.blue_bright;
			target_bright[i] = m_led_para.blue_bright;
			m_led_para.ble_para.manual_para.mBright[i] = m_led_para.blue_bright;
		}
		else
		{
			current_bright[i] = 0;
			target_bright[i] = 0;
			m_led_para.ble_para.manual_para.mBright[i] = 0;
		}
	}
}

static void led_update_night_status()
{
	if(m_led_para.blue_bright > MAX_LED_BRIGHT - DELTA_LED_BRIGHT)
	{
		led_run_para.mNr = 0;
	}
	else if(m_led_para.blue_bright < DELTA_LED_BRIGHT)
	{
		led_run_para.mNr = 1;
	}
}

/* key action @ led state off  */

static void led_state_off_short_press_cb()
{
	m_led_para.mState++;
	led_update_day_bright();
	led_indicate_day();
	led_prepare_to_save();
}

static void led_state_off_long_press_cb()
{
	m_led_para.mState++;
	m_led_para.all_bright = MIN_LED_BRIGHT;
	led_update_day_bright();
	led_indicate_day();
	led_run_para.mDr = 1;
}

static void led_state_off_cont_press_cb() { }

static void led_state_off_release_cb() { }

static void led_state_off_cb(uint8_t key, key_state_t state)
{
	if(key == KEY_TOUCH)
	{
		switch(state)
		{
			case KEY_STATE_SHORT_PRESS:
				led_state_off_short_press_cb();
				break;
			case KEY_STATE_LONG_PRESS:
				led_state_off_long_press_cb();
				break;
			case KEY_STATE_CONT_PRESS:
				led_state_off_cont_press_cb();
				break;
			case KEY_STATE_RELEASE:
				led_state_off_release_cb();
				break;
			default:
				break;
		}
	}
}

/* key action @ led state day */

static void led_state_day_short_press_cb()
{
	m_led_para.mState++;
	led_update_night_bright();
	led_indicate_night();
	led_prepare_to_save();
}

static void led_state_day_long_press_cb()
{
	led_update_day_status();
}

static void led_state_day_cont_press_cb()
{
	if(led_run_para.mDr)
	{
		increase(&m_led_para.all_bright, LED_DELTA_TOUCH, MAX_LED_BRIGHT);	
	}
	else
	{
		decrease(&m_led_para.all_bright, LED_DELTA_TOUCH, MIN_LED_BRIGHT);
	}
	led_update_day_bright();
}

static void led_state_day_release_cb()
{
	led_prepare_to_save();
}

static void led_state_day_cb(uint8_t key, key_state_t state)
{
	if(key == KEY_TOUCH)
	{
		switch(state)
		{
			case KEY_STATE_SHORT_PRESS:
				led_state_day_short_press_cb();
				break;
			case KEY_STATE_LONG_PRESS:
				led_state_day_long_press_cb();
				break;
			case KEY_STATE_CONT_PRESS:
				led_state_day_cont_press_cb();
				break;
			case KEY_STATE_RELEASE:
				led_state_day_release_cb();
				break;
			default:
				break;
		}
	}
}

/* key action @ led state night */

static void led_state_night_short_press_cb()
{
	m_led_para.mState++;
	if(m_led_para.last_mode == BLE_MODE_PRO)
	{
		m_led_para.ble_para.mMode = BLE_MODE_PRO;
	}
	else
	{
		m_led_para.ble_para.mMode = BLE_MODE_AUTO;
	}
	led_indicate_ble();
	led_prepare_to_save();
}

static void led_state_night_long_press_cb()
{
	led_update_night_status();
}

static void led_state_night_cont_press_cb()
{
	if(led_run_para.mNr)
	{
		increase(&m_led_para.blue_bright, LED_DELTA_TOUCH, MAX_LED_BRIGHT);
	}
	else
	{
		decrease(&m_led_para.blue_bright, LED_DELTA_TOUCH, MIN_LED_BRIGHT);
	}
	led_update_night_bright();
}

static void led_state_night_release_cb()
{
	led_prepare_to_save();
}

static void led_state_night_cb(uint8_t key, key_state_t state)
{
	if(key == KEY_TOUCH)
	{
		switch(state)
		{
			case KEY_STATE_SHORT_PRESS:
				led_state_night_short_press_cb();
				break;
			case KEY_STATE_LONG_PRESS:
				led_state_night_long_press_cb();
				break;
			case KEY_STATE_CONT_PRESS:
				led_state_night_cont_press_cb();
				break;
			case KEY_STATE_RELEASE:
				led_state_night_release_cb();
			default:
				break;
		}
	}
}

/* key action @ led state ble */

static void led_state_ble_short_press_cb()
{
	m_led_para.mState++;
	led_turnoff();
	led_indicate_off();
	led_prepare_to_save();
}

static void led_state_ble_long_press_cb() { }

static void led_state_ble_cont_press_cb() { }

static void led_state_ble_release_cb() { }

static void led_state_ble_cb(uint8_t key, key_state_t state)
{
	if(key == KEY_TOUCH)
	{
		switch(state)
		{
			case KEY_STATE_SHORT_PRESS:
				led_state_ble_short_press_cb();
				break;
			case KEY_STATE_LONG_PRESS:
				led_state_ble_long_press_cb();
				break;
			case KEY_STATE_CONT_PRESS:
				led_state_ble_cont_press_cb();
				break;
			case KEY_STATE_RELEASE:
				led_state_ble_release_cb();
			default:
				break;
		}
	}
}

void led_touch_cb(key_value_t key, key_state_t state)
{
	led_state_cb[m_led_para.mState](key, state);
}
#endif

#ifdef	DYNAMIC_ENABLE
static void led_cloud1_init()
{
	dynamic_chn = 0x0D;
	dynamic_rise = 0x09;
	dynamic_min[0] = 0;
	dynamic_max[0] = 250;
	dynamic_min[2] = 0;
	dynamic_max[2] = 250;
	dynamic_min[3] = 125;
	dynamic_max[3] = 250;
	current_bright[1] = 250;
	dynamic_period = 2000;
}

static void led_cloud2_init()
{
	dynamic_chn = 0x0E;
	dynamic_rise = 0x08;
	dynamic_min[1] = 0;
	dynamic_max[1] = 125;
	dynamic_min[2] = 0;
	dynamic_max[2] = 250;
	dynamic_min[3] = 125;
	dynamic_max[3] = 250;
	current_bright[0] = 0;
	dynamic_period = 2000;
}

static void led_cloud3_init()
{
	dynamic_chn = 0x07;
	dynamic_rise = 0x01;
	dynamic_min[0] = 0;
	dynamic_max[0] = 250;
	dynamic_min[1] = 0;
	dynamic_max[1] = 125;
	dynamic_min[2] = 0;
	dynamic_max[2] = 250;
	current_bright[3] = 1000;
	dynamic_period = 2000;
}

static void led_cloud4_init()
{
	dynamic_chn = 0x09;
	dynamic_rise = 0x00;
	dynamic_min[0] = 100;
	dynamic_max[0] = 160;
	dynamic_min[3] = 125;
	dynamic_max[3] = 250;
	current_bright[1] = 0;
	current_bright[2] = 0;
	dynamic_period = 2000;
}

static void led_moon1_init()
{
	dynamic_chn = 0x04;
	dynamic_rise = 0x00;
	dynamic_min[2] = 75;
	dynamic_max[2] = 250;
	current_bright[0] = 0;
	current_bright[1] = 0;
	current_bright[3] = 0;
	dynamic_period = 2000;
}

static void led_moon2_init()
{
	dynamic_chn = 0x04;
	dynamic_rise = 0x00;
	dynamic_min[2] = 25;
	dynamic_max[2] = 100;
	current_bright[0] = 0;
	current_bright[1] = 0;
	current_bright[3] = 0;
	dynamic_period = 2000;
}

static void led_moon3_init()
{
	dynamic_chn = 0x04;
	dynamic_rise = 0x00;
	dynamic_min[2] = 100;
	dynamic_max[2] = 250;
	current_bright[0] = 0;
	current_bright[1] = 0;
	current_bright[3] = 100;
	dynamic_period = 2000;
}

static void led_sunrs_init()
{
	global_interrupt_disable();
	dynamic_count = 0;
	dynamic_run_pause = false;
	dynamic_run_mode = DYNAMIC_SUNRS;
	bool flag = false;
	for(uint8_t i = 0; i < CHANNEL_COUNT; i++)
	{
		if(current_bright[i] > 0)
		{
			flag = true;
			break;
		}
	}
	if(m_led_para.ble_para.manual_para.mOn && flag)
	{
		m_led_para.ble_para.manual_para.mOn = 0;
		for(uint8_t i = 0; i < CHANNEL_COUNT; i++)
		{
			target_bright[i] = 0;
			dynamic_min[i] = 0;
			dynamic_max[i] = current_bright[i]>>2;
		}
		dynamic_rise = 0x00;
	}
	else
	{
		m_led_para.ble_para.manual_para.mOn = 1;
		for(uint8_t i = 0; i < CHANNEL_COUNT; i++)
		{
			m_led_para.ble_para.manual_para.mBright[i] = MAX_LED_BRIGHT;
			target_bright[i] = MAX_LED_BRIGHT;
			dynamic_min[i] = 0;
			dynamic_max[i] = 250;
		}
		dynamic_rise = 0x0F;
	}
	dynamic_chn = 0x0F;
	dynamic_period = 31250;
	global_interrupt_enable();
}

static void led_thunder1_init()
{
	dynamic_chn = 0x00;
	current_bright[0] = 0;
	current_bright[1] = 0;
	current_bright[2] = 250;
	current_bright[3] = 250;
	dynamic_period = 500;
}

static void led_thunder1_process()
{
	dynamic_chn = 0x00;
	current_bright[2] = 250;
	switch(dynamic_state)
	{
		case 0:
			current_bright[0] = 0;
			current_bright[1] = 0;
			current_bright[3] = 200;
			dynamic_period = 500;
			break;
		case 1:
			current_bright[0] = 0;
			current_bright[1] = 0;
			current_bright[3] = 200;
			dynamic_period = 35;
			break;
		case 2:
			current_bright[0] = 0;
			current_bright[1] = 0;
			current_bright[3] = 300;
			dynamic_period = 30;
			break;
		case 3:
			current_bright[0] = 450;
			current_bright[1] = 450;
			current_bright[3] = 500;
			dynamic_period = 30;
			break;
		case 4:
			current_bright[0] = 0;
			current_bright[1] = 0;
			current_bright[3] = 250;
			dynamic_period = 30;
			break;
		case 5:
			current_bright[0] = 0;
			current_bright[1] = 0;
			current_bright[3] = 0;
			dynamic_period = 250;
			break;
		case 6:
			current_bright[0] = 0;
			current_bright[1] = 0;
			current_bright[3] = 300;
			dynamic_period = 35;
			break;
		case 7:
			current_bright[0] = 450;
			current_bright[1] = 450;
			current_bright[3] = 400;
			dynamic_period = 20;
			break;
		case 8:
			current_bright[0] = 0;
			current_bright[1] = 0;
			current_bright[3] = 250;
			dynamic_period = 20;
			break;
		case 9:
			current_bright[0] = 0;
			current_bright[1] = 0;
			current_bright[3] = 200;
			dynamic_period = 20;
			break;
		case 10:
			current_bright[0] = 0;
			current_bright[1] = 0;
			current_bright[3] = 0;
			dynamic_period = 2500;
			break;
		default:
			break;
	}
}

static void led_thunder2_init()
{
	dynamic_chn = 0x0C;
	dynamic_rise = 0x04;
	dynamic_min[2] = 25;
	dynamic_max[2] = 53;
	dynamic_min[3] = 3;
	dynamic_max[3] = 25;
	current_bright[0] = 0;
	current_bright[1] = 0;
	dynamic_period = 80;
}

static void led_thunder2_process()
{
	current_bright[0] = 0;
	current_bright[1] = 0;
	switch(dynamic_state)
	{
		case 0:
		case 15:
		case 30:
		case 45:
		case 60:
			dynamic_chn = 0x0C;
			dynamic_rise = 0x04;
			dynamic_min[2] = 25;
			dynamic_max[2] = 53;
			dynamic_min[3] = 3;
			dynamic_max[3] = 25;
			dynamic_period = 80;
			break;
		case 1:
		case 16:
		case 31:
		case 46:
		case 61:
			dynamic_chn = 0x04;
			dynamic_rise = 0x04;
			dynamic_min[2] = 53;
			dynamic_max[2] = 60;
			current_bright[3] = 0;
			dynamic_period = 20;
			break;
		case 2:
		case 17:
		case 32:
		case 47:
		case 62:
			dynamic_chn = 0x04;
			dynamic_rise = 0x04;
			dynamic_min[2] = 60;
			dynamic_max[2] = 74;
			current_bright[3] = 16;
			dynamic_period = 40;
			break;
		case 3:
		case 18:
		case 33:
		case 48:
		case 63:
			dynamic_chn = 0x04;
			dynamic_rise = 0x04;
			dynamic_min[2] = 74;
			dynamic_max[2] = 123;
			current_bright[3] = 0;
			dynamic_period = 140;
			break;
		case 4:
		case 19:
		case 34:
		case 49:
		case 64:
			dynamic_chn = 0x00;
			current_bright[2] = 492;
			current_bright[3] = 250;
			dynamic_period = 10;
			break;
		case 5:
		case 20:
		case 35:
		case 50:
		case 65:
			dynamic_chn = 0x00;
			current_bright[2] = 200;
			current_bright[3] = 100;
			dynamic_period = 10;
			break;
		case 6:
		case 21:
		case 36:
		case 51:
		case 66:
			dynamic_chn = 0x00;
			current_bright[2] = 100;
			current_bright[3] = 0;
			dynamic_period = 10;
			break;
		case 7:
		case 22:
		case 37:
		case 52:
		case 67:
			dynamic_chn = 0x00;
			current_bright[2] = 50;
			current_bright[3] = 76;
			dynamic_period = 20;
			break;
		case 8:
		case 23:
		case 38:
		case 53:
		case 68:
			dynamic_chn = 0x00;
			current_bright[2] = 0;
			current_bright[3] = 0;
			dynamic_period = 10;
			break;
		case 9:
		case 24:
		case 39:
		case 54:
		case 69:
			dynamic_chn = 0x0C;
			dynamic_rise = 0x00;
			dynamic_min[2] = 25;
			dynamic_max[2] = 75;
			dynamic_min[3] = 0;
			dynamic_max[3] = 25;
			dynamic_period = 80;
			break;
		case 10:
		case 25:
			dynamic_chn = 0x00;
			dynamic_period = 500;
			break;
		case 55:
		case 70:
			dynamic_chn = 0x00;
			dynamic_period = 1500;
			break;
		case 40:
			dynamic_chn = 0x00;
			dynamic_period = 2750;
			break;
		case 11:
		case 26:
		case 41:
		case 56:
		case 71:
			dynamic_chn = 0x00;
			current_bright[2] = 180;
			current_bright[3] = 150;
			dynamic_period = 30;
			break;
		case 12:
		case 27:
		case 42:
		case 57:
		case 72:
			dynamic_chn = 0x00;
			current_bright[2] = 0;
			current_bright[3] = 0;
			dynamic_period = 10;
			break;
		case 13:
		case 28:
		case 43:
		case 58:
		case 73:
			dynamic_chn = 0x0C;
			dynamic_rise = 0x00;
			dynamic_min[2] = 25;
			dynamic_max[2] = 45;
			dynamic_min[3] = 0;
			dynamic_max[3] = 43;
			dynamic_period = 100;
			break;
		case 14:
		case 44:
		case 59:
			dynamic_chn = 0x00;
			dynamic_period = 600;
			break;
		case 29:
			dynamic_chn = 0x00;
			dynamic_period = 1000;
			break;
		case 74:
			dynamic_chn = 0x00;
			dynamic_period = 500;
			break;
		default:
			break;
	}
}

static void led_thunder3_init()
{
	dynamic_chn = 0x0F;
	dynamic_rise = 0x06;
	dynamic_min[0] = 0;
	dynamic_max[0] = 250;
	dynamic_min[1] = 0;
	dynamic_max[1] = 125;
	dynamic_min[2] = 0;
	dynamic_max[2] = 250;
	dynamic_min[3] = 175;
	dynamic_max[3] = 250;
	dynamic_period = 1000;
}

static void led_thunder3_process()
{
	switch(dynamic_state)
	{
		case 0:
		case 2:
			dynamic_chn = 0x0F;
			dynamic_rise = 0x06;
			dynamic_min[0] = 0;
			dynamic_max[0] = 250;
			dynamic_min[1] = 0;
			dynamic_max[1] = 125;
			dynamic_min[2] = 0;
			dynamic_max[2] = 250;
			dynamic_min[3] = 175;
			dynamic_max[3] = 250;
			dynamic_period = 1000;
			break;
		case 1:
		case 3:
			dynamic_chn = 0x0F;
			dynamic_rise = 0x09;
			dynamic_min[0] = 0;
			dynamic_max[0] = 250;
			dynamic_min[1] = 0;
			dynamic_max[1] = 125;
			dynamic_min[2] = 0;
			dynamic_max[2] = 250;
			dynamic_min[3] = 175;
			dynamic_max[3] = 250;
			dynamic_period = 1000;
			break;
		case 4:
			dynamic_chn = 0x0F;
			dynamic_rise = 0x06;
			dynamic_min[0] = 0;
			dynamic_max[0] = 250;
			dynamic_min[1] = 0;
			dynamic_max[1] = 125;
			dynamic_min[2] = 0;
			dynamic_max[2] = 250;
			dynamic_min[3] = 125;
			dynamic_max[3] = 250;
			dynamic_period = 1000;
			break;
		case 5:
			dynamic_chn = 0x0A;
			dynamic_rise = 0x00;
			dynamic_min[1] = 0;
			dynamic_max[1] = 125;
			dynamic_min[3] = 0;
			dynamic_max[3] = 125;
			current_bright[0] = 0;
			current_bright[2] = 1000;
			dynamic_period = 1000;
			break;
		case 6:
			dynamic_chn = 0x04;
			dynamic_rise = 0x00;
			dynamic_min[2] = 63;
			dynamic_max[2] = 250;
			current_bright[0] = 0;
			current_bright[1] = 0;
			current_bright[3] = 0;
			dynamic_period = 1000;
			break;
		case 7:
			dynamic_chn = 0x08;
			dynamic_rise = 0x08;
			dynamic_min[3] = 0;
			dynamic_max[3] = 113;
			current_bright[0] = 0;
			current_bright[1] = 0;
			current_bright[2] = 250;
			dynamic_period = 150;
			break;
		case 8:
			dynamic_chn = 0x07;
			dynamic_rise = 0x07;
			dynamic_min[0] = 110;
			dynamic_max[0] = 125;
			dynamic_min[1] = 110;
			dynamic_max[1] = 125;
			dynamic_min[2] = 110;
			dynamic_max[2] = 125;
			current_bright[3] = 250;
			dynamic_period = 15;
			break;
		case 9:
			dynamic_chn = 0x07;
			dynamic_rise = 0x00;
			dynamic_min[0] = 110;
			dynamic_max[0] = 125;
			dynamic_min[1] = 110;
			dynamic_max[1] = 125;
			dynamic_min[2] = 110;
			dynamic_max[2] = 125;
			current_bright[3] = 250;
			dynamic_period = 15;
			break;
		case 10:
			dynamic_chn = 0x00;
			current_bright[0] = 0;
			current_bright[1] = 0;
			current_bright[2] = 0;
			current_bright[3] = 0;
			dynamic_period = 30;
			break;
		case 11:
			dynamic_chn = 0x00;
			current_bright[0] = 0;
			current_bright[1] = 0;
			current_bright[2] = 0;
			current_bright[3] = 300;
			dynamic_period = 30;
			break;
		case 12:
			dynamic_chn = 0x07;
			dynamic_rise = 0x07;
			dynamic_min[0] = 75;
			dynamic_max[0] = 90;
			dynamic_min[1] = 75;
			dynamic_max[1] = 90;
			dynamic_min[2] = 75;
			dynamic_max[2] = 90;
			current_bright[3] = 250;
			dynamic_period = 30;
			break;
		case 13:
			dynamic_chn = 0x00;
			current_bright[0] = 0;
			current_bright[1] = 0;
			current_bright[2] = 250;
			current_bright[3] = 100;
			dynamic_period = 15;
			break;
		case 14:
			dynamic_chn = 0x00;
			current_bright[0] = 0;
			current_bright[1] = 0;
			current_bright[2] = 250;
			current_bright[3] = 0;
			dynamic_period = 3000;
			break;
		case 15:
			dynamic_chn = 0x0D;
			dynamic_rise = 0x0D;
			dynamic_min[0] = 0;
			dynamic_max[0] = 250;
			dynamic_min[2] = 63;
			dynamic_max[2] = 125;
			dynamic_min[3] = 0;
			dynamic_max[3] = 63;
			current_bright[1] = 0;
			dynamic_period = 1000;
			break;
		case 16:
			dynamic_chn = 0x0C;
			dynamic_rise = 0x08;
			dynamic_min[2] = 0;
			dynamic_max[2] = 125;
			dynamic_min[3] = 63;
			dynamic_max[3] = 250;
			current_bright[0] = 1000;
			current_bright[1] = 0;
			dynamic_period = 1000;
			break;
		default:
			break;
	}
}

static void led_allcolor_init()
{
	dynamic_chn = 0x01;
	dynamic_rise = 0x00;
	dynamic_min[0] = 75;
	dynamic_max[0] = 175;
	current_bright[1] = 0;
	current_bright[2] = 1000;
	current_bright[3] = 100;
	dynamic_period = 2000;
}

static void led_allcolor_process()
{
	dynamic_period = 2000;
	switch(dynamic_state)
	{
		case 0:
			dynamic_chn = 0x01;
			dynamic_rise = 0x00;
			dynamic_min[0] = 75;
			dynamic_max[0] = 175;
			current_bright[1] = 0;
			current_bright[2] = 1000;
			current_bright[3] = 100;
			break;
		case 1:
			dynamic_chn = 0x03;
			dynamic_rise = 0x03;
			dynamic_min[0] = 75;
			dynamic_max[0] = 175;
			dynamic_min[1] = 0;
			dynamic_max[1] = 175;
			current_bright[2] = 1000;
			current_bright[3] = 100;
			break;
		case 2:
			dynamic_chn = 0x0F;
			dynamic_rise = 0x08;
			dynamic_min[0] = 0;
			dynamic_max[0] = 175;
			dynamic_min[1] = 0;
			dynamic_max[1] = 175;
			dynamic_min[2] = 0;
			dynamic_max[2] = 250;
			dynamic_min[3] = 25;
			dynamic_max[3] = 56;
			break;
		case 3:
			dynamic_chn = 0x0C;
			dynamic_rise = 0x04;
			dynamic_min[2] = 0;
			dynamic_max[2] = 250;
			dynamic_min[3] = 25;
			dynamic_max[3] = 56;
			current_bright[0] = 0;
			current_bright[1] = 0;
			break;
		case 4:
			dynamic_chn = 0x01;
			dynamic_rise = 0x01;
			dynamic_min[0] = 0;
			dynamic_max[0] = 175;
			current_bright[1] = 0;
			current_bright[2] = 1000;
			current_bright[3] = 100;
			break;
		default:
			break;
	}
}

static void led_dynamic_process()
{
	if(dynamic_run_pause)
	{
		return;
	}
	if(dynamic_count < dynamic_period)
	{
		dynamic_count++;
	}
	else
	{
		dynamic_count = 0;
		if(dynamic_run_mode == DYNAMIC_SUNRS)
		{
			dynamic_run_mode = DYNAMIC_NONE;
			return;
		}
		switch( dynamic_run_mode )
		{
			case DYNAMIC_THUNDER1:
				dynamic_state++;
				if(dynamic_state > THUNDER1_STATE_MAX)
				{
					dynamic_state = 1;
				}
				led_thunder1_process();
				break;
			case DYNAMIC_THUNDER2:
				dynamic_state++;
				if(dynamic_state > THUNDER2_STATE_MAX)
				{
					dynamic_state = 0;
				}
				led_thunder2_process();
				break;
			case DYNAMIC_THUNDER3:
				dynamic_state++;
				if(dynamic_state > THUNDER3_STATE_MAX)
				{
					dynamic_state = 0;
				}
				led_thunder3_process();
				break;
			case DYNAMIC_ALLCOLOR:
				dynamic_state++;
				if(dynamic_state > ALLCOLOR_STATE_MAX)
				{
					dynamic_state = 0;
				}
				led_allcolor_process();
				break;
			case DYNAMIC_CLOUD1:
			case DYNAMIC_CLOUD2:
			case DYNAMIC_CLOUD3:
			case DYNAMIC_CLOUD4:
			case DYNAMIC_MOON1:
			case DYNAMIC_MOON2:
			case DYNAMIC_MOON3:
				dynamic_rise ^= dynamic_chn;
				break;
			default:
				break;
		}
	}
	uint16_t temp;
	for(uint8_t i = 0; i < CHANNEL_COUNT; i++)
	{
		if(dynamic_chn&(1<<i))
		{
			temp = 4ul*(dynamic_max[i] - dynamic_min[i])*dynamic_count/dynamic_period;
			if(dynamic_rise&(1<<i))
			{
				current_bright[i] = 4u*dynamic_min[i] + temp;
			}
			else
			{
				current_bright[i] = 4u*dynamic_max[i] - temp;
			}
		}
		led_load_duty[i](current_bright[i]);
	}
}

static bool led_period_dynamic_process(uint16_t ct)
{
	bool flag = false;
	uint8_t week = m_led_para.ble_para.dynamic_para.array[0];
	uint8_t mode = m_led_para.ble_para.dynamic_para.dynamic_mode;
	if(week > 0x80 && mode > DYNAMIC_NONE && mode < DYNAMIC_SUNRS)
	{
		if((week & (1 << rtc_get_week())) != 0x00)
		{
			uint16_t start = m_led_para.ble_para.dynamic_para.start_hour * 60u + m_led_para.ble_para.dynamic_para.start_minute;
			uint16_t end = m_led_para.ble_para.dynamic_para.end_hour * 60u + m_led_para.ble_para.dynamic_para.end_minute;
			if(end >= start)
			{
				if(ct >= start && ct < end)
				{
					flag = true;
				}
			}
			else
			{
				if(ct >= start || ct < end)
				{
					flag = true;
				}
			}
		}
	}
	if(flag == false)
	{
		dynamic_run_mode = DYNAMIC_NONE;
	}
	else if(dynamic_run_mode != m_led_para.ble_para.dynamic_para.dynamic_mode)
	{
		led_dynamic_init(mode);
	}
	return flag;
}

static void led_dynamic_init(uint8_t dyn)
{
	global_interrupt_disable();
	dynamic_count = 0;
	dynamic_state = 0;
	dynamic_run_pause = false;
	dynamic_run_mode = dyn;
	dynamic_func_init[dyn-DYNAMIC_THUNDER1]();
	global_interrupt_enable();
}

bool led_set_dynamic(uint8_t dyn)
{
	if(led_run_para.mFind || led_run_para.mPrev || m_led_para.ble_para.mMode != BLE_MODE_MANUAL)
	{
		return false;
	}
	if(dyn == DYNAMIC_NONE || dyn > DYNAMIC_PAUSE)
	{
		return false;
	}
	if(dyn == DYNAMIC_SUNRS)
	{
		led_sunrs_init();
		m_led_para.ble_para.manual_para.mDyn = DYNAMIC_NONE;
		led_prepare_to_save();
		return true;
	}
	if(m_led_para.ble_para.manual_para.mOn)
	{
		if(dyn > DYNAMIC_NONE && dyn < DYNAMIC_SUNRS)
		{
			led_dynamic_init(dyn);
			m_led_para.ble_para.manual_para.mDyn = dyn;
			led_prepare_to_save();
			return true;
		}
		else if(dyn == DYNAMIC_PAUSE && dynamic_run_mode > DYNAMIC_NONE && dynamic_run_mode < DYNAMIC_SUNRS)
		{
			dynamic_run_pause = !dynamic_run_pause;
			return true;
		}
	}
	return false;
}

void led_set_period_dynamic(const uint8_t * const pbuf)
{
	uint8_t len = sizeof(m_led_para.ble_para.dynamic_para.array);
	for(uint8_t i = 0; i < len; i++)
	{
		m_led_para.ble_para.dynamic_para.array[i] = *(pbuf + i);
	}
	led_prepare_to_save();
}
#endif

/* led flash -> find device */

void led_start_flash()
{
	led_run_para.mFind = 1;
	led_run_para.flash_count = FIND_FLASH_COUNT;
}

static void led_find_device()
{
	static bool toggle = false;
	if(toggle)
	{
		toggle = false;
		led_turnoff();
		if(led_run_para.flash_count > 0)
		{
			led_run_para.flash_count--;
		}
		if(led_run_para.flash_count == 0)
		{
			led_run_para.mFind = 0;
		}
	}
	else
	{
		toggle = true;
		led_turnon_max();
	}
}

/* led preview */

void led_start_preview()
{
	led_run_para.mPrev = 1;
	led_run_para.prev_count = PREVIEW_COUNT;
}

void led_stop_preview()
{
	led_run_para.mPrev = 0;
	led_run_para.prev_count = 0;
}

static void led_preview()
{
	if(led_run_para.prev_count > 0)
	{
		led_run_para.prev_count--;
	}
	if(led_run_para.prev_count == 0)
	{
		led_run_para.mPrev = 0;
	}
}

/* led save para */

static void led_prepare_to_save()
{
	led_run_para.mSave = 1;
	led_run_para.save_delay_count = PARA_SAVE_DELAY;
}

static void led_save_para()
{
	if(led_run_para.save_delay_count > 0)
	{
		led_run_para.save_delay_count--;
	}
	if(led_run_para.save_delay_count == 0)
	{
		m_led_para.save_flag = PARA_SAVED_FLAG;
		eeprom_write_buffer(ADDR_LED_PARA, (uint8_t *) &m_led_para, sizeof(m_led_para));
		led_run_para.mSave = 0;
	}
}

void led_second_cb()
{
	uint16_t ct = rtc_get_hour()*60u + rtc_get_minute();
	uint8_t sec = rtc_get_second();
	if(led_run_para.mFind)
	{
		led_find_device();
	}
	else 
	{
#ifdef	TOUCH_ENABLE
		if(m_led_para.mState == LED_STATUS_BLE)
		{
#endif
			if(led_run_para.mPrev)
			{
				led_preview();
			}
#ifdef	DYNAMIC_ENABLE
			else if(m_led_para.ble_para.mMode == BLE_MODE_AUTO || m_led_para.ble_para.mMode == BLE_MODE_PRO)
			{
				if(led_period_dynamic_process(ct) == false)
				{
					if(m_led_para.ble_para.mMode == BLE_MODE_AUTO)
					{
						led_auto_process(ct, sec);
					}
					else if(m_led_para.ble_para.mMode == BLE_MODE_PRO)
					{
						led_pro_process(ct, sec);
					}
				}
			}
#else
			else if(m_led_para.ble_para.mMode == BLE_MODE_AUTO)
			{
				led_auto_process(ct, sec);
			}
			else if(m_led_para.ble_para.mMode == BLE_MODE_PRO)
			{
				led_pro_process(ct, sec);
			}
#endif
#ifdef	TOUCH_ENABLE
		}
#endif
	}
	
	if(led_run_para.mSave)
	{
		led_save_para();
	}
}

bool led_set_mode(uint8_t m)
{
	if(led_run_para.mFind || led_run_para.mPrev)
	{
		return false;
	}
#ifdef	DYNAMIC_ENABLE
	dynamic_run_mode = DYNAMIC_NONE;
	dynamic_run_pause = false;
#endif	
	m_led_para.ble_para.mMode = m;
	if(m != BLE_MODE_AUTO && m != BLE_MODE_PRO)
	{
		if(m_led_para.ble_para.manual_para.mOn)
		{
#ifdef	DYNAMIC_ENABLE
			if(m_led_para.ble_para.manual_para.mDyn > DYNAMIC_NONE && m_led_para.ble_para.manual_para.mDyn < DYNAMIC_SUNRS)
			{
				led_dynamic_init(m_led_para.ble_para.manual_para.mDyn);
			}
			else
			{
#endif
				led_turnon_ramp();
#ifdef	DYNAMIC_ENABLE
			}
#endif
		}
		else
		{
			led_turnoff_ramp();
		}
	}
#ifdef	TOUCH_ENABLE
	else
	{
		m_led_para.last_mode = m;
	}
#endif
	led_prepare_to_save();
	return true;
}

bool led_set_power(bool on)
{
	if(led_run_para.mFind || led_run_para.mPrev || m_led_para.ble_para.mMode != BLE_MODE_MANUAL)
	{
		return false;
	}
#ifdef	DYNAMIC_ENABLE
	dynamic_run_mode = DYNAMIC_NONE;
	dynamic_run_pause = false;
#endif	
	m_led_para.ble_para.manual_para.mOn = on;
	if(on)
	{
#ifdef	DYNAMIC_ENABLE
		if(m_led_para.ble_para.manual_para.mDyn > DYNAMIC_NONE && m_led_para.ble_para.manual_para.mDyn < DYNAMIC_SUNRS)
		{
			led_dynamic_init(m_led_para.ble_para.manual_para.mDyn);
		}
		else
		{
#endif
			led_turnon_ramp();
#ifdef	DYNAMIC_ENABLE
		}
#endif
	}
	else
	{
		led_turnoff_ramp();
	}
	led_prepare_to_save();
	return true;
}

bool led_set_bright(const uint8_t * const pbuf)
{
	if(led_run_para.mFind || led_run_para.mPrev || m_led_para.ble_para.mMode != BLE_MODE_MANUAL || m_led_para.ble_para.manual_para.mOn == 0)
	{
		return false;
	}
#ifdef	DYNAMIC_ENABLE
	dynamic_run_mode = DYNAMIC_NONE;
	dynamic_run_pause = false;
	m_led_para.ble_para.manual_para.mDyn = DYNAMIC_NONE;
#endif	
	for(uint8_t i = 0; i < CHANNEL_COUNT; i++)
	{
		uint16_t val = (*(pbuf + 2 * i)) << 8 | (*(pbuf + 2 * i + 1));
		if(val <= MAX_LED_BRIGHT)
		{
			m_led_para.ble_para.manual_para.mBright[i] = val;
			target_bright[i] = val;
		}
	}
	led_prepare_to_save();
	return true;
}

bool led_set_custom(uint8_t idx)
{
//	if(led_run_para.mFind || led_run_para.mPrev || m_led_para.ble_para.mMode != BLE_MODE_MANUAL )
//	{
//		return false;
//	}
#ifdef	DYNAMIC_ENABLE
	if(dynamic_run_mode > DYNAMIC_NONE && dynamic_run_mode < DYNAMIC_PAUSE)
	{
		return false;
	}
#endif
	if(m_led_para.ble_para.manual_para.mOn && idx < CUSTOM_COUNT)
	{
		for(uint8_t i = 0; i < CHANNEL_COUNT; i++)
		{
			m_led_para.ble_para.manual_para.mCustomBright[idx][i] = m_led_para.ble_para.manual_para.mBright[i]/10;
		}
		led_prepare_to_save();
		return true;
	}
	return false;
}

bool led_set_cycle(const uint8_t * const pbuf)
{
//	if(led_run_para.mFind || led_run_para.mPrev || m_led_para.ble_para.mMode != BLE_MODE_AUTO)
//	{
//		return false;
//	}
	uint8_t len = sizeof(m_led_para.ble_para.auto_para.array);
	for(uint8_t i = 0; i < len; i++)
	{
		m_led_para.ble_para.auto_para.array[i] = *(pbuf+i);
	}
	led_prepare_to_save();
	return true;
}

bool led_set_pro(const uint8_t * const pbuf)
{
//	if(led_run_para.mFind || led_run_para.mPrev || m_led_para.ble_para.mMode != BLE_MODE_PRO)
//	{
//		return false;
//	}
	uint8_t len = (*pbuf)*(2+CHANNEL_COUNT)+1;
	for(uint8_t i = 0; i < len; i++)
	{
		m_led_para.ble_para.pro_para.array[i] = *(pbuf+i);
	}
	led_prepare_to_save();
	return true;
}

bool led_increase(uint8_t chn, uint8_t delt)
{
	if(led_run_para.mFind || led_run_para.mPrev || m_led_para.ble_para.mMode != BLE_MODE_MANUAL || m_led_para.ble_para.manual_para.mOn == 0 || chn >= CHANNEL_COUNT)
	{
		return false;
	}
#ifdef	DYNAMIC_ENABLE
	if(dynamic_run_mode > DYNAMIC_NONE)
	{
		return false;
	}
#endif
	increase(&m_led_para.ble_para.manual_para.mBright[chn], delt, MAX_LED_BRIGHT );
	target_bright[chn] = m_led_para.ble_para.manual_para.mBright[chn];
	led_prepare_to_save();
	return true;
}

bool led_decrease(uint8_t chn, uint8_t delt)
{
	if(led_run_para.mFind || led_run_para.mPrev || m_led_para.ble_para.mMode != BLE_MODE_MANUAL || m_led_para.ble_para.manual_para.mOn == 0 || chn >= CHANNEL_COUNT)
	{
		return false;
	}
#ifdef	DYNAMIC_ENABLE
	if(dynamic_run_mode > DYNAMIC_NONE)
	{
		return false;
	}
#endif
	decrease(&m_led_para.ble_para.manual_para.mBright[chn], delt, 0);
	target_bright[chn] = m_led_para.ble_para.manual_para.mBright[chn];
	led_prepare_to_save();
	return true;
}

bool led_set_preview(const uint8_t * const pbuf)
{
	if(led_run_para.mFind || m_led_para.ble_para.mMode == BLE_MODE_MANUAL)
	{
		return false;
	}
#ifdef	DYNAMIC_ENABLE
	dynamic_run_mode = DYNAMIC_NONE;
	dynamic_run_pause = false;
#endif
	for(uint8_t i = 0; i < CHANNEL_COUNT; i++)
	{
		uint16_t val = (*(pbuf + 2 * i)) << 8 | (*(pbuf + 2 * i + 1));
		if(val <= MAX_LED_BRIGHT)
		{
			target_bright[i] = val;
			current_bright[i] = val;
		}
	}
	return true;
}

void led_set_time(const uint8_t* ptime)
{
	rtc_set(ptime);
#ifdef	TOUCH_ENABLE
	if(m_led_para.ble_para.mMode == BLE_MODE_MANUAL)
	{
		if(m_led_para.ble_para.manual_para.mOn)
		{
			led_turnon_ramp();
		}
		else
		{
			led_turnoff_ramp();
		}
	}
	m_led_para.mState = LED_STATUS_BLE;
	led_indicate_ble();
	led_prepare_to_save();
#endif
}