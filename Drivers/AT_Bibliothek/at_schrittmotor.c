#include "at_schrittmotor.h"
#include "defines.h"
#include "dspin.h"
#include "dspin_config.h"
#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "tm_stm32_fonts.h"
#include "tm_stm32_lcd.h"
#include "tm_stm32_spi.h"
#include "tm_stm32_usart.h"
#include "tm_stm32f4_stmpe811.h"

dSPIN_RegsStruct_TypeDef dSPIN_RegsStruct;

void print_data_uart(void);
int at_toff_fast(int us);
int at_ocd_th(int voltage);
int at_step_sel(int step);
/*
 *******************************************************************************
 * Sende Daten an jeweiliges Modul
 *******************************************************************************
 */
int at_dSPIN_Write_Byte(uint8_t byte) {
   uint8_t antwort = 0;

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
}

/*
 *******************************************************************************
 * Schrittmotor Initialisierung mit Connection Check
 *******************************************************************************
 */
uint8_t at_schrittmotor_init(void) {
   uint8_t aktive_module = 0;
   /* Zuerst ein Reset aller Module */
   for (uint8_t i = 8; i >= 1; i--) {
      /*ohne diese Verzögerung funktioniert der Treiber nicht korrekt*/
      HAL_Delay(300);

      anschluss = i;
      dSPIN_Reset_Device();
      /*
       * pr�ft ob irgendetwas zur�ck kommt, wenn ja dann ist das modul
       * angesteckt diese Info wird genutzt um bei der Initialisierung
       * auszugeben, welche module aktiv sind. Es wird immer +1 dazugez�hlt und
       * um ein bit nach links geschoben
       */
      HAL_Delay(300);
      if (dSPIN_Get_Status() != 0) {
         aktive_module += 1;
      }

      if (i != 1) {
         aktive_module = aktive_module << 1;
      }
   }
   return aktive_module;
}

/*
 *******************************************************************************
 * Schrittmotor Parametrierungen
 *******************************************************************************
 */
int at_schrittmotor_param(uint8_t option, uint8_t parameter, int wert) {
   if (option == LESEN) {
      at_schrittmotor_get_param(&dSPIN_RegsStruct);
      print_data_uart();
   } else if (option == SCHREIBEN) {
      at_schrittmotor_set_param(parameter, wert);
      dSPIN_Registers_Set(&dSPIN_RegsStruct);
   } else if (option == CONFIG_1) {
      L3518_init(&dSPIN_RegsStruct);
      dSPIN_Registers_Set(&dSPIN_RegsStruct);
   } else if (option == CONFIG_2) {
      LSP1518_init(&dSPIN_RegsStruct);
      dSPIN_Registers_Set(&dSPIN_RegsStruct);
   }
   // ich k�nnte die funktion als int deklarieren udn den wert 0 zur�ck schicken
   // der wird dann dazu benutzt um den anschluss auf 0 zu setzen
   return 0;
}

/*
 *******************************************************************************
 * Schrittmotor Parameter fuer L3518 (großer Schrittmotor)
 *******************************************************************************
 */
void L3518_init(dSPIN_RegsStruct_TypeDef* dSPIN_RegsStruct) {
   dSPIN_RegsStruct->ABS_POS = 0;
   dSPIN_RegsStruct->EL_POS = 0;
   dSPIN_RegsStruct->MARK = 0;
   dSPIN_RegsStruct->ACC = AccDec_Steps_to_Par(2008); //steps/s
   dSPIN_RegsStruct->DEC = AccDec_Steps_to_Par(2008); //steps/s
   dSPIN_RegsStruct->MAX_SPEED = MaxSpd_Steps_to_Par(500);//steps/s
   dSPIN_RegsStruct->MIN_SPEED = MinSpd_Steps_to_Par(0);//steps/s
   dSPIN_RegsStruct->FS_SPD = FSSpd_Steps_to_Par(100);//steps/s
   dSPIN_RegsStruct->TVAL_HOLD = Tval_Current_to_Par(200); //mA
   dSPIN_RegsStruct->TVAL_RUN = Tval_Current_to_Par(200); //mA
   dSPIN_RegsStruct->TVAL_ACC = Tval_Current_to_Par(200); //mA
   dSPIN_RegsStruct->TVAL_DEC = Tval_Current_to_Par(200); //mA
   dSPIN_RegsStruct->T_FAST = dSPIN_TOFF_FAST_20us; //us
   dSPIN_RegsStruct->TON_MIN = Tmin_Time_to_Par(20); //us
   dSPIN_RegsStruct->TOFF_MIN = Tmin_Time_to_Par(20); //us
   dSPIN_RegsStruct->OCD_TH = dSPIN_OCD_TH_375mA; //mA
   // dSPIN_RegsStruct->OCD_TH = dSPIN_OCD_TH_1125mA;
   dSPIN_RegsStruct->STEP_MODE = 0x08 | dSPIN_STEP_SEL_1_16;
   dSPIN_RegsStruct->ALARM_EN = 0xFF;
   dSPIN_RegsStruct->CONFIG = 0x2E88;
}

