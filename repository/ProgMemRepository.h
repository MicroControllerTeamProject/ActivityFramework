#pragma once
#include <stdint.h>
class ProgMemRepository
{
public:
	ProgMemRepository();
	virtual uint16_t getStringLength(uint16_t index);
	virtual void fillStringBuffer(char buffer[], uint16_t length, uint16_t index);
};

