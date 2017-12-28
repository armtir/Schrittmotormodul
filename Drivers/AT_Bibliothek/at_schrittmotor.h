/*
 *******************************************************************************
 * File:    at_schrittmotor.h
 * Author:  Armin Tirala
 * Version: V4.1
 * Date:    28.12.2017
 * IDE:     Eclipse Neon.3
 * Note:
 * Schrittmotor-Headerfile
 * Hier stehen nur selbstgeschriebene Funktionen
 * zur Ansteuerung der Schrittmotoren drin.
 *******************************************************************************
 */

#ifndef AT_SCHRITTMOTOR_H
#define AT_SCHRITTMOTOR_H

#include "at_defines.h"
#include "dspin.h"

void L3518_init(dSPIN_RegsStruct_TypeDef* dSPIN_RegsStruct);
void LSP1518_init(dSPIN_RegsStruct_TypeDef* dSPIN_RegsStruct);
void at_schrittmotor_get_param(dSPIN_RegsStruct_TypeDef* dSPIN_RegsStruct);
void at_schrittmotor_set_param(uint8_t parameter, int wert,
                               dSPIN_RegsStruct_TypeDef* dSPIN_RegsStruct);
void print_data_uart(void);
int at_toff_fast(int us);
int at_ocd_th(int voltage);
int at_step_sel(int step);

extern uint8_t anschluss;
extern uint8_t serie[9];

extern void at_schrittmotor_print_data(uint8_t data);
extern void at_schrittmotor_test(void);
extern void at_schrittmotor_stop_hard(void);
extern void at_schrittmotor_stop_soft(void);
extern void at_schrittmotor_off_hard(void);
extern void at_schrittmotor_off_soft(void);
extern void at_schrittmotor_run(uint8_t FWDREV, uint8_t speed);
extern void at_schrittmotor_sync(void);
extern void at_schrittmotor_step(uint8_t FWDREV);


extern int at_dSPIN_Write_Byte(uint8_t byte);
extern int at_schrittmotor_param(uint8_t option, uint8_t parameter, int wert);
extern void at_schritt_konfig(uint8_t schritt);
extern uint8_t at_schrittmotor_init(void);
extern void at_schrittmotor_move(uint8_t FWDREV, uint32_t n_step);


/* Umrechnung der Konfigurationsparameter */
/* Speed conversion, range 0 to 15625 stepss */
#define Speed_Steps_to_Par_print(steps) ((uint32_t)((steps - 0.5) / 67.108864))

/* Acc/Dec rates conversion,range 14.55 to 59590  steps/s2 */
#define AccDec_Steps_to_Par_print(steps) \
   ((uint32_t)(steps / 0.068719476736 + 0.5))

/* Max Speed conversion, range 15.25 to 15610 steps/s */
#define MaxSpd_Steps_to_Par_print(steps) ((uint32_t)(steps / 0.065536 + 0.5))

/* Min Speed conversion, range 0 to 976.3 steps/s */
#define MinSpd_Steps_to_Par_print(steps) ((uint32_t)((steps + 0.5) / 4.194304))

/* Full Step Speed conversion, range 7.63 to 15625 steps/s */
#define FSSpd_Steps_to_Par_print(steps) ((uint32_t)(steps / 0.065536 + 0.5))

/* Torque regulation DAC    current conversion, range  31.25mA to 4000mA */
#define Tval_Current_to_Par_print(Tval) \
   ((uint32_t)(((Tval - 0.5) * 31.25) + 31.25))

/* Minimum time conversion, range 0.5us to 64us */
#define Tmin_Time_to_Par_print(Tmin) \
   ((uint32_t)(((Tmin - 0.5) / 2) + 0.5 + 0.5))

#endif