/*
 *******************************************************************************
 * Schrittmotor Parameter fuer LSP1518 (kleiner Schrittmotor)
 *******************************************************************************
 */
void LSP1518_init(dSPIN_RegsStruct_TypeDef* dSPIN_RegsStruct) {
   dSPIN_RegsStruct->ABS_POS = 0;
   dSPIN_RegsStruct->EL_POS = 0;
   dSPIN_RegsStruct->MARK = 0;
   dSPIN_RegsStruct->ACC = AccDec_Steps_to_Par(2008);
   dSPIN_RegsStruct->DEC = AccDec_Steps_to_Par(2008);
   dSPIN_RegsStruct->MAX_SPEED = MaxSpd_Steps_to_Par(500);
   dSPIN_RegsStruct->MIN_SPEED = MinSpd_Steps_to_Par(0);
   dSPIN_RegsStruct->FS_SPD = FSSpd_Steps_to_Par(500);
   dSPIN_RegsStruct->TVAL_HOLD = Tval_Current_to_Par(200);
   dSPIN_RegsStruct->TVAL_RUN = Tval_Current_to_Par(200);
   dSPIN_RegsStruct->TVAL_ACC = Tval_Current_to_Par(200);
   dSPIN_RegsStruct->TVAL_DEC = Tval_Current_to_Par(200);
   dSPIN_RegsStruct->T_FAST = dSPIN_TOFF_FAST_10us;
   dSPIN_RegsStruct->TON_MIN = Tmin_Time_to_Par(20);
   dSPIN_RegsStruct->TOFF_MIN = Tmin_Time_to_Par(20);
   dSPIN_RegsStruct->OCD_TH = dSPIN_OCD_TH_375mA;
   // dSPIN_RegsStruct->OCD_TH = dSPIN_OCD_TH_750mA;
   dSPIN_RegsStruct->STEP_MODE = 0x08 | dSPIN_STEP_SEL_1_2;
   dSPIN_RegsStruct->ALARM_EN = 0xFF;
   dSPIN_RegsStruct->CONFIG = 0x2E88;
}

/*
 *******************************************************************************
 * Lade Parameter aus Schrittmotor in Struct
 *******************************************************************************
 */
