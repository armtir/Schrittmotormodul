/**
  ******************************************************************************
  * @file    at_schrittmotor.h 
  * @author  Armin Tirala
	*	@email   a.tirala@gmail.com
  * @version V1.0
  * @date    16.05.2017
	* @ide     Keil uVision V5.23.0.0
  * @brief   Schrittmotor-Headerfile
  * @note    Hier stehen nur selbstgeschriebene Funktionen
	* zur Ansteuerung der Schrittmotoren drin.
  * ***do not edit***
  ******************************************************************************
 */

#ifndef _USE_SCHRITTMOTOR_H	
#define _USE_SCHRITTMOTOR_H

#include "stm32f4xx_hal.h"
#include "defines.h"
#include "dspin.h"
#include "dspin_config.h"

//externe Variable, steht in main.c
extern uint8_t anschluss;
//dSPIN_RegsStruct_TypeDef dSPIN_RegsStruct;


extern int at_dSPIN_Write_Byte(uint8_t byte);

extern void at_schritt_konfig(uint8_t schritt);

extern void L3518_init               (dSPIN_RegsStruct_TypeDef* dSPIN_RegsStruct);
extern void LSP1518_init             (dSPIN_RegsStruct_TypeDef* dSPIN_RegsStruct);
       void at_schrittmotor_get_param(dSPIN_RegsStruct_TypeDef* dSPIN_RegsStruct, uint8_t modul);
extern void at_schrittmotor_print_data(uint8_t data);

extern void at_schrittmotor_test(void);
extern void at_schrittmotor_stop(void);

extern void at_schrittmotor_run(void);
extern void at_schrittmotor_sync(void);

extern void at_schrittmotor_step(void);

extern void at_schrittmotor_init(void);

#endif
