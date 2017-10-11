#include "at_schrittmotor.h"
#include "defines.h"
#include "stm32f4xx_hal.h"
#include "tm_stm32_lcd.h"
#include "tm_stm32_spi.h"
#include "tm_stm32_fonts.h"
#include "tm_stm32f4_stmpe811.h"
#include "tm_stm32_usart.h"
#include "dspin.h"
#include "dspin_config.h"
#include "stdint.h"

dSPIN_RegsStruct_TypeDef dSPIN_RegsStruct;

int at_dSPIN_Write_Byte(uint8_t byte) {

	uint8_t antwort = 0;
	/*
	 * Anschluss Variable muss global sein weil...
	 * kann ich jetzt nicht mehr sagen...
	 */
	switch (anschluss) {

	case 1: {
		Anschluss_1_CS_AKTIV;
		antwort = TM_SPI_Send(TREIBER_SPI, byte);
		Anschluss_1_CS_INAKTIV;
		return (antwort);
	}
	case 2: {
		Anschluss_2_CS_AKTIV;
		antwort = TM_SPI_Send(TREIBER_SPI, byte);
		Anschluss_2_CS_INAKTIV;
		return (antwort);
	}
	case 3: {
		Anschluss_3_CS_AKTIV;
		antwort = TM_SPI_Send(TREIBER_SPI, byte);
		Anschluss_3_CS_INAKTIV;
		return (antwort);
	}
	case 4: {
		Anschluss_4_CS_AKTIV;
		antwort = TM_SPI_Send(TREIBER_SPI, byte);
		Anschluss_4_CS_INAKTIV;
		return (antwort);
	}
	case 5: {
		Anschluss_5_CS_AKTIV;
		antwort = TM_SPI_Send(TREIBER_SPI, byte);
		Anschluss_5_CS_INAKTIV;
		return (antwort);
	}
	case 6: {
		Anschluss_6_CS_AKTIV;
		antwort = TM_SPI_Send(TREIBER_SPI, byte);
		Anschluss_6_CS_INAKTIV;
		return (antwort);
	}
	case 7: {
		Anschluss_7_CS_AKTIV;
		antwort = TM_SPI_Send(TREIBER_SPI, byte);
		Anschluss_7_CS_INAKTIV;
		return (antwort);
	}
	case 8: {
		Anschluss_8_CS_AKTIV;
		antwort = TM_SPI_Send(TREIBER_SPI, byte);
		Anschluss_8_CS_INAKTIV;
		return (antwort);
	}
	default:
		break;
	}

	return (1);
}

void at_schrittmotor_init(void) {

/* Zuerst ein Reset aller Module */
for(uint8_t i=1; i<=8;i++){
/*ohne diese Verzögerung funktioniert der Treiber nicht korrekt*/
	HAL_Delay(100);
	anschluss = i;
	dSPIN_Reset_Device();
	dSPIN_Get_Status();
}
HAL_Delay(100);

anschluss = 1;
	//dSPIN_Reset_Device();
	//HAL_Delay(100);

//dSPIN_Regs_Struct_Reset(&dSPIN_RegsStruct); braucht man nicht

/*klein*/
	LSP1518_init       (&dSPIN_RegsStruct);
	dSPIN_Registers_Set(&dSPIN_RegsStruct);

/*gross*/
//L3518_init(&dSPIN_RegsStruct);	
//dSPIN_Registers_Set(&dSPIN_RegsStruct);	
}

/******************************************************************************
 * Standard Schrittmotor Parametrierungen
 ******************************************************************************
 * Diese Definition ist zwar sch�n und gut aber man brauch hier eine Klasse
 * Man soll ja auch �ber UART das ganze steuern k�nnen
 * Achso die Klasse ist ja schon da!!
 */

/* 
 * Gro�er Schrittmotor L3518
 * Standardparametrierung
 * Selbst getestet und ausgedacht
 */
void L3518_init(dSPIN_RegsStruct_TypeDef* dSPIN_RegsStruct) {

	dSPIN_RegsStruct->ABS_POS   = 0;
	dSPIN_RegsStruct->EL_POS    = 0;
	dSPIN_RegsStruct->MARK      = 0;
	dSPIN_RegsStruct->ACC       = AccDec_Steps_to_Par(2008);
	dSPIN_RegsStruct->DEC       = AccDec_Steps_to_Par(2008);
	dSPIN_RegsStruct->MAX_SPEED = MaxSpd_Steps_to_Par (500);
	dSPIN_RegsStruct->MIN_SPEED = MinSpd_Steps_to_Par   (0);
	dSPIN_RegsStruct->FS_SPD    = FSSpd_Steps_to_Par  (100);
	dSPIN_RegsStruct->TVAL_HOLD = Tval_Current_to_Par (200);
	dSPIN_RegsStruct->TVAL_RUN  = Tval_Current_to_Par (200);
	dSPIN_RegsStruct->TVAL_ACC  = Tval_Current_to_Par (200);
	dSPIN_RegsStruct->TVAL_DEC  = Tval_Current_to_Par (200);
	dSPIN_RegsStruct->T_FAST    = dSPIN_TOFF_FAST_20us;
	dSPIN_RegsStruct->TON_MIN   = Tmin_Time_to_Par     (20);
	dSPIN_RegsStruct->TOFF_MIN  = Tmin_Time_to_Par     (20);
	//dSPIN_RegsStruct->OCD_TH	= dSPIN_OCD_TH_375mA;
	dSPIN_RegsStruct->OCD_TH    = dSPIN_OCD_TH_1125mA;
	dSPIN_RegsStruct->STEP_MODE = 0x08 | dSPIN_STEP_SEL_1_16;
	dSPIN_RegsStruct->ALARM_EN  = 0xFF;
	dSPIN_RegsStruct->CONFIG    = 0x2E88;
}

