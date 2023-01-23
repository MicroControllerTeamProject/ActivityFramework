#include "SoftwareSerialRepository.h"
#include <SoftwareSerial.h>

SoftwareSerial* softwareSerial = nullptr;

SoftwareSerialRepository::SoftwareSerialRepository(uint8_t rx, uint8_t tx, bool inv_logic) {
	this->_rxPin = rx;
	this->_txPin = tx;
	this->invers_logic = inv_logic;
	softwareSerial = new SoftwareSerial(rx, tx, inv_logic);
}

SoftwareSerialRepository::~SoftwareSerialRepository()
{
		delete(softwareSerial);
}

//void SoftwareSerialRepository::init(uint8_t rx, uint8_t tx, bool inv_logic){
//	this->_rxPin = rx;
//	this->_txPin = tx;
//	this->invers_logic = inv_logic;
//	softwareSerial = new SoftwareSerial(rx, tx, inv_logic);
//}

char* SoftwareSerialRepository::readString_m() {
	String responseBufferString = softwareSerial->readString();
	char* charsBufferByReference;
	charsBufferByReference = (char*)calloc(responseBufferString.length(), sizeof(char));
	responseBufferString.toCharArray(charsBufferByReference, responseBufferString.length());
	return charsBufferByReference;
}

//void SoftwareSerialRepository::print_m(const char* data,bool isNewLine = false)
//{
//	if (this->softwareSerial != nullptr)
//	{
//		this->softwareSerial->print(data);
//	}
//}

void SoftwareSerialRepository::print_m(float data)
{
	
		softwareSerial->print(data);

}

void SoftwareSerialRepository::println(const char* data)
{
		softwareSerial->println(data);
}

void SoftwareSerialRepository::println(float data)
{
		softwareSerial->println(data);
}

bool SoftwareSerialRepository::serial_available(){
		if (softwareSerial->available() > 0)
		{
			return true;
		}
}

int SoftwareSerialRepository::read() {
		return softwareSerial->read();
}

void SoftwareSerialRepository::begin_m(unsigned long baud)
{
	softwareSerial->begin(baud);
}
//
//char* SoftwareSerialRepository::readString() {
//	char a[250];
//	char b[500];
//	String c;
//	if (softwareSerial != nullptr)
//	{
//		while (softwareSerial->available() > 0) {
//			c.concat((char)softwareSerial->read());
//		}
//		c.toCharArray(a, c.length());
//		strcpy(b, a);
//		return b;
//	}
//	
//}
//
//char* SoftwareSerialRepository::readBuffer()
//{
//	char a[250];
//	char b[500];
//	String c;
//	if (softwareSerial != nullptr)
//	{
//		c = softwareSerial->readString();
//		c.toCharArray(a, c.length());
//		strcpy(b, a);
//		return b;
//	}
//	
//}
