#include "SimModuleActivity.h"

#ifdef _DEBUG
#include <Arduino.h>
#endif
/// <summary>
/// 
/// </summary>
/// <param name="simModuleRepository"></param>
/// <param name="avrMicroRepository"></param>
/// <param name="listOfSimModuleDevice"></param>
/// <param name="simModuleDevicesNumber"></param>
SimModuleActivity::SimModuleActivity(InterfaceSerialRepository& simModuleRepository,
	AvrMicroRepository& avrMicroRepository, SimModuleDevice** listOfSimModuleDevice,
	uint8_t simModuleDevicesNumber) : DeviceActivity((AvrMicroRepository&)avrMicroRepository, (DigitalPortSensor**)listOfSimModuleDevice, simModuleDevicesNumber) {
	this->avrMicroRepository = &avrMicroRepository;
	this->_simModuleRepository = &simModuleRepository;
	this->_listOfSimModuleDevice = listOfSimModuleDevice;
	this->_simModuleDevicesNumber = simModuleDevicesNumber;
}

SimModuleActivity::SimModuleActivity(InterfaceSerialRepository& simModuleRepository, SimProgMemRepository& simProgMemRepository, AvrMicroRepository& avrMicroRepository, SimModuleDevice* simModuleDevice) : DeviceActivity((AvrMicroRepository&)avrMicroRepository, (DigitalPortSensor*)simModuleDevice)
{
	this->avrMicroRepository = &avrMicroRepository;
	this->_simModuleRepository = &simModuleRepository;
	this->_listOfSimModuleDevice = new SimModuleDevice * [1];
	this->_listOfSimModuleDevice[0] = simModuleDevice;
	this->_simProgMemRepository = &simProgMemRepository;
}

SimModuleActivity::SimModuleActivity() {
}

void SimModuleActivity::makeCall(char buffer[], uint8_t bufferLenght)
{
	
	this->_simModuleRepository->clearBuffer_m();
	uint16_t l= this->_simProgMemRepository->getAtCommandIndexLengthString(93);
	char atdCommand[l];
	this->_simProgMemRepository->getAtCommand(93, atdCommand, l);
	this->_simModuleRepository->print_m(atdCommand);
	this->_simModuleRepository->print_m(this->_listOfSimModuleDevice[0]->getPrefixNumber());
	this->_simModuleRepository->print_m(this->_listOfSimModuleDevice[0]->getPhoneNumber(), true);

	this->avrMicroRepository->delaym(5000);

	buffer[0] = '\0';

	if (this->_simModuleRepository->serial_available() > 0)
	{
		int j = 0;
		int i = 0;
		do {
			j = i++;
			buffer[j] = this->_simModuleRepository->read_m();
		} while ((buffer[j] >= 0 && buffer[j] <= 127) && j < bufferLenght);
		buffer[j] = '\0';
		//Serial.println(F("buffer : ")); Serial.println(buffer);
	}
}

void SimModuleActivity::setIsDisableSms(bool isSmsDisabled)
{
}

bool SimModuleActivity::getIsDisableSms()
{
	return false;
}

void SimModuleActivity::setIsCallDisabled(bool isCallDisabled)
{
}

bool SimModuleActivity::getIsCallDisabled()
{
	return false;
}

void SimModuleActivity::setIsInSleepMode(bool isInSleepMode)
{
}

bool SimModuleActivity::getIsInSleepMode(bool isInSleepMode)
{
}

bool SimModuleActivity::setIsDeviceTurnedOff(bool isTurnedOff, char* deviceUid)
{
	if (isTurnedOff)
	{

		for (int i = 0; i < this->_simModuleDevicesNumber; i++)
		{

			if (strcmp(this->_listOfSimModuleDevice[i]->getUid(), deviceUid) == 0)
			{
				for (int ii = 0; ii < this->_listOfSimModuleDevice[i]->getDigitalPortsNumber(); ii++)
				{
					if (strcmp(this->_listOfSimModuleDevice[i]->getAllDigitalPorts()[ii]->getUid(), "T") == 0)
					{
						this->_listOfSimModuleDevice[i]->setEnableDeviceStatus(true);

						//this->_avrMicroRepository->digitalWrite_m(this->_listOfSimModuleDevice[i]->getAllDigitalPorts()[ii]->getPin(),)
						return true;
					}
				}
			}
		}
	}
	return false;
}

bool SimModuleActivity::getIsDeviceTurnedOff()
{
	return false;
}

