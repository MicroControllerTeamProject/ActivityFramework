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

bool SimModuleActivity::makeCall(char* deviceUId) {
	bool returnValue = false;
	for (int i = 0; i < this->_simModuleDevicesNumber; i++)
	{
		if (strcmp(this->_listOfSimModuleDevice[i]->getUid(), deviceUId) == 0)
		{
			/*this->_simModuleRepository->begin_m(this->_listOfSimModuleDevice[i]->getBaud());*/
			char* bufferResponse;
			this->_simModuleRepository->clearBuffer_m();
			/*this->_simModuleRepository->print_m("atd"); this->_simModuleRepository->print_m(this->_simModuleRepository->print_m());*/
			if (this->_simModuleRepository->serial_available())
			{
				bufferResponse = this->_simModuleRepository->readString_m();
				char* findInResponse;
				/*findInResponse = strstr(bufferResponse, "ERROR");
				if (findInResponse != NULL)
				{
					this->setLastErrorCode('E');
				}
				findInResponse = strstr(bufferResponse, "DIALTONE");
				if (findInResponse != NULL)
				{
					this->setLastErrorCode('D');
				}*/
				findInResponse = strstr(bufferResponse, "OK");
				if (findInResponse != NULL)
				{
					returnValue = true;
				}
				/*else
				{
					this->setLastErrorCode('N');
				}*/
				//#if defined(VM_DEBUG)
				//		avrMicroRepository.print_m("returned internal value : "); avrMicroRepository.print_m(bufferResponse, true);
				//		avrMicroRepository.clearBuffer_m();
				//#endif

				//#if defined(VM_DEBUG)
				//		avrMicroRepository.print_m("ram b:"); avrMicroRepository.print_m(avrMicroRepository.getFreeRam(), true);
				//		avrMicroRepository.clearBuffer_m();
				//#endif

				this->avrMicroRepository->free_m(bufferResponse);
				this->avrMicroRepository->delaym(2000);
			}
		}
		//	char* bufferResponse;
		//	this->simModuleRepository->clearBuffer_m();
		//	this->simModuleRepository->print_m("atd"); this->simModuleRepository->print_m(this->_prefixAndphoneNumber, true);
		//	if (avrMicroRepository.serial_available())
		//	{
		//		bufferResponse = avrMicroRepository.readString_m();
		//		char* findInResponse; 
		//		/*findInResponse = strstr(bufferResponse, "ERROR");
		//		if (findInResponse != NULL)
		//		{
		//			this->setLastErrorCode('E');
		//		}
		//		findInResponse = strstr(bufferResponse, "DIALTONE");
		//		if (findInResponse != NULL)
		//		{
		//			this->setLastErrorCode('D');
		//		}*/
		//		findInResponse = strstr(bufferResponse, "OK");
		//		if (findInResponse != NULL)
		//		{
		//			returnValue = true;
		//		}
		//		/*else
		//		{
		//			this->setLastErrorCode('N');
		//		}*/
		////#if defined(VM_DEBUG)
		////		avrMicroRepository.print_m("returned internal value : "); avrMicroRepository.print_m(bufferResponse, true);
		////		avrMicroRepository.clearBuffer_m();
		////#endif
		//
		////#if defined(VM_DEBUG)
		////		avrMicroRepository.print_m("ram b:"); avrMicroRepository.print_m(avrMicroRepository.getFreeRam(), true);
		////		avrMicroRepository.clearBuffer_m();
		////#endif
		//
		//		avrMicroRepository.free_m(bufferResponse);
		//		avrMicroRepository.delaym(2000);
	}
	//#if defined(VM_DEBUG)
	//	avrMicroRepository.print_m("ram pointerOfCReturn:"); avrMicroRepository.print_m(avrMicroRepository.getFreeRam(), true);
	//	avrMicroRepository.clearBuffer_m();
	//#endif
	return returnValue;
}

