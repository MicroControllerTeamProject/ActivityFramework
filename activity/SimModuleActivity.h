#pragma once
#include "DeviceActivity.h"
#include <stdint.h>
#include <string.h>
#include "..\objectsSensor\SimModuleDevice.h"
#include "..\interfaces\InterfaceSerialRepository.h"
#include "..\interfaces\InterfaceMicroRepository.h"


class SimModuleActivity : public DeviceActivity
{
public:
	SimModuleActivity(InterfaceSerialRepository& simModuleRepository, AvrMicroRepository& avrMicroRepository, SimModuleDevice** listOfSimModuleDevice, uint8_t simModuleDevicesNumber);
	SimModuleActivity();
	bool makeCall(char* deviceUId);
	void setIsDisableSms(bool isSmsDisabled);
	bool getIsDisableSms();
	void setIsCallDisabled(bool isCallDisabled);
	bool getIsCallDisabled();
	void setIsInSleepMode(bool isInSleepMode);
	bool getIsInSleepMode(bool isInSleepMode);
	void setIsDeviceTurnedOff(bool isTurnedOff, char* deviceUid);
	bool getIsDeviceTurnedOff();
	uint8_t _simModuleDevicesNumber = 0;
	SimModuleDevice** _listOfSimModuleDevice = nullptr;
	InterfaceSerialRepository* _simModuleRepository = nullptr;
	AvrMicroRepository* _avrMicroRepository = nullptr;
private:
	bool _isSmsDisabled = false;
	bool _isCallDisable = false;
	bool _isTurnedOff = false;
	bool _isInSleepMode = false;
	char* _prefixAndphoneNumber;
	long unsigned _baud;
};

