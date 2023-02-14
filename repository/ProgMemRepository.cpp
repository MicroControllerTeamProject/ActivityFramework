#include "ProgMemRepository.h"
#include <avr/pgmspace.h>
#include <../externalFiles/SIM_AT_COMMADS.h>

using namespace progmem::strings::atCommands::simModule;

ProgMemRepository::ProgMemRepository(){
}

uint16_t ProgMemRepository::getStringLength(uint16_t index){
	return strlen_P(simCommands + index);
}

void ProgMemRepository::fillStringBuffer(char buffer[], uint16_t length, uint16_t index){
	for (int i = 0; i < length; i++)
	{
		char charInString = pgm_read_word(&simCommands[index + i]);
		buffer[i] = charInString;
	}
	buffer[length] = '\0';
}