char* SimModuleActivity::makeCall()
{
	//char* returnValue = "XXX";
	char* bufferResponse;
	/*this->_simModuleRepository->print_m("AT",true);*/
	//this->avrMicroRepository->delaym(1000);
	this->_simModuleRepository->clearBuffer_m();
	//this->avrMicroRepository->delaym(1000);
	//this->_simModuleRepository->print_m("atd+393202445649;",true);
	this->_simModuleRepository->print_m("atd"); this->_simModuleRepository->print_m(this->_listOfSimModuleDevice[0]->getPrefixNumber()); this->_simModuleRepository->print_m(this->_listOfSimModuleDevice[0]->getPhoneNumber(), true);

	this->avrMicroRepository->delaym(5000);

	if (this->_simModuleRepository->serial_available())
	{
		bufferResponse = this->_simModuleRepository->readString_m();
		//strcpy(returnValue, bufferResponse);

//#ifdef _DEBUG
//		Serial.println(bufferResponse);
//#endif
		//char* findInResponse;
		///*findInResponse = strstr(bufferResponse, "ERROR");
		//if (findInResponse != NULL)
		//{
		//	this->setLastErrorCode('E');
		//}
		//findInResponse = strstr(bufferResponse, "DIALTONE");
		//if (findInResponse != NULL)
		//{
		//	this->setLastErrorCode('D');
		//}*/
		//findInResponse = strstr(bufferResponse, "OK");
		//if (findInResponse != NULL)
		//{
		//	returnValue = true;
		//}
		/*else
		{
			this->setLastErrorCode('N');
		}*/
		//#if defined(VM_DEBUG)
		//		avrMicroRepository.print_m("returned internal value : "); avrMicroRepository.print_m(bufferResponse, true);
		//		avrMicroRepository.clearBuffer_m();
		//#endif
		//#if defined(VM_DEBUG)
		//		avrMicroRepository.print_m("ram b:"); avrMicroRepository.print_m(avrMicroRepository.getFreeRam(), true);
		//		avrMicroRepository.clearBuffer_m();
		//#endif

		/*this->avrMicroRepository->free_m(bufferResponse);*/
		this->avrMicroRepository->delaym(2000);
	}

	return bufferResponse;
}

//void SimModuleActivity::enableIncomingSMS()
//{
//
//	/*this->_simModuleRepository->begin_m(listOfSimModuleDevice->getBaud());
//
//	this->_simModuleRepository->print_m("AT",true);
//	this->avrMicroRepository->delaym(1000);
//
//	this->_simModuleRepository->print_m("AT+CPMS=\"SM\"",true);
//	this->avrMicroRepository->delaym(1000);
//
//	this->_simModuleRepository->print_m("AT+CMGF=1",true);
//	this->avrMicroRepository->delaym(1000);
//
//	this->_simModuleRepository->print_m("AT+CMGD=1,4",true);
//	this->avrMicroRepository->delaym(5000);
//
//	this->_simModuleRepository->print_m("AT+CSCLK=0", true);*/
//	//this->_simModuleRepository->print_m("AT+CNETLIGHT=0",true);
//	//this->avrMicroRepository->delaym(1000);
//	char* response = {};
//	uint8_t messageNumbers = 0;
//
//	enableSmsIncoming();
//
//	while (1)
//	{
//		messageNumbers = getNumberOfSmsReceived();
//		if (messageNumbers > 0)
//		{
//			char* response = getSmSResponseByIndex(1);
//			Serial.println(response);
//			deleteSmSByIndex(1);
//			char* smsMessage = extractSmsMessageFromReponse(response);
//			Serial.println(smsMessage);
//			for (int i = 0; i < 10; i++)
//			{
//				digitalWrite(13, HIGH);
//				delay(200);
//				digitalWrite(13, LOW);
//				delay(200);
//			}
//			free(smsMessage);
//			free(response);
//		}
//#ifdef _DEBUG
//		Serial.println(this->avrMicroRepository->getFreeRam());
//#endif
//	}
//	return;
//
//
//#ifdef _DEBUG
//	while (1)
//	{
//	/*	this->_simModuleRepository->clearBuffer_m();
//
//		this->_simModuleRepository->print_m("AT+CPMS?", true);
//
//		delay(100);
//
//		uint8_t messageNumbers = 0;
//		char* endOfPointer = {};
//
//		if (this->_simModuleRepository->serial_available())
//		{
//			response = this->_simModuleRepository->readString_m();
//
//			if (response != nullptr) {
//
//				char secondCommaFound[] = { strchr(response, ',')[2] };
//				
//				if (strcmp(secondCommaFound, ",") == 0)
//				{
//					endOfPointer = ((strchr(response, ',') + 2));
//				}
//				else {
//					endOfPointer = ((strchr(response, ',') + 3));
//				}
//			
//				messageNumbers = strtol(((strchr(response, ',') + 1)),&endOfPointer, 10);
//				Serial.print("number : "); Serial.println(messageNumbers);
//			}
//			free(response);
//		}*/
//
//		messageNumbers = getNumberOfSmsReceived();
//
//		if (messageNumbers > 0)
//		{
//			for (int i = 1; i <= messageNumbers; i++)
//			{
//				this->_simModuleRepository->clearBuffer_m();
//
//				char smsIndex[] = {};
//				itoa(i, smsIndex,10);
//
//				char readMessageInStoreString[15] = "AT+CMGR=";
//				strcat(readMessageInStoreString, smsIndex);
//
//				char deleteMessageInStoreString[15] = "AT+CMGD=";
//				strcat(deleteMessageInStoreString, smsIndex);
//				strcat(deleteMessageInStoreString, ",0");
//			
//				this->_simModuleRepository->print_m(readMessageInStoreString, true);
//
//				delay(1000);
//
//				if (this->_simModuleRepository->serial_available() > 0)
//				{
//					response = this->_simModuleRepository->readString_m();
//
//					if (strstr(response, "+CMGR:") != nullptr)
//					{
//#ifdef _DEBUG
//						Serial.print('#'); Serial.print(response); Serial.println('#');
//#endif
//						/*uint8_t cicle = 0;*/
//
//					/*	char* messageReceived = {};*/
//
//						char* pointerFirstMessageChar = (strrchr(response, '"') + 3);
//
//						char* pointerOfCReturn = strchr(pointerFirstMessageChar, '\r\n');
//
//						Serial.print("mess.lentgh : "); Serial.println((int)pointerOfCReturn-(int)pointerFirstMessageChar);
//
//						uint16_t messageLength = (uint16_t)pointerOfCReturn - (uint16_t)pointerFirstMessageChar;
//
//						char messageBuffer[messageLength];
//
//						for (int i = 0; i < messageLength; i++)
//						{
//							messageBuffer[i] = pointerFirstMessageChar[i];
//							/*Serial.print(pointerFirstMessageChar[i]);*/
//						}
//						messageBuffer[messageLength - 1] = '\0';
//
//						Serial.print("message : "); Serial.println(messageBuffer);
//						
//						/*while (pointerFirstMessageChar[cicle] != '\r\n')
//						{
//							Serial.print('-'); Serial.print(pointerFirstMessageChar[cicle]); Serial.println('-');
//
//							cicle++;
//						}*/
//
//					/*	Serial.print('#'); Serial.print(messageReceived); Serial.println('#');*/
//						
//						this->_simModuleRepository->print_m(deleteMessageInStoreString, true);
//					}
//					free(response);
//				}
//			}
//		}
//#ifdef _DEBUG
//		Serial.println(this->avrMicroRepository->getFreeRam());
//#endif
//	}
//#endif
//
//}

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

	delay(1000);

	if (this->_simModuleRepository->serial_available())
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

