#pragma once
#include "DeviceActivity.h"
#include <stdint.h>
#include <string.h>
#include "..\objectsSensor\SimModuleDevice.h"
#include "..\interfaces\InterfaceSerialRepository.h"
#include "..\interfaces\InterfaceMicroRepository.h"
#include "..\repository\ProgMemRepository.h"


class SimModuleActivity : public DeviceActivity
{
public:
	SimModuleActivity(InterfaceSerialRepository& simModuleRepository, AvrMicroRepository& avrMicroRepository, SimModuleDevice** listOfSimModuleDevice, uint8_t simModuleDevicesNumber);
	SimModuleActivity(InterfaceSerialRepository& simModuleRepository, AvrMicroRepository& avrMicroRepository, SimModuleDevice* simModuleDevice);
	SimModuleActivity();
	bool makeCall(char* deviceUId);
	char* makeCall();
	/*void enableIncomingSMS();*/
	void setIsDisableSms(bool isSmsDisabled);
	bool getIsDisableSms();
	void setIsCallDisabled(bool isCallDisabled);
	bool getIsCallDisabled();
	void setIsInSleepMode(bool isInSleepMode);
	bool getIsInSleepMode(bool isInSleepMode);
	bool setIsDeviceTurnedOff(bool isTurnedOff, char* deviceUid);
	bool getIsDeviceTurnedOff();
	uint8_t _simModuleDevicesNumber = 0;
	SimModuleDevice** _listOfSimModuleDevice = nullptr;
	InterfaceSerialRepository* _simModuleRepository = nullptr;
	/*AvrMicroRepository* _avrMicroRepository = nullptr;*/
	uint8_t getNumberOfSms();
	void enableSmsIncoming(ProgMemRepository* progMemRepository);

	/// <summary>
	/// remember to free memory of returned char* pointer
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	char* getSmSResponseByIndex(uint8_t index);
	void deleteSmSByIndex(uint8_t index);

	char* extractSmsMessageFromReponse(char* response);
	char* extractSmsCallerFromReponse(char* response);
private:
	char* subStringBetweenTags(char* p_string, char tag[1], uint16_t position);
	bool _isSmsDisabled = false;
	bool _isCallDisable = false;
	bool _isTurnedOff = false;
	bool _isInSleepMode = false;
	long unsigned _baud;
};

