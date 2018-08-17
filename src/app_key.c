#include "app_key.h"

key_func_t key_func;

void key_init(key_func_t cb)
{
	key_func = cb;
}

static uint8_t key_read()
{
	static uint8_t trg;
	static uint8_t cont;
	uint8_t dat = (KEY_PORT^0xFF) & KEY_MASK;
	trg = dat & (dat ^ cont);
	cont = dat;
	return( trg ^ cont);
}

static void key_action(key_value_t key, key_state_t state)
{
	if(key_func != NULL)
	{
		key_func(key, state);
	}
}

void key_scan()
{
	static key_value_t last_key = KEY_NONE;
	static uint8_t repeat = 0;
	key_value_t key_value = key_read();
	if(key_value != KEY_NONE)
	{
		if(key_value == last_key)
		{
			repeat++;
			if(repeat == LONG_PRESS_THRESHOLD)
			{
				key_action(key_value, KEY_STATE_LONG_PRESS);
			}
			else if(repeat >= LONG_PRESS_THRESHOLD + CONT_PRESS_INTERVAL)
			{
				repeat = LONG_PRESS_THRESHOLD;
				key_action(key_value, KEY_STATE_CONT_PRESS);
			}
		}
		else
		{
			repeat = 0;
		}
	}
	else
	{
		if(last_key != KEY_NONE)
		{
			if(repeat >= LONG_PRESS_THRESHOLD)
			{
				key_action(last_key, KEY_STATE_RELEASE);
			}
			else
			{
				key_action(last_key, KEY_STATE_SHORT_PRESS);
			}
		}
		repeat = 0;
	}
	last_key = key_value;
}
