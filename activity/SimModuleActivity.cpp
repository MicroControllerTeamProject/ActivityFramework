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
	this->_simModuleRepository->print_m("AT");
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