/* 
 * Kleiner Schrittmotor LSP1518
 * Standardparametrierung
 * Selbst getestet und ausgedacht
 */
void LSP1518_init(dSPIN_RegsStruct_TypeDef* dSPIN_RegsStruct) {

	dSPIN_RegsStruct->ABS_POS   = 0;
	dSPIN_RegsStruct->EL_POS    = 0;
	dSPIN_RegsStruct->MARK      = 0;
	dSPIN_RegsStruct->ACC       = AccDec_Steps_to_Par(2008);
	dSPIN_RegsStruct->DEC       = AccDec_Steps_to_Par(2008);
	dSPIN_RegsStruct->MAX_SPEED = MaxSpd_Steps_to_Par (500);
	dSPIN_RegsStruct->MIN_SPEED = MinSpd_Steps_to_Par   (0);
	dSPIN_RegsStruct->FS_SPD    = FSSpd_Steps_to_Par  (500);
	dSPIN_RegsStruct->TVAL_HOLD = Tval_Current_to_Par (200);
	dSPIN_RegsStruct->TVAL_RUN  = Tval_Current_to_Par (200);
	dSPIN_RegsStruct->TVAL_ACC  = Tval_Current_to_Par (200);
	dSPIN_RegsStruct->TVAL_DEC  = Tval_Current_to_Par (200);
	dSPIN_RegsStruct->T_FAST    = dSPIN_TOFF_FAST_10us;
	dSPIN_RegsStruct->TON_MIN   = Tmin_Time_to_Par     (20);
	dSPIN_RegsStruct->TOFF_MIN  = Tmin_Time_to_Par     (20);
	//dSPIN_RegsStruct->OCD_TH  = dSPIN_OCD_TH_375mA;
	dSPIN_RegsStruct->OCD_TH    = dSPIN_OCD_TH_750mA;
	dSPIN_RegsStruct->STEP_MODE = 0x08 | dSPIN_STEP_SEL_1_2;
	dSPIN_RegsStruct->ALARM_EN  = 0xFF;
	dSPIN_RegsStruct->CONFIG    = 0x2E88;
}

void at_schritt_konfig(uint8_t schritt) {

	dSPIN_Reset_Device();
	HAL_Delay(50);

	switch (schritt) {
	case 0:
		dSPIN_RegsStruct.STEP_MODE = 0x8 | dSPIN_STEP_SEL_1;
		break;
	case 1:
		dSPIN_RegsStruct.STEP_MODE = 0x8 | dSPIN_STEP_SEL_1_2;
		break;
	case 4:
		dSPIN_RegsStruct.STEP_MODE = 0x8 | dSPIN_STEP_SEL_1_4;
		break;
	case 8:
		dSPIN_RegsStruct.STEP_MODE = 0x8 | dSPIN_STEP_SEL_1_8;
		break;
	case 16:
		dSPIN_RegsStruct.STEP_MODE = 0x8 | dSPIN_STEP_SEL_1_16;
		break;
	default:
		break;
	}


	dSPIN_Registers_Set(&dSPIN_RegsStruct);

/* Stepclock aktivieren ... überarbeiten!!!*/
	dSPIN_Step_Clock(0x01);
}

/******************************************************************************
 * Schrittmotor Abl�ufe
 ******************************************************************************
 */

void at_schrittmotor_step(void) {
//expandergaudi
}

void at_schrittmotor_test(void) {
	dSPIN_Run(FWD, Speed_Steps_to_Par(5));
}

void at_schrittmotor_stop(void) {
	dSPIN_Soft_Stop();
}

void at_schrittmotor_run(void) {
	dSPIN_Run(FWD, Speed_Steps_to_Par(200));
}

void at_schrittmotor_sync(void) {
	dSPIN_Run(FWD, Speed_Steps_to_Par(50));
	dSPIN_Run(FWD, Speed_Steps_to_Par(20));
}