void SimModuleActivity::enableSmsIncoming()
{
	//AT+CPMS="SM" index 0
	this->_simProgMemRepository->sendAtCommand(0, this->_simModuleRepository);

	this->avrMicroRepository->delaym(2000);

	//"AT+CMGF=1" index = 13
	this->_simProgMemRepository->sendAtCommand(13, this->_simModuleRepository);

	this->avrMicroRepository->delaym(2000);

	////"AT+CMGD=1,4" index 71
	this->_simProgMemRepository->sendAtCommand(71, this->_simModuleRepository);
	this->avrMicroRepository->delaym(5000);

	/*this->_simModuleRepository->print_m("AT+CSCLK=0", true);*/
	this->_simProgMemRepository->sendAtCommand(23, this->_simModuleRepository);


}

void SimModuleActivity::deleteAllReadSMS() {
	this->_simModuleRepository->print_m("AT+CMGD=1,4", true);
}

bool SimModuleActivity::isSmsOnBuffer(bool deleteIfFound, uint16_t progmemIndex)
{
	bool isSmsOnBuffer = false;

	uint16_t smsStringToFindLenght = _simProgMemRepository->getProgMemSmsToFindLenght(progmemIndex);

	char smsStringToFound[smsStringToFindLenght];

	_simProgMemRepository->getSmsToFind(progmemIndex, smsStringToFound, smsStringToFindLenght);

#ifdef _DEBUG
	//Serial.print(F("sms to find #")); Serial.print(smsStringToFound); Serial.println(F("#"));
#endif
	uint8_t smsNumbers = getNumberOfSmsReceived();
#ifdef _DEBUG
	Serial.print(F("sms number : ")); Serial.println(smsNumbers);
#endif

	if (smsNumbers > 0)
	{
		int smsResponceLength = 0;

		smsResponceLength = 90;

		getSmsUnReadResponceLengh(0);

#ifdef _DEBUG
		/*Serial.print(F("smsResponceLength : ")); Serial.println(smsResponceLength);*/
#endif

		char smsResponceBuff[smsResponceLength];

		if (getSmsResponse(smsResponceBuff, smsResponceLength))
		{
#ifdef _DEBUG
			/*Serial.print("#"); Serial.print(smsResponceBuff); Serial.println("#");*/
#endif
			int smsReceivedLenght = getSmsBytesLength(smsResponceBuff);
#ifdef _DEBUG
			/*Serial.print(F("sms lenght : ")); Serial.println(smsReceivedLenght);*/
#endif

			char smsReceived[smsReceivedLenght];

			extractSmsMessageFromReponse2(smsResponceBuff, smsReceived, smsReceivedLenght);

#ifdef _DEBUG
			Serial.print(F("smsReceived : ")); Serial.println(smsReceived);
#endif
			if (strcmp(smsReceived, smsStringToFound) == 0) {
#ifdef _DEBUG
				/*Serial.println(F("found"));*/
#endif
				isSmsOnBuffer = true;
			}
		}
	/*	else
		{
			deleteAllReadSMS();
			isSmsOnBuffer = false;
		}*/
	}
	return isSmsOnBuffer;
}

