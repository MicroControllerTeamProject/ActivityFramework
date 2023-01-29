#include "SoftwareSerialRepository.h"
#include <SoftwareSerial.h>
#include <Arduino.h>

SoftwareSerial* _softwareSerial = nullptr;

SoftwareSerialRepository::SoftwareSerialRepository(uint8_t rx, uint8_t tx, bool inv_logic = false) {
	this->_rxPin = rx;
	this->_txPin = tx;
	this->invers_logic = inv_logic;
	_softwareSerial = new SoftwareSerial(rx, tx, inv_logic);
}

SoftwareSerialRepository::~SoftwareSerialRepository()
{
		delete(_softwareSerial);
}

//void SoftwareSerialRepository::init(uint8_t rx, uint8_t tx, bool inv_logic){
//	this->_rxPin = rx;
//	this->_txPin = tx;
//	this->invers_logic = inv_logic;
//	_softwareSerial = new SoftwareSerial(rx, tx, inv_logic);
//}

char* SoftwareSerialRepository::readString_m() {
	String responseBufferString = _softwareSerial->readString();
	char* charsBufferByReference;
	charsBufferByReference = (char*)calloc(responseBufferString.length(), sizeof(char));
	responseBufferString.toCharArray(charsBufferByReference, responseBufferString.length());
	return charsBufferByReference;
}

void SoftwareSerialRepository::clearBuffer_m()
{
	while (_softwareSerial->available() > 0) {
		_softwareSerial->readString();
	}
	_softwareSerial->readString();
}

//void SoftwareSerialRepository::print_m(const char* data,bool isNewLine = false)
//{
//	if (this->_softwareSerial != nullptr)
//	{
//		this->_softwareSerial->print(data);
//	}
//}

//void SoftwareSerialRepository::print_m(float data, bool isNewLine = false)
//{
//	
//		_softwareSerial->print(data);
//
//}

void SoftwareSerialRepository::print_m(int data, bool isNewLine)
{
}

void SoftwareSerialRepository::print_m(uint8_t data, bool isNewLine)
{
}

void SoftwareSerialRepository::print_m(const char* data, bool isNewLine = false)
{
	_softwareSerial->print(data);
	if (isNewLine)_softwareSerial->println();
}

void SoftwareSerialRepository::print_m(float data, bool isNewLine = false)
{
		_softwareSerial->println(data);
}

bool SoftwareSerialRepository::serial_available(){
		if (_softwareSerial->available() > 0)
		{
			return true;
		}
}

int SoftwareSerialRepository::read() {
		return _softwareSerial->read();
}

void SoftwareSerialRepository::begin_m(unsigned long baud)
{
	_softwareSerial->begin(baud);
}
//
//char* SoftwareSerialRepository::readString() {
//	char a[250];
//	char b[500];
//	String c;
//	if (_softwareSerial != nullptr)
//	{
//		while (_softwareSerial->available() > 0) {
//			c.concat((char)_softwareSerial->read());
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
//	if (_softwareSerial != nullptr)
//	{
//		c = _softwareSerial->readString();
//		c.toCharArray(a, c.length());
//		strcpy(b, a);
//		return b;
//	}
//	
//}
