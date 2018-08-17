#include "app_rtc.h"

typedef struct{
	unsigned fSec : 1;
	unsigned fMin : 1;
	unsigned fHour : 1;
	unsigned fWeek : 1;
	unsigned fDay : 1;
	unsigned fMon : 1;
	unsigned fYear : 1;
	unsigned : 1;
}rtc_status_t;

#define BASE_YEAR               2000
#define NORMAL_YEAR_FEBRUARY    28
#define LEAP_YEAR_FEBRUARY      29

uint8_t MONTH_DAY[12] = {31, NORMAL_YEAR_FEBRUARY, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
static date_time_t m_current_time;
static rtc_status_t rtc_status;

static bool rtc_is_leap_year(uint16_t year)
{
	if((year & 0x03) == 0)
	{
		if(year % 100 == 0)
		{
			if(year % 400 == 0)
			{
				return true;
			}
		}
		else
		{
			return true;
		}
	}
	return false;
}

void rtc_init()
{
	m_current_time.year = 0;
	m_current_time.month = 1;
	m_current_time.day = 1;
	m_current_time.week = 0;
	m_current_time.hour = 0;
	m_current_time.minute = 0;
	m_current_time.second = 0;
}

void rtc_process()
{
	m_current_time.second++;
	if(m_current_time.second >= 60)
	{
		m_current_time.second = 0;
		m_current_time.minute++;
		if(m_current_time.minute >= 60)
		{
			m_current_time.minute = 0;
			m_current_time.hour++;
			if(m_current_time.hour >= 24)
			{
				m_current_time.hour = 0;
				m_current_time.day++;
				m_current_time.week++;
				if(m_current_time.week > 6)
				{
					m_current_time.week = 0;
				}
				if(rtc_is_leap_year(m_current_time.year + BASE_YEAR))
				{
					MONTH_DAY[1] = LEAP_YEAR_FEBRUARY;
				}
				else
				{
					MONTH_DAY[1] = NORMAL_YEAR_FEBRUARY;
				}
				if(m_current_time.month > 12 || m_current_time.month == 0)
				{
					m_current_time.month = 1;
				}
				if(m_current_time.day > MONTH_DAY[m_current_time.month - 1])
				{
					m_current_time.day = 1;
					m_current_time.month++;
					if(m_current_time.month > 12)
					{
						m_current_time.month = 1;
						m_current_time.year++;
					}
				}
			}
		}
	}
	rtc_status.fSec = 1;
}

bool rtc_second_ready()
{
	if(rtc_status.fSec)
	{
		rtc_status.fSec = 0;
		return true;
	}
	return false;
}

void rtc_set(const uint8_t *ptime)
{
	global_interrupt_disable();
	for(uint8_t i = 0; i < 7; i++)
	{
		m_current_time.array[i] = *ptime++;
	}
	global_interrupt_enable();
}

uint8_t rtc_get_year()
{
	return m_current_time.year;
}

uint8_t rtc_get_month()
{
	return m_current_time.month;
}

uint8_t rtc_get_day()
{
	return m_current_time.day;
}

uint8_t rtc_get_week()
{
	return m_current_time.week;
}

uint8_t rtc_get_hour()
{
	return m_current_time.hour;
}

uint8_t rtc_get_minute()
{
	return m_current_time.minute;
}

uint8_t rtc_get_second()
{
	return m_current_time.second;
}