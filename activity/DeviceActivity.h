#pragma once
//#include "DigitalPort.h"
#include "..\model\AnalogPort.h"
#include "..\model\DigitalPort.h"
#include "..\repository\AvrMicroRepository.h"
#include "..\commons\commonsLayer.h"
#include "..\objectsSensor\DigitalPortSensor.h"
#include "..\objectsSensor\AnalogPortSensor.h"


class DeviceActivity
{
public:
	DeviceActivity(AvrMicroRepository& avrMicroRepository, DigitalPortSensor** digitalPortSensors,uint8_t digitalPortSensorsNumber);
	DeviceActivity(AvrMicroRepository& avrMicroRepository, AnalogPortSensor** analogPortSensor,float _vref ,commonsLayer::analogRefMode mode, uint8_t analogPortSensorsNumber);
	DeviceActivity();

	void initializeDigitalPorts();
	float getVref();
	commonsLayer::analogRefMode vrefMode = commonsLayer::analogRefMode::DEFAULT_m;
	float _vref = 5;
	
	float getAnalogPortVrefVoltage(char* portName);
private:
	
protected:
	AvrMicroRepository* avrMicroRepository = nullptr;
	bool isDigitalPortOnAlarm(char* portName);
	bool isAnalogPortOnAlarm(char* portName);
	DigitalPortSensor** digitalPortSensors = nullptr;
	AnalogPortSensor** analogPortSensors = nullptr;
	uint8_t _analogPortsSensorNumber = 0;
	uint8_t _digitalPortsNumber = 0;
	uint8_t _digitalPortSensorNumber = 0;
};