uint8_t SimModuleActivity::getNumberOfSmsReceived()
{
	char* response = {};

	char* endOfPointer = {};

	uint8_t messageNumbers = 0;

	this->_simModuleRepository->clearBuffer_m();

	this->_simModuleRepository->print_m("AT+CPMS?", true);

	this->avrMicroRepository->delaym(1000);

	if (this->_simModuleRepository->serial_available() > 0)
	{
		response = this->_simModuleRepository->readString_m();

		//#ifdef _DEBUG
		//		Serial.println(response);
		//#endif

		if (response != nullptr) {

			char secondCommaFound[] = { strchr(response, ',')[2] };

			if (strcmp(secondCommaFound, ",") == 0)
			{
				endOfPointer = ((strchr(response, ',') + 2));
			}
			else {
				endOfPointer = ((strchr(response, ',') + 3));
			}

			messageNumbers = strtol(((strchr(response, ',') + 1)), &endOfPointer, 10);
			//Serial.print("number : "); Serial.println(messageNumbers);
		}
		free(response);
		/*free(endOfPointer);*/
	}
	return messageNumbers;
}


//uint8_t SimModuleActivity::getNumberOfSmsReceived()
//{
//	char* endOfPointer = {};
//
//	uint8_t messageNumbers = 0;
//
//	this->_simModuleRepository->clearBuffer_m();
//
//	sendProgMemAtCommand(34);
//
//	delay(1000);
//
//	uint8_t l = this->_simModuleRepository->get_SS_MAX_RX_BUFF();
//
//	char bufferP[l];
//
//	if (this->_simModuleRepository->serial_available() > 0)
//	{
//		int j = 0;
//
//		int i = 0;
//
//		do {
//			j = i++;
//			bufferP[j] = this->_simModuleRepository->read_m();
//			/*	Serial.print(buffer[j]); Serial.print("   "); Serial.println((buffer[j],10));*/
//		} while ((bufferP[j] >= 0 && bufferP[j] <= 127) && j < l);
//		bufferP[j] = '\0';
//		//Serial.println(F("buffer : ")); Serial.println(buffer);
//	}
//			char secondCommaFound[] = { strchr(bufferP, ',')[2] };
//
//			if (strcmp(secondCommaFound, ",") == 0)
//			{
//				endOfPointer = ((strchr(bufferP, ',') + 2));
//			}
//			else {
//				endOfPointer = ((strchr(bufferP, ',') + 3));
//			}
//			messageNumbers = strtol(((strchr(bufferP, ',') + 1)), &endOfPointer, 10);
//			//Serial.print("number : "); Serial.println(messageNumbers);
//
//	return messageNumbers;
//}

void SimModuleActivity::sendProgMemAtCommand(uint16_t progMemIndex)
{
	uint16_t commProgMemLenght =  this->_simProgMemRepository->getAtCommandIndexLengthString(progMemIndex);
	char commandBuffer[commProgMemLenght];
	this->_simProgMemRepository->getAtCommand(progMemIndex, commandBuffer, commProgMemLenght);
	//Serial.print(F("buffer command : ")); Serial.println(commandBuffer);
	this->_simModuleRepository->print_m(commandBuffer);

}

void SimModuleActivity::enableSmsIncoming()
{
	//AT+CPMS="SM" index 0
	sendProgMemAtCommand(0);
	this->avrMicroRepository->delaym(2000);

	//"AT+CMGF=1" index = 13
	sendProgMemAtCommand(13);
	this->avrMicroRepository->delaym(2000);

	////"AT+CMGD=1,4" index 71
	sendProgMemAtCommand(71);
	this->avrMicroRepository->delaym(5000);

	//"AT+CSCLK=0" index 23
	sendProgMemAtCommand(23);
}

void SimModuleActivity::deleteAllSMS() {
	sendProgMemAtCommand(71);
}

void SimModuleActivity::deleteSmsByIndex(uint8_t index)
{
	this->_simModuleRepository->clearBuffer_m();

	char smsIndex[] = {};

	itoa(index, smsIndex, 10);

	uint8_t l = this->_simProgMemRepository->getAtCommandIndexLengthString(59);

	char readMessageInStoreString[l];

	this->_simProgMemRepository->getAtCommand(59, readMessageInStoreString, l);

	strcat(readMessageInStoreString, smsIndex);

	this->_simModuleRepository->print_m(readMessageInStoreString, true);

	this->avrMicroRepository->delaym(1000);
}

void SimModuleActivity::getSmsByIndex(uint8_t index)
{
	this->_simModuleRepository->clearBuffer_m();

    char smsIndex[] = {};

	itoa(index, smsIndex,10);

	uint8_t l = this->_simProgMemRepository->getAtCommandIndexLengthString(43);

	char readMessageInStoreString[l];

	this->_simProgMemRepository->getAtCommand(43, readMessageInStoreString, l);

	strcat(readMessageInStoreString, smsIndex);

	this->_simModuleRepository->print_m(readMessageInStoreString, true);

	this->avrMicroRepository->delaym(1000);
}

