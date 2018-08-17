#include "app_util.h"

void increase(uint16_t * const psrc, const uint8_t delt, const uint16_t max)
{
	if((*psrc) + delt < max)
	{
		(*psrc) += delt;
	}
	else
	{
		(*psrc) = max;
	}
}

void decrease(uint16_t * const psrc, const uint8_t delt, const uint16_t min)
{
	if((*psrc) > min + delt)
	{
		(*psrc) -= delt;
	}
	else
	{
		(*psrc) = min;
	}
}
