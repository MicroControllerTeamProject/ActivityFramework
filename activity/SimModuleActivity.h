#pragma once
#include "DeviceActivity.h"
#include <stdint.h>
#include <string.h>
#include "..\objectsSensor\SimModuleDevice.h"
#include "..\interfaces\InterfaceSerialRepository.h"
#include "..\interfaces\InterfaceMicroRepository.h"
#include "..\repository\SimProgMemRepository.h"


class SimModuleActivity : public DeviceActivity
{
public:
	SimModuleActivity(InterfaceSerialRepository& simModuleRepository, AvrMicroRepository& avrMicroRepository, SimModuleDevice** listOfSimModuleDevice, uint8_t simModuleDevicesNumber);
	SimModuleActivity(InterfaceSerialRepository& simModuleRepository, SimProgMemRepository& simProgMemRepository,  AvrMicroRepository& avrMicroRepository, SimModuleDevice* simModuleDevice);
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
	SimProgMemRepository* _simProgMemRepository = nullptr;
	/*AvrMicroRepository* _avrMicroRepository = nullptr;*/
	uint8_t getNumberOfSmsReceived();
	void enableSmsIncoming();

	void deleteAllReadSMS();

	bool isSmsOnBuffer(bool deleteIfFound,uint16_t progmemIndex);

	void getSmsByIndex(uint8_t index);

	bool getSmsResponse(char* bufferP, uint16_t bufferLenght);

	/// <summary>
	/// remember to free memory of returned char* pointer
	/// </summary>
	/// <param name="index"></param>
	/// <returns></returns>
	char* getSmSResponseByIndex(uint8_t index);


	void deleteSmSByIndex(uint8_t index);

	uint16_t getSmsBytesLength(char* response);

	int getSmsByIndex();

	void deleteSmsByIndex(uint8_t index);

	int getBuffLenghtPROGMEM_AT_INDEX(uint16_t progMemIndex);

	void extractSmsMessageFromReponse2(char* response, char* messageBuffer, uint16_t messageLength);

	char* extractSmsMessageFromReponse(char* response);

	char* extractSmsCallerFromReponse(char* response);

	bool isCallerAuthorized(char* response, char* phoneNumberToCheck);

private:
	char* subStringBetweenTags(char* p_string, char tag[1], uint16_t position);
	char* subStringBetweenTags2(char* p_string, char tag[1], uint16_t position, char* buffer);

	bool _isSmsDisabled = false;
	bool _isCallDisable = false;
	bool _isTurnedOff = false;
	bool _isInSleepMode = false;
	long unsigned _baud;
};

