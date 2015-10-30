/*
 * HelloRPiWorld.cpp
 */

#include <iostream>
#include "bcm2835.h"
#include "mcp23s17.h"
#include "LCD8_16x2.h"


int main(int argc, char **argv)
{

	if (!argc)
		return 1;

	if (!bcm2835_init())
		return 1;

	mcp23s17 exp;
	lcd8_16x2 lcdC;

	bcm2835_spi_begin();
	bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
	bcm2835_spi_setDataMode(BCM2835_SPI_MODE1);                   // The default
	bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_4096); // The default
	bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
	bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default


	exp.deviceAddress = 7;
	exp.Init(0x00, 0x00); // Output
	lcdC.exp = &exp;

	lcdC.Init();

	lcdC.clear();
	lcdC.display();
	lcdC.cursor();
	lcdC.blink();
	lcdC.Set_Cursor(0,0);

	for(int i = 1; i < argc; i++){
		lcdC.Write_String(argv[i]);
		lcdC.Write_String(" ");
	}

	bcm2835_spi_end();
	bcm2835_close();
	return 0;
}

