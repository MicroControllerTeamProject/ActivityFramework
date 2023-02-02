#include "SimModuleDevice.h"

SimModuleDevice::SimModuleDevice(char* uid, DigitalPort** listOfDigitalPorts, uint8_t digitalPortsNumbers) : DigitalPortSensor(uid, listOfDigitalPorts, digitalPortsNumbers){
}

SimModuleDevice::SimModuleDevice()
{
}

void SimModuleDevice::init(char* prefixNumber, char* phoneNumber)
{
	this->_phoneNumber = phoneNumber;
	this->_prefixNumber = prefixNumber;
	
}


void SimModuleDevice::setIsDisableSms(bool isSmsDisabled)
{
}

bool SimModuleDevice::getIsDisableSms()
{
	return false;
}

void SimModuleDevice::setIsCallDisabled(bool isCallDisabled)
{
}

void SimModuleDevice::setIsDeviceDisabled(bool isDeviceDisabled)
{
}

bool SimModuleDevice::getIsDeviceDisabled()
{
	return false;
}

bool SimModuleDevice::getIsCallDisabled()
{
	return false;
}

//void SimModuleDevice::isSmsDisabled(bool isSmsDisabled){
//	this->_isSmsDisabled = isSmsDisabled;
//}
//
//void SimModuleDevice::callDisabled(bool isCallDisabled){
//	this->_isCallDisable = isCallDisabled;
//}

char* SimModuleDevice::getPhoneNumber()
{
	return this->_phoneNumber;
}

char* SimModuleDevice::getPrefixNumber()
{
	return this->_prefixNumber;
}

//unsigned long SimModuleDevice::getBaud()
//{
//	return this->_baud;
//}