void at_schrittmotor_get_param(dSPIN_RegsStruct_TypeDef* dSPIN_RegsStruct) {
   for (uint8_t i = 1; i <= 27; i++) {
      HAL_Delay(50);
      switch (i) {
         case 1:
            dSPIN_RegsStruct->ABS_POS = dSPIN_Get_Param(i);
            break;
         case 2:
            dSPIN_RegsStruct->EL_POS = dSPIN_Get_Param(i);
            break;
         case 3:
            dSPIN_RegsStruct->MARK = dSPIN_Get_Param(i);
            break;
         case 5:
            dSPIN_RegsStruct->ACC = dSPIN_Get_Param(i);
            break;
         case 6:
            dSPIN_RegsStruct->DEC = dSPIN_Get_Param(i);
            break;
         case 7:
            dSPIN_RegsStruct->MAX_SPEED = dSPIN_Get_Param(i);
            break;
         case 8:
            dSPIN_RegsStruct->MIN_SPEED = dSPIN_Get_Param(i);
            break;
         case 21:
            dSPIN_RegsStruct->FS_SPD = dSPIN_Get_Param(i);
            break;
         case 9:
            dSPIN_RegsStruct->TVAL_HOLD = dSPIN_Get_Param(i);
            break;
         case 10:
            dSPIN_RegsStruct->TVAL_RUN = dSPIN_Get_Param(i);
            break;
         case 11:
            dSPIN_RegsStruct->TVAL_ACC = dSPIN_Get_Param(i);
            break;
         case 12:
            dSPIN_RegsStruct->TVAL_DEC = dSPIN_Get_Param(i);
            break;
         case 14:
            dSPIN_RegsStruct->T_FAST = dSPIN_Get_Param(i);
            break;
         case 15:
            dSPIN_RegsStruct->TON_MIN = dSPIN_Get_Param(i);
            break;
         case 16:
            dSPIN_RegsStruct->TOFF_MIN = dSPIN_Get_Param(i);
            break;
         case 19:
            dSPIN_RegsStruct->OCD_TH = dSPIN_Get_Param(i);
            break;
         case 22:
            dSPIN_RegsStruct->STEP_MODE = dSPIN_Get_Param(i);
            break;
         case 23:
            dSPIN_RegsStruct->ALARM_EN = dSPIN_Get_Param(i);
            break;
         case 24:
            dSPIN_RegsStruct->CONFIG = dSPIN_Get_Param(i);
            break;
         default:
            break;
      }
   }
}

/*
 *******************************************************************************
 * Schreibe Parameter aus Struct in Schrittmotor
 *******************************************************************************
 */
void at_schrittmotor_set_param(uint8_t parameter, int wert) {
   switch (parameter) {
      case 1:
         dSPIN_RegsStruct.ABS_POS = wert;
         break;
      case 2:
         dSPIN_RegsStruct.EL_POS = wert;
         break;
      case 3:
         dSPIN_RegsStruct.MARK = wert;
         break;
      case 5:
         dSPIN_RegsStruct.ACC = AccDec_Steps_to_Par(wert);
         break;
      case 6:
         dSPIN_RegsStruct.DEC = AccDec_Steps_to_Par(wert);
         break;
      case 7:
         dSPIN_RegsStruct.MAX_SPEED = MaxSpd_Steps_to_Par(wert);
         break;
      case 8:
         dSPIN_RegsStruct.MIN_SPEED = MinSpd_Steps_to_Par(wert);
         break;
      case 21:
         dSPIN_RegsStruct.FS_SPD = FSSpd_Steps_to_Par(wert);
         break;
      case 9:
         dSPIN_RegsStruct.TVAL_HOLD = Tval_Current_to_Par(wert);
         break;
      case 10:
         dSPIN_RegsStruct.TVAL_RUN = Tval_Current_to_Par(wert);
         break;
      case 11:
         dSPIN_RegsStruct.TVAL_ACC = Tval_Current_to_Par(wert);
         break;
      case 12:
         dSPIN_RegsStruct.TVAL_DEC = Tval_Current_to_Par(wert);
         break;
      case 14:
         dSPIN_RegsStruct.T_FAST = at_toff_fast(wert);
         break;
      case 15:
         dSPIN_RegsStruct.TON_MIN = Tmin_Time_to_Par(wert);
         break;
      case 16:
         dSPIN_RegsStruct.TOFF_MIN = Tmin_Time_to_Par(wert);
         break;
      case 19:
         dSPIN_RegsStruct.OCD_TH = at_ocd_th(wert);
         break;
      case 22:
         dSPIN_RegsStruct.STEP_MODE = at_step_sel(wert);
         break;
      case 23:
         dSPIN_RegsStruct.ALARM_EN = wert;
         break;
      case 24:
         dSPIN_RegsStruct.CONFIG = wert;
         break;
      default:
         break;
   }
}

/*
 ******************************************************************************
 * Schrittmotor Abläufe
 ******************************************************************************
 */

