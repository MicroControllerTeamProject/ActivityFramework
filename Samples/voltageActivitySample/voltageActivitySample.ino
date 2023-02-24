/*
 Name:		test_lsgNewFramework.ino
 Created:	1/19/2023 11:44:53 AM
 Author:	luigi.santagada
*/
#include "\Repos\MicroControllerTeamProject\ActivityFramework\activity\VoltageActivity.h"
#include "\Repos\MicroControllerTeamProject\ActivityFramework\activity\DeviceActivity.h"
#include "\Repos\MicroControllerTeamProject\ActivityFramework\repository\AvrMicroRepository.h"
#include "\Repos\MicroControllerTeamProject\ActivityFramework\objectsSensor\AnalogPortSensor.h"
#include <Arduino.h>

AnalogPort* listOfBatteryAnalogPorts[1];
AvrMicroRepository avrMicroRepository(19200);
AnalogPortSensor* listOfBatteriesAnalogSensor[1];
VoltageActivity* batteryVoltageActivity;

void setup() {
	listOfBatteryAnalogPorts[0] = new AnalogPort("BA0", A0);
	listOfBatteryAnalogPorts[0]->isEnable = true;
	listOfBatteryAnalogPorts[0]->maxVoltageAlarmValueIn = 4.30f;
	listOfBatteryAnalogPorts[0]->minVoltageAlarmValueIn = 3.25f;
	listOfBatteriesAnalogSensor[0] = new AnalogPortSensor("SB01",listOfBatteryAnalogPorts, sizeof(listOfBatteryAnalogPorts) / sizeof(listOfBatteryAnalogPorts[0]));
	batteryVoltageActivity = new VoltageActivity(avrMicroRepository, listOfBatteriesAnalogSensor, 4.80f, commonsLayer::DEFAULT_m, 1);
}

// the loop function runs over and over again until power down or reset
void loop() {
	Serial.print("voltage : "); Serial.println(batteryVoltageActivity->getVoltage("SB01"));
	Serial.print("graph : "); Serial.println(batteryVoltageActivity->getGrafBarLevel("SB01",3.30,3.80,4.30));
	/*if (batteryVoltageActivity->isVoltageOutOfRange("SB01"))
	{
		Serial.println("problem");
	}*/
	delay(500);
}
