/*
 *******************************************************************************
 * File:    at_io_expander.h
 * Author:  Armin Tirala
 * Version: V4.1
 * Date:    28.12.2017
 * IDE:     Eclipse Neon.3
 * Note:
 * Expandertreiber
 * Definitionen für den 16 Bit I/O Expander
 * Hier stehen alle Register mit einer klaren Definition drin
 *******************************************************************************
 */

#ifndef AT_IO_EXPANDER_H
#define AT_IO_EXPANDER_H

#include "at_defines.h"
#include "stm32f4xx_hal.h"

/* In Version 2.0 hart verdrahtet */

#define ExpanderA 0x42
#define ExpanderB 0x44

#define OPCODE 0x40
#define IOCON_Bank0 0x0A

/*
 * Registerdefinition
 * Makros für die 16Bit bzw. 8Bit Version
 * Kann man auch verwenden, weiß jedoch nicht ob das
 * mit den Rückgabewerten funktioniert...
 */

/* Bank0 */
#if defined(Expander_16Bit_Mode)

#define IODIRA 0x00
#define IODIRB 0x01
#define IPOLA 0x02
#define IPOLB 0x03
#define GPINTENA 0x04
#define GPINTENB 0x05
#define DEFVALA 0x06
#define DEFVALB 0x07
#define INTCONA 0x08
#define INTCONB 0x09
#define IOCON 0x0A /* alternativ auch 0x0B */
#define GPPUA 0x0C
#define GPPUB 0x0D
#define INTFA 0x0E
#define INTFB 0x0F
#define INTCAPA 0x10
#define INTCAPB 0x11
#define AGPIO 0x12
#define BGPIO 0x13
#define OLATA 0x14
#define OLATB 0x15

/* 8 Bit Modus auch Bank1 genannt */
#else

#define IODIRA 0x00
#define IPOLA 0x01
#define GPINTENA 0x02
#define DEFVALA 0x03
#define INTCONA 0x04
#define IOCON 0x05 /* alternativ auch 0x15 */
#define GPPUA 0x06
#define INTFA 0x07
#define INTCAPA 0x08
#define AGPIO 0x12
#define OLATA 0x0A

#define IODIRB 0x10
#define IPOLB 0x11
#define GPINTENB 0x12
#define DEFVALB 0x13
#define INTCONB 0x14
#define GPPUB 0x16
#define INTFB 0x17
#define INTCAPB 0x18
#define BGPIO 0x19
#define OLATB 0x1A

#endif

typedef enum {
   expander_GPIO_1 = ((uint8_t)0x00),
   expander_GPIO_2 = ((uint8_t)0x01),
   expander_GPIO_3 = ((uint8_t)0x02),
   expander_GPIO_4 = ((uint8_t)0x03),
   expander_GPIO_5 = ((uint8_t)0x04),
   expander_GPIO_6 = ((uint8_t)0x05),
   expander_GPIO_7 = ((uint8_t)0x06),
   expander_GPIO_8 = ((uint8_t)0x07),
} expander_GPIO_TypeDef;

/*
 * Sende Befehle an Expander
 * Befehle werden einzeln verschickt sequp 1,bank 1
 */
extern void at_expander_senddata(uint8_t opcode, uint8_t adress, uint8_t data);

/*
 * Lese Befehle von Expander
 */
extern int at_expander_readdata(uint8_t opcode, uint8_t adress, uint8_t data);

/*
 * nitialisierung der Expander
 */
extern int at_expander_init(void);

/*
 * Testfunktion fuer Expander
 */
extern void at_expander_stck(uint8_t port);
extern void at_expander_reset(void);

#endif
