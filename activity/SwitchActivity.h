#pragma once
#include "DeviceActivity.h"
#include "..\repository\AvrMicroRepository.h"
#include "..\model\DigitalPort.h"

class SwitchActivity :
    public DeviceActivity
{
public:
    SwitchActivity(AvrMicroRepository& avrMicroRepository,DigitalPort** digitalPort);
    bool isThereASwitchOn();
    bool isSwitchOn(char* portName);
    bool isSwitchOn(uint8_t pinNumber);
};