/// <summary>
/// remember to free memory of returned char* pointer
/// </summary>
/// <param name="index"></param>
/// <returns></returns>
/// 

int SimModuleActivity::getSmsUnReadResponceLengh()
{
	this->_simModuleRepository->clearBuffer_m();

	char readMessageInStoreString[8] = "AT+CMGL";

	this->_simModuleRepository->print_m(readMessageInStoreString, true);

	this->avrMicroRepository->delaym(1000);

	return this->_simModuleRepository->serial_available();
}

int SimModuleActivity::getBuffLenghtPROGMEM_AT_INDEX(uint16_t progMemIndex)
{
	this->_simModuleRepository->clearBuffer_m();

	this->_simProgMemRepository->sendAtCommand(progMemIndex, this->_simModuleRepository);

	delay(1000);

	return this->_simModuleRepository->serial_available();
}

bool SimModuleActivity::getSmsResponse(char* bufferP, uint16_t bufferLenght)
{
	//for (int i = 0; i < bufferLenght; i++)
	//{
	//	bufferP[i] = this->_simModuleRepository->read_m();
	//	Serial.print(bufferP[i]); Serial.print(" - - "); Serial.println(bufferP[i], 10);
	//}
	int i = 0;
	bool exit = false;
	while(!exit && i < 90)
	{
		bufferP[i] = this->_simModuleRepository->read_m();
		//if (i > 0)
		//{
		//	if (bufferP[i-1] == 'O' && bufferP[i] == 'K')
		//	{
		//		exit = true;
		//	}
		//}
		//i++;
		if(bufferP[i] == '*')
		{
			exit = true;
		}
		else {
			i++;
		}
	}
	bufferP[i + 1] = '\0';

	if (strstr(bufferP, "+CMGL:") != nullptr)
	{
		return true;
	}
	return false;
}

char* SimModuleActivity::getSmSResponseByIndex(uint8_t index)
{
	if (index == 0)index++;

	this->_simModuleRepository->clearBuffer_m();

	char smsIndex[] = {};

	itoa(index, smsIndex, 10);

	char readMessageInStoreString[15] = "AT+CMGR=";

	strcat(readMessageInStoreString, smsIndex);

	this->_simModuleRepository->print_m(readMessageInStoreString, true);

	delay(1000);

	char* response = {};

	if (this->_simModuleRepository->serial_available() > 0)
	{
		response = this->_simModuleRepository->readString_m();

		if (strstr(response, "+CMGR:") != nullptr)
		{
			return response;
		}
	}
	return '\0';
}

void SimModuleActivity::deleteSmSByIndex(uint8_t index)
{
	if (index == 0)index++;

	this->_simModuleRepository->clearBuffer_m();

	char smsNumber[] = {};

	itoa(index, smsNumber, 10);

	char deleteMessageInStoreString[15] = "AT+CMGD=";

	strcat(deleteMessageInStoreString, smsNumber);

	strcat(deleteMessageInStoreString, ",0");

	this->_simModuleRepository->print_m(deleteMessageInStoreString, true);

}