/* Run */
void at_schrittmotor_run(uint8_t FWDREV, uint8_t speed) {
   dSPIN_Run(FWDREV, Speed_Steps_to_Par(speed));
}

/* Stop */
void at_schrittmotor_stop(void) { dSPIN_Soft_Stop(); }

/* Off */
void at_schrittmotor_off(void) { dSPIN_Soft_HiZ(); }

/* Step */
void at_schrittmotor_step(void) {
   // hier hab ich wieder einen schei� beinand weil die expander ports
   // nicht mit den tats�chlichen modulen �bereinstimmen...
   at_stck(anschluss);
}

/* Print Parameter to UART */
void print_data_uart(void) {
   UART_INFO("1 : ABS_POS     %ld", dSPIN_RegsStruct.ABS_POS);
   UART_INFO("2 : EL_POS:     %d", dSPIN_RegsStruct.EL_POS);
   UART_INFO("3 : MARK:       %ld", dSPIN_RegsStruct.MARK);
   UART_INFO("5 : ACC:        %dsteps/s", dSPIN_RegsStruct.ACC);
   UART_INFO("6 : DEC:        %dsteps/s", dSPIN_RegsStruct.DEC);
   UART_INFO("7 : MAX_SPEED:  %dsteps/s", dSPIN_RegsStruct.MAX_SPEED);
   UART_INFO("8 : MIN_SPEED:  %dsteps/s", dSPIN_RegsStruct.MIN_SPEED);
   UART_INFO("21: FS_SPD:     %dsteps/s", dSPIN_RegsStruct.FS_SPD);
   UART_INFO("9 : TVAL_HOLD:  %dmA", dSPIN_RegsStruct.TVAL_HOLD);
   UART_INFO("10: TVAL_RUN:   %dmA", dSPIN_RegsStruct.TVAL_RUN);
   UART_INFO("11: TVAL_ACC:   %dmA", dSPIN_RegsStruct.TVAL_ACC);
   UART_INFO("12: TVAL_DEC:   %dmA", dSPIN_RegsStruct.TVAL_DEC);
   UART_INFO("14: T_FAST:     %dus", dSPIN_RegsStruct.T_FAST);
   UART_INFO("15: TON_MIN:    %dus", dSPIN_RegsStruct.TON_MIN);
   UART_INFO("16: TOFF_MIN:   %dus", dSPIN_RegsStruct.TOFF_MIN);
   UART_INFO("19: OCD_TH:     %dmA", dSPIN_RegsStruct.OCD_TH);
   UART_INFO("22: STEP_MODE:  %d", dSPIN_RegsStruct.STEP_MODE);
   UART_INFO("23: ALARM_EN:   %d", dSPIN_RegsStruct.ALARM_EN);
   UART_INFO("24: CONFIG:     " BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(dSPIN_RegsStruct.CONFIG));
}



/*
 ******************************************************************************
 * LCD Ausgabe, Bedienung mittels Blauen Taster (to be deleted)
 ******************************************************************************
 */
