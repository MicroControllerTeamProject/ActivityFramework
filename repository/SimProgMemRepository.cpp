#include "SimProgMemRepository.h"

#include "..\externalFiles\SIM_AT_COMMADS.h"
#include "..\externalFiles\SIM_RESPONSE_DATA.h"

#include "Arduino.h"

using namespace progmem::strings::atCommands::simModule;

SimProgMemRepository::SimProgMemRepository(){
}

void SimProgMemRepository::sendAtCommand(uint16_t index,InterfaceSerialRepository* serialRepository)
{
	uint16_t arrayLength = getStringLength(simCommands, index);
	char buffer[arrayLength];
	fillStringBuffer(buffer, arrayLength, index, simCommands);
	Serial.println(buffer);
	serialRepository->print_m(buffer, true);
}

void SimProgMemRepository::getAtCommand(uint16_t index, char* atCommandbuffer, uint8_t atCommandBufferLenght)
{
	fillStringBuffer(atCommandbuffer, atCommandBufferLenght, index, simCommands);
}

uint16_t SimProgMemRepository::getAtCommandIndexLengthString(uint16_t stringIndex)
{
	return getStringLength(simCommands, stringIndex);
}

uint16_t SimProgMemRepository::getProgMemSmsToFindLenght(uint16_t stringIndex)
{
	return getStringLength(simResponseData, stringIndex);
}

void SimProgMemRepository::getSmsToFind(uint16_t index, char* responseDatabuffer,uint8_t responseDatabufferLenght)
{
	fillStringBuffer(responseDatabuffer, responseDatabufferLenght, index, simResponseData);
}

uint16_t SimProgMemRepository::getStringLength(PROGMEM const char preogMemString[],  uint16_t index){
	return strlen_P(preogMemString + index) + 1;
}

void SimProgMemRepository::fillStringBuffer(char buffer[], uint16_t length, uint16_t index, PROGMEM const char preogMemString[]) {
	for (int i = 0; i < length - 1; i++)
	{
		char charInString = pgm_read_word(&preogMemString[index + i]);
		buffer[i] = charInString;
	}
	buffer[length - 1] = '\0';
}



