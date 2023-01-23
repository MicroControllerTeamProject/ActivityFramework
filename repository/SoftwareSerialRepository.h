#pragma once
#include <stdint.h>
#include "..\interfaces\InterfaceSerialRepository.h"

class SoftwareSerialRepository : public InterfaceSerialRepository
{
public:
	SoftwareSerialRepository(uint8_t rx, uint8_t tx, bool inv_logic);
	virtual char* readString_m();
	virtual void print_m(float data);
	virtual void println(const char* data);
	virtual void println(float data);
	virtual bool serial_available();
	virtual int read();
	virtual void begin_m(unsigned long baud);
	virtual ~SoftwareSerialRepository();
protected:
	uint8_t _rxPin;
	uint8_t _txPin;
	bool invers_logic;
	
};