uint16_t SimModuleActivity::getSmsBytesLength(char* response)
{
	char* pointerFirstMessageChar = (strrchr(response, '"') + 3);

	char* pointerOfCReturn = strchr(pointerFirstMessageChar, '\r\n');

	//Serial.print("mess.lentgh : "); Serial.println((int)pointerOfCReturn - (int)pointerFirstMessageChar);

	uint16_t messageLength = (uint16_t)pointerOfCReturn - (uint16_t)pointerFirstMessageChar;

	return messageLength;
}

void SimModuleActivity::extractSmsMessageFromReponse2(char* response, char* messageBuffer, uint16_t messageLength)
{
	char* pointerFirstMessageChar = (strrchr(response, '"') + 3);

	int i,j = 0;
	do
	{
		j = i++;
		messageBuffer[j] = pointerFirstMessageChar[j];
	} while (messageBuffer[j] != '*' && j < messageLength);

	messageBuffer[j] = '\0';
}

/// <summary>
/// remember to free memory of returned char* pointer
/// </summary>
/// <param name="response"></param>
/// <returns></returns>
char* SimModuleActivity::extractSmsMessageFromReponse(char* response)
{
	char* pointerFirstMessageChar = (strrchr(response, '"') + 3);

	char* pointerOfCReturn = strchr(pointerFirstMessageChar, '\r\n');

	//Serial.print("mess.lentgh : "); Serial.println((int)pointerOfCReturn - (int)pointerFirstMessageChar);

	uint16_t messageLength = (uint16_t)pointerOfCReturn - (uint16_t)pointerFirstMessageChar;

	char* messageBuffer = {};

	messageBuffer = (char*)calloc(messageLength, sizeof(char));
	if (messageBuffer == nullptr)
	{
#ifdef _DEBUG
		Serial.println("nP");
#endif
		return '\0';
	}

	/*char messageBuffer[messageLength];*/

	for (int i = 0; i < messageLength; i++)
	{
		messageBuffer[i] = pointerFirstMessageChar[i];
		/*Serial.print(pointerFirstMessageChar[i]);*/
	}
	messageBuffer[messageLength - 1] = '\0';

	//Serial.print("smsMessage : "); Serial.println(messageBuffer);
	return messageBuffer;
}

char* SimModuleActivity::extractSmsCallerFromReponse(char* response)
{
	return subStringBetweenTags(response, "\"", 4);
}

char* SimModuleActivity::subStringBetweenTags(char* p_string, char tag[1], uint16_t position)
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
	char* messageBuffer = {};
	messageBuffer = (char*)calloc(messageLength, sizeof(char));
	if (messageBuffer == nullptr)
	{
#ifdef _DEBUG
		Serial.println("nP");
#endif
		return '\0';
	}

	for (int i = 0; i < messageLength; i++)
	{
		messageBuffer[i] = startPointer[i];
	}
	messageBuffer[messageLength - 1] = '\0';
	return messageBuffer;
}

char* SimModuleActivity::subStringBetweenTags2(char* p_string, char tag[1], uint16_t position, char* buffer)
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
	subStringBetweenTags2(response, "\"", 4, phoneNumber);
	if (strcmp(phoneNumber, phoneNumberToCheck) == 0)
	{
		return true;
	}
	return false;
}

//void SimModuleActivity::makeCall(AvrMicroRepository& avrMicroRepository){
//	avrMicroRepository.begin_m(this->_baud);
//	char* bufferResponse;
//	avrMicroRepository.clearBuffer_m();
//	avrMicroRepository.print_m("atd");avrMicroRepository.println(this->_prefixAndphoneNumber);
//	if (avrMicroRepository.serial_available())
//	{
//		int bufferAddress = avrMicroRepository.readString_m(bufferResponse);
//		char* findInResponse = strstr(bufferResponse, "ERROR");
//		if (findInResponse != NULL)
//		{
//			avrMicroRepository.setLastErrorCode('E');
//		}
//#if defined(VM_DEBUG)
//		avrMicroRepository.print_m("returned internal value : "); avrMicroRepository.println(bufferResponse);
//		avrMicroRepository.clearBuffer_m();
//#endif
//
//#if defined(VM_DEBUG)
//		avrMicroRepository.print_m("free ram : "); avrMicroRepository.println(avrMicroRepository.getFreeRam());
//		avrMicroRepository.clearBuffer_m();
//#endif
//
//		avrMicroRepository.free_m(bufferResponse);
//		avrMicroRepository.delaym(2000);
//	}
//}







