#pragma once
#include <stdint.h>
#include "..\interfaces\InterfaceSerialRepository.h"
class ProgMemRepository
{
public:
	ProgMemRepository();
	virtual void sendAtCommand(uint16_t index, InterfaceSerialRepository* repo);
private:
	virtual uint16_t getStringLength(uint16_t index);
	virtual void fillStringBuffer(char buffer[], uint16_t length, uint16_t index);

};

