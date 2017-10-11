#include "defines.h"
#include "stm32fxxx_hal.h"
#include "at_io_expander.h"
#include "tm_stm32_spi.h"

void at_expander_senddata(uint8_t opcode, uint8_t adress, uint8_t data) {
	Expander_CS_AKTIV;
	TM_SPI_Send(EXPANDER_SPI, opcode);
	TM_SPI_Send(EXPANDER_SPI, adress);
	TM_SPI_Send(EXPANDER_SPI, data);
	Expander_CS_INAKTIV;
}

int at_expander_readdata(uint8_t opcode, uint8_t adress, uint8_t data) {
	uint8_t antwort = 0;
	Expander_CS_AKTIV;
	TM_SPI_Send(EXPANDER_SPI, opcode | 1);
	TM_SPI_Send(EXPANDER_SPI, adress);
	antwort = TM_SPI_Send(EXPANDER_SPI, data);
	Expander_CS_INAKTIV;

	return (antwort);
}

void at_expander_init(void) {

	Expander_CS_INAKTIV;

/*
 * iocon registers
 * Bit 7 Bank   1	--> 8Bit modus
 * Bit 6 Mirror 0	--> INTA getrennt von INTB
 * Bit 5 Seqop  1	--> sequenzielle Konfig. AUS
 * Bit 4 DISSLW 1	--> Slewrate MISO control disabled
 * Bit 3 HAEN   1	--> Adresspins enabled
 * Bit 2 ODR    0	--> Interupt als Treiberausgang
 * Bit 1 INTPOL 1	--> Intpol high
 * Bit 0			--> unimplemented 0
 * 10111010			--> 0xBA
 *
 *                      opcode, adress, data
 * at_expander_senddata(0x40  , 0x0A  , 0xBA);
 */

/* Parametrierung via IOCON Register */
	at_expander_senddata(OPCODE, IOCON_Bank0, 0xEA);

/*
 * Mit INTERRUPT FLAG REGISTER Pin auslesen
 */

/*
 * Expander A
 * Register A0-A7 Interupt "Flag"
 * Interuptflag A setzen Active-High
 * NVIC Priorit�t hoch --> 2
 */
//	at_expander_senddata(ExpanderA, IODIRA,   0xff); /* Alle als Eingang setzen*/
	at_expander_senddata(ExpanderA, GPINTENA, 0xff); /* Interupt alle ein bei Flankenwechsel*/
	at_expander_senddata(ExpanderA, DEFVALA,  0x00); /* nur initialisiert*/
	at_expander_senddata(ExpanderA, INTCONA,  0x00); /* Vergleichswert vorheriger Wert*/
	at_expander_readdata(ExpanderA, INTFA,    0x00);
	at_expander_readdata(ExpanderA, INTCAPA,  0x00); //Quitieren

	at_expander_senddata(ExpanderA, IODIRB,   0x00);
	at_expander_senddata(ExpanderA, GPIOBx,   0x00);

	HAL_Delay(10);

/*
 * Expander A
 * Register B0-B7 GPIO Out "STCK"
 */
	//at_expander_senddata(ExpanderA, IODIRB, 0x00);

/*
 * Expander B
 * Register A0-A7 Interupt "Busy"
 * Interuptflag B setzen Active-High
 * NVIC Priorit�t gering --> 4
 * de ham wos beinand in dem Datenblattl...
 * wir brauchen interrupt on pin
 */
	 // at_expander_senddata(ExpanderB, IODIRA,   0xff); /* Alle als Eingang setzen*/
	at_expander_senddata(ExpanderB, GPINTENA, 0xff); /* Interupt alle ein*/
	at_expander_senddata(ExpanderB, DEFVALA,  0x00); /* Vergleichswert f. Int*/
	at_expander_senddata(ExpanderB, INTCONA,  0x00); /* Vergleichswert DEFVAL*/
	at_expander_readdata(ExpanderB, INTFA,    0x00); // jetzigen STatus auslesen
	at_expander_readdata(ExpanderB, INTCAPA,  0x00); //Quitieren

/*
 * Expander B
 * Register B0 GPIO Out "CLK Enable"
 * Register B1 GPIO Out "Reset Modul 1-4"
 * Register B2 GPIO Out "Reset Modul 5-8"
 */
	//at_expander_senddata(ExpanderB, IODIRB,   0x78);
}


void at_expander_test(void) {
//at_expander_senddata(ExpanderA, GPIOAx, 0x);
//at_expander_senddata(ExpanderB, GPIOAx, 0x10);
}

/*
 * Einfacher TEST ob man damit StepClock bedienen kann...
 * Wird gekübelt
 */
void at_stck(uint8_t port) {

/*
 * Funktioniert 5us dauer
 */
at_expander_senddata(ExpanderA, GPIOBx, port);
at_expander_senddata(ExpanderA, GPIOBx, port);
}

/*
 * Lesen von Registern
 * Wird verbessert
 */
void at_expander_status(void) {

	 uint8_t test = at_expander_readdata(ExpanderB, IOCON, 0x00);
	LCD_INFO("IOCON:\n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(test));
	test =0;
	//test = at_expander_readdata(ExpanderB, INTCAPB, 0x00);
//	LCD_INFO("Interrupt:\n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(test));
}

void at_reset(void){

	at_expander_senddata(ExpanderB, GPIOBx, 0x06);
	HAL_Delay(100);
#ifdef CLK16_enable
		at_expander_senddata(ExpanderB, GPIOBx, 0x01);

#else
		at_expander_senddata(ExpanderB, GPIOBx, 0x00);
#endif
}