bool SimModuleActivity::getSmsResponse(char* bufferP, uint16_t bufferLenght)
{
	if (this->_simModuleRepository->serial_available() > 0)
	{
		int j = 0;

		int i = 0;
		
		do {
			j = i++;
			bufferP[j] = this->_simModuleRepository->read_m();
			/*	Serial.print(buffer[j]); Serial.print("   "); Serial.println((buffer[j],10));*/
		} while ((bufferP[j] >= 0 && bufferP[j] <= 127) && j < bufferLenght);
		bufferP[j] = '\0';
		//Serial.println(F("buffer : ")); Serial.println(buffer);
	}

	//for (int i = 0; i < bufferLenght; i++)
	//{
	//	bufferP[i] = this->_simModuleRepository->read_m();
	//	Serial.print(bufferP[i]); Serial.print(" - - "); Serial.println(bufferP[i], 10);
	//}
	//int i = 0;
	//bool exit = false;
	//while(!exit && i < bufferLenght)
	//{
	//	bufferP[i] = this->_simModuleRepository->read_m();
	//	//if (i > 0)
	//	//{
	//	//	if (bufferP[i-1] == 'O' && bufferP[i] == 'K')
	//	//	{
	//	//		exit = true;
	//	//	}
	//	//}
	//	//i++;
	//	if(bufferP[i] == '*')
	//	{
	//		exit = true;
	//	}
	//	else {
	//		i++;
	//	}
	//}
	//bufferP[i + 1] = '\0';

	uint16_t l = this->_simProgMemRepository->getAtCommandIndexLengthString(52);

	char sToFind[l];

	this->_simProgMemRepository->getAtCommand(52,sToFind,l);

	if (strstr(bufferP, sToFind) != nullptr)
	{
		return true;
	}
	return false;
}

bool SimModuleActivity::isSmsOnBuffer(char* response,uint16_t progMemIndex)
{
	char message[15]{};

	extractSmsMessageFromReponse(response, message, 15);
	
	uint8_t l = this->_simProgMemRepository->getProgMemSmsToFindLenght(progMemIndex);
	
	char b[l];
	
	this->_simProgMemRepository->getSmsToFind(0, b, l);
	
	//Serial.print(F("progmem : ")); Serial.println(strlen(b));

	//Serial.print(F("message : ")); Serial.println(strlen(message));

	if (strcmp(b, message) == 0)
	{
		//Serial.println(F("message found"));
		return true;
	}
	
	return false;
}

void SimModuleActivity::extractSmsMessageFromReponse(char* response, char* messageBuffer, uint16_t messageLength)
{
	char* pointerFirstMessageChar = (strrchr(response, '"') + 3);
	bool exit = false;
	int i = 0;
	int j = 0;
	do
	{
		j = i++;
		messageBuffer[j] = pointerFirstMessageChar[j];
		//Serial.println(messageBuffer[j], 10);
		if (messageBuffer[j] == '\r' || j >= messageLength)
		{
			exit = true;
		}
	} while (!exit);

	messageBuffer[j] = '\0';
}

char* SimModuleActivity::subStringBetweenTags(char* p_string, char tag[1], uint16_t position, char* buffer)
{
	char* startPointer{};
	char* endPointer{};
	char* c[2]{};
	if (position == 1 || position == 0) {
		startPointer = p_string;
		endPointer = (char*)strstr(p_string, tag);
	}
	else
	{
		for (int i = 0; i < position; i++)
		{
			char* index = (char*)strstr(p_string, tag) + 1;
			p_string = (char*)index;
			if (i == (position - 2))
			{
				c[0] = (char*)index;
			}
			if (i == (position - 1))
			{
				c[1] = (char*)index;
			}
			startPointer = c[0];
			endPointer = c[1] - 1;

		}
	}
	uint8_t messageLength = ((uint16_t)endPointer - (uint16_t)startPointer);

	for (int i = 0; i < messageLength; i++)
	{
		buffer[i] = startPointer[i];
	}
	buffer[messageLength] = '\0';

	return buffer;
}

bool SimModuleActivity::isCallerAuthorized(char* response, char* phoneNumberToCheck)
{
	char phoneNumber[30];
	subStringBetweenTags(response, "\"", 4, phoneNumber);
	if (strcmp(phoneNumber, phoneNumberToCheck) == 0)
	{
		return true;
	}
	return false;
}








