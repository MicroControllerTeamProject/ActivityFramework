#pragma once
#include <stdint.h>
#include <avr/pgmspace.h>
#include "..\interfaces\InterfaceSerialRepository.h"
class SimProgMemRepository
{
public:
	SimProgMemRepository();
	/*virtual void sendAtCommand(uint16_t index, InterfaceSerialRepository* repo);*/
	void getAtCommand(uint16_t index, char* atCommandbuffer, uint8_t atCommandBufferLenght);
	void getSmsToFind(uint16_t index, char* responseDatabuffer, uint8_t responseDatabufferLenght);
	uint16_t getProgMemSmsToFindLenght(uint16_t stringIndex);
	uint16_t getAtCommandIndexLengthString(uint16_t stringIndex);
private:
	virtual uint16_t getStringLength(PROGMEM const char simCommands[], uint16_t index);
	virtual void fillStringBuffer(char buffer[], uint16_t length, uint16_t index, PROGMEM const char preogMemString[]);

};

