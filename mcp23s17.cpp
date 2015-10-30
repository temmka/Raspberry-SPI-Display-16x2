/*
 * mcp23s17.cpp
 *
 *  Created on: 30 окт. 2015
 *      Author: temmka
 */

#include "mcp23s17.h"

static const unsigned char EXP_IODIRA = 0x00;
static const unsigned char EXP_IODIRB = 0x01;
static const unsigned char EXP_IPOLA	 = 0x02;
static const unsigned char EXP_IPOLB	 = 0x03;
static const unsigned char EXP_GPINTENA = 0x04;
static const unsigned char EXP_GPINTENB = 0x05;
static const unsigned char EXP_DEFVALA	 = 0x06;
static const unsigned char EXP_DEFVALB	 = 0x07;
static const unsigned char EXP_INTCONA	 = 0x08;
static const unsigned char EXP_INTCONB	 = 0x09;
static const unsigned char EXP_IOCONA = 0x0A;
static const unsigned char EXP_IOCONB = 0x0B;
static const unsigned char EXP_GPPUA	 = 0x0C;
static const unsigned char EXP_GPPUB	 = 0x0D;
static const unsigned char EXP_INTFA	 = 0x0E;
static const unsigned char EXP_INTFB	 = 0x0F;
static const unsigned char EXP_INTCAPA	 = 0x10;
static const unsigned char EXP_INTCAPB	 = 0x11;
static const unsigned char EXP_GPIOA = 0x12;
static const unsigned char EXP_GPIOB = 0x13;
static const unsigned char EXP_OLATA	 = 0x14;
static const unsigned char EXP_OLATB	 = 0x15;

mcp23s17::mcp23s17() {
	deviceAddress = 0;

}

mcp23s17::~mcp23s17() {
	// TODO Auto-generated destructor stub
}


unsigned char mcp23s17::regRead(unsigned char reg)
{
	senBuf[0]=(deviceAddress << 1) | 0x41;
	senBuf[1]=reg;
	bcm2835_spi_transfernb(senBuf,&rcvByte,2);

	return rcvByte;

}
void mcp23s17::regWrite(unsigned char reg, unsigned char data)
{
	senBuf[0]=(deviceAddress << 1) | 0x40;
	senBuf[1]=reg;
	senBuf[2]=data;
	 bcm2835_spi_transfernb(senBuf,&rcvByte,3);
}


void mcp23s17::writeA(unsigned char data)
{
	regWrite(EXP_GPIOA, data);
}

void mcp23s17::writeB(unsigned char data)
{
	regWrite(EXP_GPIOB, data);
}

unsigned char mcp23s17::readA()
{
	return regRead(EXP_GPIOA);
}


unsigned char mcp23s17::readB()
{
	return regRead(EXP_GPIOB);
}


unsigned short mcp23s17::readAB()
{
	return (readB() << 8) | readA();
}

void mcp23s17::writeAB(unsigned short data)
{
	writeA(data & 0xFF);
	writeB(data >> 8);

}

void mcp23s17::Init(uint8_t portA, uint8_t portB)
{
	regWrite(EXP_IOCONA, 0x08);
	regWrite(EXP_IOCONB, 0x08);

	regWrite(EXP_IODIRA, portA);
	regWrite(EXP_IODIRB, portB);

}

void mcp23s17::writeBit(unsigned char BitNumber, unsigned char Value)
{

	if (BitNumber < 8)
	{
		writeA((readA() & ~(1 << BitNumber)) | (Value << BitNumber));
	}
	else
	{
		writeB((readB() & ~(1 << (BitNumber - 8))) | (Value << (BitNumber - 8)));
	}

}

unsigned char mcp23s17::readBit(unsigned char BitNumber)
{

	unsigned short Value = readAB();

	if (Value & (1 << BitNumber))
	{
		return 1;
	}
	else
	{
		return 0;
	}



}