void at_schrittmotor_print_data(uint8_t data) {

	switch (data) {
	case 101: {
		L3518_init(&dSPIN_RegsStruct);
		LCD_INFO("L3518"); // werte aus dem vordefiniertem register
	}
		break;
	case 102: {
		LSP1518_init(&dSPIN_RegsStruct);
		LCD_INFO("LSP1518"); // werte aus dem vordefiniertem register
	}
		break;
	case 1: {
		at_schrittmotor_get_param(&dSPIN_RegsStruct, 1); // werte aus modul 1
		LCD_INFO("Modul 1");
	}
		break;
	default:
		break;
	}

	LCD_INFO("ABS_POS:    %ld", dSPIN_RegsStruct.ABS_POS);
	LCD_INFO("EL_POS:     %d",  dSPIN_RegsStruct.EL_POS);
	LCD_INFO("MARK:       %ld", dSPIN_RegsStruct.MARK);
	LCD_INFO("ACC:        %d",  dSPIN_RegsStruct.ACC);
	LCD_INFO("DEC:        %d",  dSPIN_RegsStruct.DEC);
	LCD_INFO("MAX_SPEED:  %d",  dSPIN_RegsStruct.MAX_SPEED);
	LCD_INFO("MIN_SPEED:  %d",  dSPIN_RegsStruct.MIN_SPEED);
	LCD_INFO("FS_SPD:     %d",  dSPIN_RegsStruct.FS_SPD);
	LCD_INFO("TVAL_HOLD:  %d",  dSPIN_RegsStruct.TVAL_HOLD);
	LCD_INFO("TVAL_RUN:   %d",  dSPIN_RegsStruct.TVAL_RUN);
	LCD_INFO("TVAL_ACC:   %d",  dSPIN_RegsStruct.TVAL_ACC);
	LCD_INFO("TVAL_DEC:   %d",  dSPIN_RegsStruct.TVAL_DEC);
	LCD_INFO("T_FAST:     %d",  dSPIN_RegsStruct.T_FAST);
	LCD_INFO("TON_MIN:    %d",  dSPIN_RegsStruct.TON_MIN);
	LCD_INFO("TOFF_MIN:   %d",  dSPIN_RegsStruct.TOFF_MIN);
	LCD_INFO("OCD_TH:     %d",  dSPIN_RegsStruct.OCD_TH);
	LCD_INFO("STEP_MODE:  %d",  dSPIN_RegsStruct.STEP_MODE);
	LCD_INFO("ALARM_EN:   %d",  dSPIN_RegsStruct.ALARM_EN);
	LCD_INFO("CONFIG:     "BYTE_TO_BINARY_PATTERN,
			BYTE_TO_BINARY(dSPIN_RegsStruct.CONFIG));

}

void at_schrittmotor_get_param(dSPIN_RegsStruct_TypeDef* dSPIN_RegsStruct,
		uint8_t modul) {

	for (uint8_t i=1; i <= 27; i++) {
		HAL_Delay(100);
		switch (i) {
		case 1:
			dSPIN_RegsStruct->ABS_POS   = dSPIN_Get_Param(i);
			break;
		case 2:
			dSPIN_RegsStruct->EL_POS    = dSPIN_Get_Param(i);
			break;
		case 3:
			dSPIN_RegsStruct->MARK      = dSPIN_Get_Param(i);
			break;
		case 5:
			dSPIN_RegsStruct->ACC       = dSPIN_Get_Param(i);
			break;
		case 6:
			dSPIN_RegsStruct->DEC       = dSPIN_Get_Param(i);
			break;
		case 7:
			dSPIN_RegsStruct->MAX_SPEED = dSPIN_Get_Param(i);
			break;
		case 8:
			dSPIN_RegsStruct->MIN_SPEED = dSPIN_Get_Param(i);
			break;
		case 21:
			dSPIN_RegsStruct->FS_SPD    = dSPIN_Get_Param(i);
			break;
		case 9:
			dSPIN_RegsStruct->TVAL_HOLD = dSPIN_Get_Param(i);
			break;
		case 10:
			dSPIN_RegsStruct->TVAL_RUN  = dSPIN_Get_Param(i);
			break;
		case 11:
			dSPIN_RegsStruct->TVAL_ACC  = dSPIN_Get_Param(i);
			break;
		case 12:
			dSPIN_RegsStruct->TVAL_DEC  = dSPIN_Get_Param(i);
			break;
		case 14:
			dSPIN_RegsStruct->T_FAST    = dSPIN_Get_Param(i);
			break;
		case 15:
			dSPIN_RegsStruct->TON_MIN   = dSPIN_Get_Param(i);
			break;
		case 16:
			dSPIN_RegsStruct->TOFF_MIN  = dSPIN_Get_Param(i);
			break;
		case 19:
			dSPIN_RegsStruct->OCD_TH    = dSPIN_Get_Param(i);
			break;
		case 22:
			dSPIN_RegsStruct->STEP_MODE = dSPIN_Get_Param(i);
			break;
		case 23:
			dSPIN_RegsStruct->ALARM_EN  = dSPIN_Get_Param(i);
			break;
		case 24:
			dSPIN_RegsStruct->CONFIG    = dSPIN_Get_Param(i);
			break;
		default:
			break;
		}
		HAL_Delay(50);

	}

}

