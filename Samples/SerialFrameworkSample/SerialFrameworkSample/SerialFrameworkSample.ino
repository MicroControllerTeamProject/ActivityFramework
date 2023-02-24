/*
 Name:		SerialFrameworkSample.ino
 Created:	1/25/2023 9:54:04 AM
 Author:	luigi.santagada
*/
#include "\Repos\MicroControllerTeamProject\ActivityFramework\activity\SimModuleActivity.h"
#include "\Repos\MicroControllerTeamProject\ActivityFramework\activity\DeviceActivity.h"
#include "\Repos\MicroControllerTeamProject\ActivityFramework\repository\AvrMicroRepository.h"
#include "\Repos\MicroControllerTeamProject\ActivityFramework\model\DigitalPort.h"
#include "\Repos\MicroControllerTeamProject\ActivityFramework\objectsSensor\SimModuleDevice.h"
#include "\Repos\MicroControllerTeamProject\ActivityFramework\repository\AvrMicroRepository.h"
#include "\Repos\MicroControllerTeamProject\ActivityFramework\repository\SoftwareSerialRepository.h"
#include "\Repos\MicroControllerTeamProject\ActivityFramework\interfaces\InterfaceSerialRepository.h"
#include "\Repos\MicroControllerTeamProject\ActivityFramework\repository\SimProgMemRepository.h"

//#define PREFIX "+39"
//#define PHONENUMBER "3202445649;"

//const char StringPtr[] = "string0";



//SimModuleDevice* listOfSimModuleDevice[1];
DigitalPort* listOfPortsForSimModule[1];
SimModuleActivity simModuleActivity1;
//SimModuleActivity* simModuleActivity2;
AvrMicroRepository  avrMicroRepository(19200);
SimProgMemRepository simProgMemRepository;


//SoftwareSerialRepository softwareSerialRepository2(8, 7, 19200);
SoftwareSerialRepository softwareSerialRepository1(10, 9, 19200);


SimModuleDevice* simModuleDevice;


// the setup function runs once when you press reset or power the board
void setup() {

	pinMode(13, OUTPUT);

	Serial.println(F("RESTART---------------------------------------------"));

	listOfPortsForSimModule[0] = new DigitalPort("T", 5);

	listOfPortsForSimModule[0]->direction = DigitalPort::PortDirection::output;

	/*listOfSimModuleDevice[0] = new SimModuleDevice("Sim01", listOfPortsForSimModule, 1);

	listOfSimModuleDevice[0]->init("+39", "3202445649;");*/

	simModuleDevice = new SimModuleDevice("Sim01", listOfPortsForSimModule, 1);

	simModuleDevice->init("+39", "3202445649;");

	//simModuleActivity1 = new SimModuleActivity(softwareSerialRepository1, avrMicroRepository, listOfSimModuleDevice, 1);

	simModuleActivity1 = SimModuleActivity(softwareSerialRepository1, simProgMemRepository, avrMicroRepository, simModuleDevice);

	simModuleActivity1.enableSmsIncoming();


}
// the loop function runs over and over again until power down or reset
void loop() {
	Serial.print(F("start free ram : ")); Serial.println(avrMicroRepository.getFreeRam());
	/*callTest();
	delay(10000);
	receiveSmsTest();*/

	receiveSmsTest();

}

void callTest()
{
	int bl = simModuleActivity1._simModuleRepository->get_SS_MAX_RX_BUFF();

	char buffer[bl];

	simModuleActivity1.makeCall(buffer, bl);

	Serial.println(buffer);
}

void receiveSmsTest()
{
	if (simModuleActivity1.getNumberOfSmsReceived() == 0)
	{
		Serial.println(F("no message"));
		return;
	}

	int bl = simModuleActivity1._simModuleRepository->get_SS_MAX_RX_BUFF();

	char response[bl];

	for (int i = 0; i < 10; i++)
	{
		simModuleActivity1.getSmsByIndex(i);

		if (simModuleActivity1.getSmsResponse(response, bl))
		{
			Serial.println(response);

			if (simModuleActivity1.isCallerAuthorized(response, "+393202445649"))
			{
				Serial.println(F("caller is authorized"));

				if (simModuleActivity1.isSmsOnBuffer(response, 0))
				{
					Serial.println(F("do somethink for 0 command"));
					callTest();
				}
			}
			simModuleActivity1.deleteSmsByIndex(i);
		}
	}
}
