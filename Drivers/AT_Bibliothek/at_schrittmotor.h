/**
 ******************************************************************************
 * @file    at_schrittmotor.h
 * @author  Armin Tirala
 *  @email   a.tirala@gmail.com
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

#include "defines.h"
#include "dspin.h"
#include "dspin_config.h"
#include "stm32f4xx_hal.h"

/*
 * globale Variable hier als extern deklariert
 * w�rde eigentlich in main.h geh�ren...
 */
extern uint8_t anschluss;

// was ist das?
// dSPIN_RegsStruct_TypeDef dSPIN_RegsStruct;

extern int at_dSPIN_Write_Byte(uint8_t byte);
extern uint8_t at_schrittmotor_init(void);
extern int at_schrittmotor_param(uint8_t rw, uint8_t vordefiniert);
void L3518_init(dSPIN_RegsStruct_TypeDef* dSPIN_RegsStruct);
void LSP1518_init(dSPIN_RegsStruct_TypeDef* dSPIN_RegsStruct);
void at_schrittmotor_get_param(dSPIN_RegsStruct_TypeDef* dSPIN_RegsStruct);

extern void at_schritt_konfig(uint8_t schritt);
extern void at_schrittmotor_print_data(uint8_t data);
extern void at_schrittmotor_test(void);
extern void at_schrittmotor_stop(void);
extern void at_schrittmotor_run(uint8_t FWDREV, uint8_t speed);
extern void at_schrittmotor_sync(void);
extern void at_schrittmotor_step(void);

#endif