void at_schrittmotor_print_data(uint8_t data) {
   switch (data) {
      case CONFIG_1: {
         L3518_init(&dSPIN_RegsStruct);
         LCD_INFO("Standardparameter: L3518");
      } break;
      case CONFIG_2: {
         LSP1518_init(&dSPIN_RegsStruct);
         LCD_INFO("Standardparameter: LSP1518");
      } break;
      case 1: {
         at_schrittmotor_get_param(&dSPIN_RegsStruct);
         LCD_INFO("Parameter von Modul: %d", anschluss);
      } break;
      default:
         break;
   }

   LCD_INFO("ABS_POS:    %ld", dSPIN_RegsStruct.ABS_POS);
   LCD_INFO("EL_POS:     %d", dSPIN_RegsStruct.EL_POS);
   LCD_INFO("MARK:       %ld", dSPIN_RegsStruct.MARK);
   LCD_INFO("ACC:        %d", dSPIN_RegsStruct.ACC);
   LCD_INFO("DEC:        %d", dSPIN_RegsStruct.DEC);
   LCD_INFO("MAX_SPEED:  %d", dSPIN_RegsStruct.MAX_SPEED);
   LCD_INFO("MIN_SPEED:  %d", dSPIN_RegsStruct.MIN_SPEED);
   LCD_INFO("FS_SPD:     %d", dSPIN_RegsStruct.FS_SPD);
   LCD_INFO("TVAL_HOLD:  %d", dSPIN_RegsStruct.TVAL_HOLD);
   LCD_INFO("TVAL_RUN:   %d", dSPIN_RegsStruct.TVAL_RUN);
   LCD_INFO("TVAL_ACC:   %d", dSPIN_RegsStruct.TVAL_ACC);
   LCD_INFO("TVAL_DEC:   %d", dSPIN_RegsStruct.TVAL_DEC);
   LCD_INFO("T_FAST:     %d", dSPIN_RegsStruct.T_FAST);
   LCD_INFO("TON_MIN:    %d", dSPIN_RegsStruct.TON_MIN);
   LCD_INFO("TOFF_MIN:   %d", dSPIN_RegsStruct.TOFF_MIN);
   LCD_INFO("OCD_TH:     %d", dSPIN_RegsStruct.OCD_TH);
   LCD_INFO("STEP_MODE:  %d", dSPIN_RegsStruct.STEP_MODE);
   LCD_INFO("ALARM_EN:   %d", dSPIN_RegsStruct.ALARM_EN);
   LCD_INFO("CONFIG:     " BYTE_TO_BINARY_PATTERN,
            BYTE_TO_BINARY(dSPIN_RegsStruct.CONFIG));
}

int at_toff_fast(int us) {
   switch (us) {
      case 2:
         return (((uint8_t)0x00) << 4);
      case 4:
         return (((uint8_t)0x01) << 4);
      case 6:
         return (((uint8_t)0x02) << 4);
      case 8:
         return (((uint8_t)0x03) << 4);
      case 10:
         return (((uint8_t)0x04) << 4);
      case 12:
         return (((uint8_t)0x05) << 4);
      case 14:
         return (((uint8_t)0x06) << 4);
      case 16:
         return (((uint8_t)0x07) << 4);
      case 18:
         return (((uint8_t)0x08) << 4);
      case 20:
         return (((uint8_t)0x09) << 4);
      case 22:
         return (((uint8_t)0x0A) << 4);
      case 24:
         return (((uint8_t)0x0B) << 4);
      case 26:
         return (((uint8_t)0x0C) << 4);
      case 28:
         return (((uint8_t)0x0D) << 4);
      case 30:
         return (((uint8_t)0x0E) << 4);
      case 32:
         return (((uint8_t)0x0F) << 4);
      default:
         break;
   }
   return 0;
}

int at_ocd_th(int voltage) {
   switch (voltage) {
      case 375:
         return ((uint8_t)0x00);
      case 750:
         return ((uint8_t)0x01);
      case 125:
         return ((uint8_t)0x02);
      case 1500:
         return ((uint8_t)0x03);
      case 1875:
         return ((uint8_t)0x04);
      case 2250:
         return ((uint8_t)0x05);
      case 2625:
         return ((uint8_t)0x06);
      case 3000:
         return ((uint8_t)0x07);
      case 3375:
         return ((uint8_t)0x08);
      case 3750:
         return ((uint8_t)0x09);
      case 4125:
         return ((uint8_t)0x0A);
      case 4500:
         return ((uint8_t)0x0B);
      case 4875:
         return ((uint8_t)0x0C);
      case 5250:
         return ((uint8_t)0x0D);
      case 5625:
         return ((uint8_t)0x0E);
      default:
         break;
   }
   return 0;
}

int at_step_sel(int step) {
   switch (step) {
      case 1:
         return ((uint8_t)(0x08 | 0x00));
      case 2:
         return ((uint8_t)(0x08 | 0x01));
      case 4:
         return ((uint8_t)(0x08 | 0x02));
      case 8:
         return ((uint8_t)(0x08 | 0x03));
      case 16:
         return ((uint8_t)(0x08 | 0x04));
      default:
         break;
   }
   return 0;
}
