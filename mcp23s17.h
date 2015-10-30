/*
 * mcp23s17.h
 *
 *  Created on: 30 окт. 2015
 *      Author: temmka
 */

#include "bcm2835.h"


#ifndef MCP23S17_H_
#define MCP23S17_H_



class mcp23s17 {
public:
	mcp23s17();
	virtual ~mcp23s17();

	unsigned char regRead(unsigned char port);
	void regWrite(unsigned char reg, unsigned char data);

	unsigned char readA();
	unsigned char readB();
	unsigned short readAB();

	void writeA(unsigned char data);
	void writeB(unsigned char data);
	void writeAB(unsigned short data);

	void Init(uint8_t portA, uint8_t portB);

	void writeBit(unsigned char BitNumber, unsigned char Value);
	unsigned char readBit(unsigned char BitNumber);

	unsigned char deviceAddress;
	char senBuf[3];
	char rcvByte;

};

#endif /* MCP23S17_H_ */
