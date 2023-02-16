#include "ProgMemRepository.h"
#include <avr/pgmspace.h>
#include "..\externalFiles\SIM_AT_COMMADS.h"
#include "Arduino.h"

using namespace progmem::strings::atCommands::simModule;

ProgMemRepository::ProgMemRepository(){
}
//AT+CPMS=\"SM\"
void ProgMemRepository::sendAtCommand(uint16_t index,InterfaceSerialRepository* serialRepository)
{
	/*Serial.println("eco1");*/
	uint16_t arrayLength = getStringLength(index);
	char buffer[arrayLength];
	/*Serial.print("len : "); Serial.println(arrayLength);*/
	fillStringBuffer(buffer, arrayLength, 0);
	//Serial.print("#"); Serial.print(buffer); Serial.println("#");
	serialRepository->print_m(buffer, true);
	/*serialRepository->print_m("AT+CPMS=\"SM\"", true);*/
}

uint16_t ProgMemRepository::getStringLength(uint16_t index){
	return strlen_P(simCommands + index) + 1;
}

void ProgMemRepository::fillStringBuffer(char buffer[], uint16_t length, uint16_t index) {
	for (int i = 0; i < length - 1; i++)
	{
		char charInString = pgm_read_word(&simCommands[index + i]);
		buffer[i] = charInString;
	}
	buffer[length - 1] = '\0';
}



