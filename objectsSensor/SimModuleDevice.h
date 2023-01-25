#pragma once
#include "DigitalPortSensor.h"

class SimModuleDevice : public DigitalPortSensor
{
public:
	SimModuleDevice(char* uid, DigitalPort** listOfDigitalPorts, uint8_t digitalPortsNumbers);
	void init(char* prefixNumber, char* phoneNumber, unsigned long baud);
	void setIsDisableSms(bool isSmsDisabled);
	bool getIsDisableSms();
	void setIsCallDisabled(bool isCallDisabled);

	void setIsDeviceDisabled(bool isDeviceDisabled);
	bool getIsDeviceDisabled();

	bool getIsCallDisabled();
	char* getPhoneNumber();
	char* getPrefixNumber();
	unsigned long getBaud();
private:
	bool _isSmsDisabled = false;
	bool _isCallDisable = false;
	bool isTurnedOff = false;
	bool isInSleepMode = false;
	char* _phoneNumber = {};
	char* _prefixNumber = {};
	unsigned long _baud = 0;
};

