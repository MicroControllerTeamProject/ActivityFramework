#pragma once
class InterfaceSerialRepository
{
public:
	~InterfaceSerialRepository(){}

	virtual void print_m(const char* data, bool isNewLine = false) = 0;

	virtual void print_m(float data, bool isNewLine = false) = 0;

	virtual void print_m(int data, bool isNewLine = false) = 0;

	virtual void print_m(uint8_t data, bool isNewLine = false) = 0;

	virtual bool serial_available() = 0;

	virtual char* readString_m() = 0;

	virtual void clearBuffer_m() = 0;

	virtual void begin_m(unsigned long baud) = 0;

	virtual int read() = 0;
};

