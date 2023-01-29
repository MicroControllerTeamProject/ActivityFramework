#include "SimModuleActivity.h"

#ifdef _DEBUG
#include <Arduino.h>
#endif

SimModuleActivity::SimModuleActivity(InterfaceSerialRepository& simModuleRepository,
	AvrMicroRepository& avrMicroRepository, SimModuleDevice** listOfSimModuleDevice,
	uint8_t simModuleDevicesNumber) : DeviceActivity((AvrMicroRepository&)avrMicroRepository, (DigitalPortSensor**)listOfSimModuleDevice, simModuleDevicesNumber) {
	this->avrMicroRepository = &avrMicroRepository;
	this->_simModuleRepository = &simModuleRepository;
	this->_listOfSimModuleDevice = listOfSimModuleDevice;
	this->_simModuleDevicesNumber = simModuleDevicesNumber;


}

SimModuleActivity::SimModuleActivity() {
}

bool SimModuleActivity::makeCall(char* deviceUId) {
	bool returnValue = false;
	for (int i = 0; i < this->_simModuleDevicesNumber; i++)
	{
		if (strcmp(this->_listOfSimModuleDevice[i]->getUid(), deviceUId) == 0)
		{
			this->_simModuleRepository->begin_m(this->_listOfSimModuleDevice[i]->getBaud());
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
	//	avrMicroRepository.print_m("ram a:"); avrMicroRepository.print_m(avrMicroRepository.getFreeRam(), true);
	//	avrMicroRepository.clearBuffer_m();
	//#endif
	return returnValue;
}

char* SimModuleActivity::makeCall(SimModuleDevice* simModuleDevice)
{
	char* returnValue = "XXX";
	char* bufferResponse;
	this->_simModuleRepository->begin_m(simModuleDevice->getBaud());
	this->_simModuleRepository->print_m("AT",true);
	//this->avrMicroRepository->delaym(1000);
	this->_simModuleRepository->clearBuffer_m();
	//this->avrMicroRepository->delaym(1000);
	this->_simModuleRepository->print_m("atd"); this->_simModuleRepository->print_m(simModuleDevice->getPrefixNumber()); this->_simModuleRepository->print_m(simModuleDevice->getPhoneNumber(), true);

	this->avrMicroRepository->delaym(5000);

	if (this->_simModuleRepository->serial_available())
	{
		bufferResponse = this->_simModuleRepository->readString_m();
		strcpy(returnValue, bufferResponse);
		
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

		this->avrMicroRepository->free_m(bufferResponse);
		this->avrMicroRepository->delaym(2000);
	}
	
	return returnValue;
}

void SimModuleActivity::enableIncomingSMS(SimModuleDevice* simModuleDevice)
{
	this->_simModuleRepository->begin_m(simModuleDevice->getBaud());

	this->_simModuleRepository->print_m("AT",true);
	this->avrMicroRepository->delaym(1000);

	this->_simModuleRepository->print_m("AT+CPMS=\"SM\"",true);
	this->avrMicroRepository->delaym(1000);

	this->_simModuleRepository->print_m("AT+CMGF=1",true);
	this->avrMicroRepository->delaym(1000);

	this->_simModuleRepository->print_m("AT+CMGD=1,4",true);
	this->avrMicroRepository->delaym(5000);

	this->_simModuleRepository->print_m("AT+CSCLK=0", true);

	//this->_simModuleRepository->print_m("AT+CNETLIGHT=0",true);

	//this->avrMicroRepository->delaym(1000);
	char* response = {};
	uint8_t smsNumbers = 0;
#ifdef _DEBUG
	while (1)
	{
		this->_simModuleRepository->clearBuffer_m();

		this->_simModuleRepository->print_m("AT+CPMS?", true);

		delay(100);

		uint8_t messageNumbers = 0;
		char* endOfPointer = {};

		if (this->_simModuleRepository->serial_available())
		{
			response = this->_simModuleRepository->readString_m();

			if (response != nullptr) {

				char secondCommaFound[] = { strchr(response, ',')[2] };
				
				if (strcmp(secondCommaFound, ",") == 0)
				{
					endOfPointer = ((strchr(response, ',') + 2));
				}
				else {
					endOfPointer = ((strchr(response, ',') + 3));
				}
			
				messageNumbers = strtol(((strchr(response, ',') + 1)),&endOfPointer, 10);
				Serial.print("number : "); Serial.println(messageNumbers);
			}
			free(response);
		}
		if (messageNumbers > 0)
		{
			for (int i = 1; i <= messageNumbers; i++)
			{
				this->_simModuleRepository->clearBuffer_m();

				char n[] = {};
				itoa(i, n,10);

				char readMessageInStoreString[15] = "AT+CMGR=";
				strcat(readMessageInStoreString, n);

				char deleteMessageInStoreString[15] = "AT+CMGD=";
				strcat(deleteMessageInStoreString, n);
				strcat(deleteMessageInStoreString, ",0");
			
				this->_simModuleRepository->print_m(readMessageInStoreString, true);

				delay(1000);

				if (this->_simModuleRepository->serial_available())
				{
					response = this->_simModuleRepository->readString_m();

					if (strstr(response, "+CMGR:") != nullptr)
					{
#ifdef _DEBUG
						Serial.print('#'); Serial.print(response); Serial.println('#');
#endif
						uint8_t cicle = 0;

						char* messageReceived = {};

						char* d = (strrchr(response, '"') + 3);

						char* a = strchr(d, '\r\n');

						Serial.print("puntatore : "); Serial.println((int)a-(int)d);

						while (d[cicle] != '\r')
						{
							Serial.print('-'); Serial.print(d[cicle]); Serial.println('-');

							cicle++;
						}

						Serial.print('#'); Serial.print(messageReceived); Serial.println('#');
						
						this->_simModuleRepository->print_m(deleteMessageInStoreString, true);
					}
					free(response);
				}
			}
		}
#ifdef _DEBUG
		Serial.println(this->avrMicroRepository->getFreeRam());
#endif
	}
#endif

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
						this->_listOfSimModuleDevice[i]->setIsDeviceDisabled(true);

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







