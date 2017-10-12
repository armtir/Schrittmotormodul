#include "defines.h"
#include "stm32fxxx_hal.h"
#include "at_io_expander.h"
#include "tm_stm32_spi.h"

/*
 * SPI lesen und schreiben an Expander
 * Die Funktionen sind im Prinzip die selben. Zwecks der �bersichtlichkeit
 * wurden sie einzeln aufgef�hrt
 * Das muss mit zeigern gehen....
 */
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

int at_expander_init(void) {

 Expander_CS_INAKTIV;

/*
 * iocon registers
 * Bit 7 Bank   1 --> 8Bit modus
 * Bit 6 Mirror 0 --> INTA getrennt von INTB
 * Bit 5 Seqop  1 --> sequenzielle Konfig. AUS
 * Bit 4 DISSLW 1 --> Slewrate MISO control disabled
 * Bit 3 HAEN   1 --> Adresspins enabled
 * Bit 2 ODR    0 --> Interupt als Treiberausgang
 * Bit 1 INTPOL 1 --> Intpol high
 * Bit 0          --> unimplemented 0
 * 10111010       --> 0xBA
 *
 *                      opcode, adress, data
 * at_expander_senddata(0x40  , 0x0A  , 0xBA);
 */

/* Parametrierung via IOCON Register */
 at_expander_senddata(OPCODE, IOCON_Bank0, 0xEA);

/*
 * Expander A
 * Register A0-A7 Interupt "Flag"
 * Interuptflag A setzen Active-High
 * NVIC Priorit�t hoch --> 2
 */
//at_expander_senddata(ExpanderA, IODIRA,   0xff); /* Alle als Eingang setzen              */
  at_expander_senddata(ExpanderA, GPINTENA, 0xff); /* Interupt alle ein bei Flankenwechsel */
  at_expander_senddata(ExpanderA, DEFVALA,  0x00); /* nur initialisiert                    */
  at_expander_senddata(ExpanderA, INTCONA,  0x00); /* Vergleichswert vorheriger Wert       */
  at_expander_readdata(ExpanderA, INTFA,    0x00); /* Interupt Status auslesen             */
  at_expander_readdata(ExpanderA, INTCAPA,  0x00); /* Quitieren des Interupts              */

  at_expander_senddata(ExpanderA, IODIRB,   0x00); /* STCK also GPIO OUT f�r alle Pins     */
  at_expander_senddata(ExpanderA, BGPIO,    0x00); /* und dann auf 0 setzen                */

  HAL_Delay(10);

/*
 * Expander B
 * Register A0-A7 Interupt "Busy"
 * Interuptflag B setzen Active-High
 * NVIC Priorit�t gering --> 4
 * De ham wos beinand in dem Datenblattl...
 * Wir brauchen Interrupt On pin
 */
//at_expander_senddata(ExpanderB, IODIRA,   0xff); /* Alle als Eingang setzen              */
  at_expander_senddata(ExpanderB, GPINTENA, 0xff); /* Interupt alle ein bei Flankenwechsel */
  at_expander_senddata(ExpanderB, DEFVALA,  0x00); /* nur initialisiert                    */
  at_expander_senddata(ExpanderB, INTCONA,  0x00); /* Vergleichswert vorheriger Wert       */
  at_expander_readdata(ExpanderB, INTFA,    0x00); /* Interupt Status auslesen             */
  at_expander_readdata(ExpanderB, INTCAPA,  0x00); /* Quitieren des Interupts              */

/*
 * Expander B
 * Register B0 GPIO Out "CLK Enable"
 * Register B1 GPIO Out "Reset Modul 1-4"
 * Register B2 GPIO Out "Reset Modul 5-8"
 */
//at_expander_senddata(ExpanderB, IODIRB,   0x78);
return 0;
}

/*
 * Einfacher TEST ob man damit StepClock bedienen kann...
 * Wird gek�belt
 * Die logisch High Dauer ist ca 5us (gemessen mit Logik Analysator)
 */
void at_stck(uint8_t port) {
 at_expander_senddata(ExpanderA, BGPIO, port);
 at_expander_senddata(ExpanderA, BGPIO, port);
}



/*
 * Alles was jetzt noch kommt ist nicht gut und wird entweder verbessert oder gel�scht
 */
 
/*
 * Lesen von Registern
 * Wird verbessert
 */
void at_expander_status(void) {

  uint8_t test = at_expander_readdata(ExpanderB, IOCON, 0x00);
  LCD_INFO("IOCON:\n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(test));
  test =0;
//test = at_expander_readdata(ExpanderB, INTCAPB, 0x00);
//LCD_INFO("Interrupt:\n"BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(test));
}
/* keine ahnung was ich da vorgehabt habe....*/
void at_reset(void){
  at_expander_senddata(ExpanderB, BGPIO, 0x06);
  HAL_Delay(100);
#ifdef CLK16_enable
    at_expander_senddata(ExpanderB, BGPIO, 0x01);
#else
    at_expander_senddata(ExpanderB, BGPIO, 0x00);
#endif
}



