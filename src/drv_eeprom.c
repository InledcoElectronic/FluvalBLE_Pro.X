#include "drv_eeprom.h"

#define EEPROM_ADDRH		0x70

void eeprom_write(uint8_t addr, uint8_t byte)
{
	bool state = INTCONbits.GIE;
	
	NVMADRH = EEPROM_ADDRH;
	NVMADRL = addr;
	NVMDATL = byte;
	NVMCON1bits.NVMREGS = 1;
	NVMCON1bits.WREN = 1;
	INTCONbits.GIE = 0;
	NVMCON2 = 0x55;
	NVMCON2 = 0xAA;
	NVMCON1bits.WR = 1;
	while(NVMCON1bits.WR);
	NVMCON1bits.WREN = 0;
	
	INTCONbits.GIE = state;
}

uint8_t eeprom_read(uint8_t addr)
{
	NVMADRH = EEPROM_ADDRH;
	NVMADRL = addr;
	NVMCON1bits.NVMREGS = 1;
	NVMCON1bits.RD = 1;
	NOP();	
	NOP();
	return (NVMDATL);
}

void eeprom_write_buffer(uint8_t addr, uint8_t *pbuf, uint8_t len)
{
	for(uint8_t i = len; i > 0; i--)
	{
		eeprom_write(addr++, *pbuf++);
	}
}

void eeprom_read_buffer(uint8_t addr, uint8_t *pbuf, uint8_t len)
{
	for(uint8_t i = len; i > 0; i--)
	{
		*pbuf++ = eeprom_read(addr++);
	}
}
