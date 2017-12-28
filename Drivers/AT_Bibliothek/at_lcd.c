/*
 *******************************************************************************
 * File:    at_lcd.c
 * Author:  Armin Tirala
 * Version: V4.1
 * Date:    28.12.2017
 * IDE:     Eclipse Neon.3
 * Note:
 *******************************************************************************
 */

#include "at_lcd.h"
#include "at_schrittmotor.h"
#include "at_defines.h"
#include "stdint.h"
#include "stm32f4xx_hal.h"
#include "tm_stm32_lcd.h"

/*
 *******************************************************************************
 * Initialisierung LCD 240x320 Pixel
 *******************************************************************************
 */
void at_lcd_init(TM_STMPE811_t* LCD_Config) {
   /* Initialisiere Touch und Display*/
   TM_LCD_Init();

   /* ausrichtung der touch einheit Select touch screen orientation */
   LCD_Config->orientation = TM_STMPE811_Orientation_Portrait_2;

   /* Initialisiere und prüfe ob Touch OK */
   if (TM_STMPE811_Init() != TM_STMPE811_State_Ok) {
      at_lcd_error();
   }
}

/*
 *******************************************************************************
 * Fußzeile
 *******************************************************************************
 */
/* Currently, these fonts are supported:
 *  - 7 x 10 pixels
 *  - 11 x 18 pixels
 *  - 16 x 26 pixels
 */
void at_lcd_fusszeile(void) {
   TM_LCD_Fill(LCD_COLOR_WHITE);
   TM_LCD_SetFont(&TM_Font_11x18);
   TM_LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_WHITE);
   // TM_LCD_SetXY(4, 180);

   TM_LCD_DrawLine(0, 301, 240, 301, LCD_COLOR_BLACK);
   TM_LCD_SetXY(0, 302);

   switch (aktuelle_seite) {
      case 1:
         LCD_INFO("%d/%d Run Modus", aktuelle_seite, MAX_SEITE);
         break;
      case 2:
         LCD_INFO("%d/%d Konfig Modus", aktuelle_seite, MAX_SEITE);
         break;
      case 3:
         LCD_INFO("%d/%d L3518 Konfig 1", aktuelle_seite, MAX_SEITE);
         break;
      case 4:
         LCD_INFO("%d/%d LSP1518 Konfig 2", aktuelle_seite, MAX_SEITE);
         break;
      case 5:
         LCD_INFO("%d/%d H1713 Konfig 3", aktuelle_seite, MAX_SEITE);
         break;
      case 6:
         LCD_INFO("%d/%d SY57 Konfig 4", aktuelle_seite, MAX_SEITE);
         break;
      case 7:
         LCD_INFO("%d/%d Debug", aktuelle_seite, MAX_SEITE);
         break;
      case 8:
         LCD_INFO("%d/%d Get Konfig", aktuelle_seite, MAX_SEITE);
         break;
      default:
         LCD_INFO("%d/%d", aktuelle_seite, MAX_SEITE);
         break;
   }

   // taskleiste mit version und blabla
   // TM_LCD_SetLayer1(void);
}
/*
 *******************************************************************************
 * Startseite
 *******************************************************************************
 */

void at_lcd_page_0(void) {
   TM_LCD_Fill(LCD_COLOR_WHITE);
#ifdef IMAGE_ON
   GG_PutImage(0, 0, &fhcampuswien);
#endif
   TM_LCD_SetFont(&TM_Font_11x18);
   TM_LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_WHITE);
   TM_LCD_SetXY(4, 180);
   TM_LCD_Puts("Schrittmotorsteuerung");
   TM_LCD_SetXY(53, 210);
   TM_LCD_Puts("Version 2.0");
   TM_LCD_SetXY(53, 260);
   TM_LCD_Puts("c1410535039");
}
/*
 *******************************************************************************
 * 1.Seite
 *******************************************************************************
 */

void at_lcd_page_1(uint16_t modul, uint16_t mode) {
   aktuelle_seite = 1;
   at_lcd_fusszeile();

   TM_LCD_SetXY(0, 0);
   TM_LCD_SetFont(&TM_Font_11x18);

   MODUL_1_STATE(0);
   MODUL_2_STATE(0);
   MODUL_3_STATE(0);
   MODUL_4_STATE(0);
   MODUL_5_STATE(0);
   MODUL_6_STATE(0);
   MODUL_7_STATE(0);
   MODUL_8_STATE(0);

   if (((aktive_ports >> 0) & 0x01) == 1) MODUL_1_STATE(1);
   if (((aktive_ports >> 1) & 0x01) == 1) MODUL_2_STATE(1);
   if (((aktive_ports >> 2) & 0x01) == 1) MODUL_3_STATE(1);
   if (((aktive_ports >> 3) & 0x01) == 1) MODUL_4_STATE(1);
   if (((aktive_ports >> 4) & 0x01) == 1) MODUL_5_STATE(1);
   if (((aktive_ports >> 5) & 0x01) == 1) MODUL_6_STATE(1);
   if (((aktive_ports >> 6) & 0x01) == 1) MODUL_7_STATE(1);
   if (((aktive_ports >> 7) & 0x01) == 1) MODUL_8_STATE(1);

   UP;
   DOWN;

   ON_OFF(1);
}
/*
 *******************************************************************************
 * 2.Seite
 *******************************************************************************
 */

/*
 * pfeile und taskleiste bleiben
 * auslesen der register module ebenfalls mit den seitlichen tastern
 */

void at_lcd_page_2(uint16_t modul, uint16_t mode) {
   aktuelle_seite = 2;

   at_lcd_fusszeile();

   TM_LCD_SetXY(0, 0);
   TM_LCD_SetFont(&TM_Font_11x18);

   MODUL_1_STATE(0);
   MODUL_2_STATE(0);
   MODUL_3_STATE(0);
   MODUL_4_STATE(0);
   MODUL_5_STATE(0);
   MODUL_6_STATE(0);
   MODUL_7_STATE(0);
   MODUL_8_STATE(0);

   if (((aktive_ports >> 0) & 0x01) == 1) MODUL_1_STATE(1);
   if (((aktive_ports >> 1) & 0x01) == 1) MODUL_2_STATE(1);
   if (((aktive_ports >> 2) & 0x01) == 1) MODUL_3_STATE(1);
   if (((aktive_ports >> 3) & 0x01) == 1) MODUL_4_STATE(1);
   if (((aktive_ports >> 4) & 0x01) == 1) MODUL_5_STATE(1);
   if (((aktive_ports >> 5) & 0x01) == 1) MODUL_6_STATE(1);
   if (((aktive_ports >> 6) & 0x01) == 1) MODUL_7_STATE(1);
   if (((aktive_ports >> 7) & 0x01) == 1) MODUL_8_STATE(1);

   KONFIG_1;
   KONFIG_2;
   KONFIG_3;
   KONFIG_4;
}

/*
 *******************************************************************************
 * Touchfunktion
 *******************************************************************************
 */

void at_lcd_state(TM_STMPE811_t* LCD_Config) {
   uint8_t i = 0;
   TM_STMPE811_ReadTouch(LCD_Config);
   TM_STMPE811_ReadTouch(LCD_Config);
   static uint8_t modul[9] = {0};
   static uint8_t on_off = 0;
   static int16_t speed = 0;
   static uint8_t konfig[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

   if (ON_OFF_TOUCH && aktuelle_seite == 1) {
      if (on_off == 1) {
         ON_OFF(0);
         on_off = 0;

         for (i = 1; i <= 8; i++) {
            if (serie[i] > 0) {
               anschluss = i;
               at_schrittmotor_off_soft();
            }
         }
      } else if (aktuelle_seite == 1) {
         ON_OFF(1);
         on_off = 1;

         for (i = 1; i <= 8; i++) {
            if (serie[i] > 0) {
               anschluss = i;
               if (speed < 0) at_schrittmotor_run(0, (-1) * speed);
               if (speed > 0) at_schrittmotor_run(1, speed);
            }
         }
      }
   }

   if (UP_TOUCH && aktuelle_seite == 1 && speed <= 190) {
      TM_LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_WHITE);
      speed += 10;
      TM_LCD_SetXY(107, 130);
      LCD_INFO("     ");
      LCD_INFO(" %d  ", speed);
   }

   if (DOWN_TOUCH && aktuelle_seite == 1 && speed >= -190) {
      TM_LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_WHITE);
      speed -= 10;
      TM_LCD_SetXY(107, 130);
      LCD_INFO("     ");
      LCD_INFO(" %d  ", speed);
   }

   if (MODUL_1_TOUCH && aktuelle_seite == 1 &&
       (((aktive_ports >> 0) & 0x01)) == 1) {
      if (serie[1] == 1) {
         serie[1] = 0;
         MODUL_1_STATE(1);
      }

      else if (serie[1] == 0) {
         serie[1] = 1;
         MODUL_1_STATE(2);
      }
   }

   if (MODUL_2_TOUCH && aktuelle_seite == 1 &&
       (((aktive_ports >> 1) & 0x01)) == 1) {
      if (serie[2] == 1) {
         serie[2] = 0;
         MODUL_2_STATE(1);
      }

      else if (serie[2] == 0) {
         serie[2] = 1;
         MODUL_2_STATE(2);
      }
   }
   if (MODUL_3_TOUCH && aktuelle_seite == 1 &&
       (((aktive_ports >> 2) & 0x01)) == 1) {
      if (serie[3] == 1) {
         serie[3] = 0;
         MODUL_3_STATE(1);
      }

      else if (serie[3] == 0) {
         serie[3] = 1;
         MODUL_3_STATE(2);
      }
   }
   if (MODUL_4_TOUCH && aktuelle_seite == 1 &&
       (((aktive_ports >> 3) & 0x01)) == 1) {
      if (serie[4] == 1) {
         serie[4] = 0;
         MODUL_4_STATE(1);
      }

      else if (serie[4] == 0) {
         serie[4] = 1;
         MODUL_4_STATE(2);
      }
   }
   if (MODUL_5_TOUCH && aktuelle_seite == 1 &&
       (((aktive_ports >> 4) & 0x01)) == 1) {
      if (serie[5] == 1) {
         serie[5] = 0;
         MODUL_5_STATE(1);
      }

      else if (serie[5] == 0) {
         serie[5] = 1;
         MODUL_5_STATE(2);
      }
   }
   if (MODUL_6_TOUCH && aktuelle_seite == 1 &&
       (((aktive_ports >> 5) & 0x01)) == 1) {
      if (serie[6] == 1) {
         serie[6] = 0;
         MODUL_6_STATE(1);
      }

      else if (serie[6] == 0) {
         serie[6] = 1;
         MODUL_6_STATE(2);
      }
   }
   if (MODUL_7_TOUCH && aktuelle_seite == 1 &&
       (((aktive_ports >> 6) & 0x01)) == 1) {
      if (serie[7] == 1) {
         serie[7] = 0;
         MODUL_7_STATE(1);
      }

      else if (serie[7] == 0) {
         serie[7] = 1;
         MODUL_7_STATE(2);
      }
   }
   if (MODUL_8_TOUCH && aktuelle_seite == 1 &&
       (((aktive_ports >> 7) & 0x01)) == 1) {
      if (serie[8] == 1) {
         serie[8] = 0;
         MODUL_8_STATE(1);
      }

      else if (serie[8] == 0) {
         serie[8] = 1;
         MODUL_8_STATE(2);
      }
   }

   if (MODUL_1_TOUCH && aktuelle_seite == 2 &&
       (((aktive_ports >> 0) & 0x01)) == 1) {
      if (konfig[1] == 1) {
         konfig[1] = 0;
         MODUL_1_STATE(1);
      }

      else if (konfig[1] == 0) {
         konfig[1] = 1;
         MODUL_1_STATE(2);
      }
   }

   if (MODUL_2_TOUCH && aktuelle_seite == 2 &&
       (((aktive_ports >> 1) & 0x01)) == 1) {
      if (konfig[2] == 1) {
         konfig[2] = 0;
         MODUL_2_STATE(1);
      }

      else if (konfig[2] == 0) {
         konfig[2] = 1;
         MODUL_2_STATE(2);
      }
   }
   if (MODUL_3_TOUCH && aktuelle_seite == 2 &&
       (((aktive_ports >> 2) & 0x01)) == 1) {
      if (konfig[3] == 1) {
         konfig[3] = 0;
         MODUL_3_STATE(1);
      }

      else if (konfig[3] == 0) {
         konfig[3] = 1;
         MODUL_3_STATE(2);
      }
   }
   if (MODUL_4_TOUCH && aktuelle_seite == 2 &&
       (((aktive_ports >> 3) & 0x01)) == 1) {
      if (konfig[4] == 1) {
         konfig[4] = 0;
         MODUL_4_STATE(1);
      }

      else if (konfig[4] == 0) {
         konfig[4] = 1;
         MODUL_4_STATE(2);
      }
   }
   if (MODUL_5_TOUCH && aktuelle_seite == 2 &&
       (((aktive_ports >> 4) & 0x01)) == 1) {
      if (konfig[5] == 1) {
         konfig[5] = 0;
         MODUL_5_STATE(1);
      }

      else if (konfig[5] == 0) {
         konfig[5] = 1;
         MODUL_5_STATE(2);
      }
   }
   if (MODUL_6_TOUCH && aktuelle_seite == 2 &&
       (((aktive_ports >> 5) & 0x01)) == 1) {
      if (konfig[6] == 1) {
         konfig[6] = 0;
         MODUL_6_STATE(1);
      }

      else if (konfig[6] == 0) {
         konfig[6] = 1;
         MODUL_6_STATE(2);
      }
   }
   if (MODUL_7_TOUCH && aktuelle_seite == 2 &&
       (((aktive_ports >> 6) & 0x01)) == 1) {
      if (konfig[7] == 1) {
         konfig[7] = 0;
         MODUL_7_STATE(1);
      }

      else if (konfig[7] == 0) {
         konfig[7] = 1;
         MODUL_7_STATE(2);
      }
   }
   if (MODUL_8_TOUCH && aktuelle_seite == 2 &&
       (((aktive_ports >> 7) & 0x01)) == 1) {
      if (konfig[8] == 1) {
         konfig[8] = 0;
         MODUL_8_STATE(1);
      }

      else if (konfig[8] == 0) {
         konfig[8] = 1;
         MODUL_8_STATE(2);
      }
   }

   if (KONFIG_1_TOUCH && aktuelle_seite == 2) {
      KONFIG_1_SEL;

      for (int i = 1; i <= 8; i++) {
         if (konfig[i] > 0) {
            at_schrittmotor_param(CONFIG_1, 0, 0);
         }
      }
      HAL_Delay(1000);
      KONFIG_1;
   }

   if (KONFIG_2_TOUCH && aktuelle_seite == 2) {
      KONFIG_2_SEL;

      for (int i = 1; i <= 8; i++) {
         if (konfig[i] > 0) {
            at_schrittmotor_param(CONFIG_2, 0, 0);
         }
      }
      HAL_Delay(1000);
      KONFIG_2;
   }

   if (KONFIG_3_TOUCH && aktuelle_seite == 2) {
      KONFIG_3_SEL;

      for (int i = 1; i <= 8; i++) {
         if (konfig[i] > 0) {
            at_schrittmotor_param(CONFIG_3, 0, 0);
         }
      }
      HAL_Delay(1000);
      KONFIG_3;
   }

   if (KONFIG_4_TOUCH && aktuelle_seite == 2) {
      KONFIG_4_SEL;

      for (int i = 1; i <= 8; i++) {
         if (konfig[i] > 0) {
            at_schrittmotor_param(CONFIG_4, 0, 0);
         }
      }
      HAL_Delay(1000);
      KONFIG_4;
   }

   // Tastendruckverzögerung
   ENTPRELL_DELAY;
}
/*
 *******************************************************************************
 * LCD Testfuntion. Man kann damit die Touchfunktion anh. Koordinaten testen
 *******************************************************************************
 */
void at_lcd_test(TM_STMPE811_t* LCD_Config) {
   char str[30];
   /*
    * FIFO Problem, deshalb zweimal aufgefrufen
    * für mehr infos siehe en.CD00203648.pdf
    * single point reading
    * dazu muss man die tm bibliothek ändern...
    */
   TM_STMPE811_ReadTouch(LCD_Config);
   TM_STMPE811_ReadTouch(LCD_Config);
   /*
    * live tracking --> funktion nicht in callback sondern in
    * while(1) packen
    * und das hier wieder auskommentieren:
    */

   // if (TM_STMPE811_ReadTouch(LCD_Config) ==
   // TM_STMPE811_State_Pressed) {
   if (1) {
      if (TM_STMPE811_TouchInRectangle(LCD_Config, 10, 260, 80, 40)) {
         sprintf(str, "Button Pressed\n\nX: %03d\nY: %03d", LCD_Config->x,
                 LCD_Config->y);
         TM_LCD_SetXY(40, 60);
         TM_LCD_Puts(str);
         at_schrittmotor_test();
      } else if (TM_STMPE811_TouchInRectangle(LCD_Config, 150, 260, 80, 40)) {
         sprintf(str, "Button Pressed\n\nX: %03d\nY: %03d", LCD_Config->x,
                 LCD_Config->y);
         TM_LCD_SetXY(40, 60);
         TM_LCD_Puts(str);
         at_schrittmotor_stop();
      } else {
         sprintf(str, "Pressed       \n\nX: %03d\nY: %03d", LCD_Config->x,
                 LCD_Config->y);
         TM_LCD_SetXY(40, 60);

         if (TM_LCD_Puts(str) != TM_LCD_Result_Ok) {
            /* Return error */
            ;
         }
      }
   } else {
      TM_LCD_SetXY(40, 60);
      TM_LCD_Puts("Not Pressed   ");
   }
}
/*
 *******************************************************************************
 * Mittels des blauen Tasters wird durch verschiedene Seiten geschalten
 *******************************************************************************
 */

/*
 * Diese Funktion ist quick and dirty gemacht um ein paar funktionen zu testen
 * irgendwann ist sie geschichte...
 */

void at_lcd_seite(TM_STMPE811_t* LCD_Config) {
   static uint8_t i = 0;
   i++;
   if (i >= MAX_SEITE + 1) i = 0;

   // TM_LCD_SetXY(0, 0);
   // TM_LCD_SetFont(&TM_Font_7x10);
   // TM_LCD_Fill(LCD_COLOR_WHITE);

   switch (i) {
      /*Run Modus*/
      case 1: {
         aktuelle_seite = 1;
         at_lcd_page_1(1, 1);
      } break;
      /* UART debugfunktion*/
      case 2: {
         aktuelle_seite = 2;
         at_lcd_page_2(1, 1);
      } break;
      /* Standardparemeterausgabe großer Motor */
      case 3: {
         aktuelle_seite = 3;
         at_lcd_fusszeile();
         TM_LCD_SetXY(0, 0);
         TM_LCD_SetFont(&TM_Font_7x10);
         at_schrittmotor_print_data(CONFIG_1);
      } break;
      /* Standardparemeterausgabe großer Motor */
      case 4: {
         aktuelle_seite = 4;
         at_lcd_fusszeile();
         TM_LCD_SetXY(0, 0);
         TM_LCD_SetFont(&TM_Font_7x10);
         at_schrittmotor_print_data(CONFIG_2);

      } break;
      /* Standardparemeterausgabe großer Motor */
      case 5: {
         aktuelle_seite = 5;
         at_lcd_fusszeile();
         TM_LCD_SetXY(0, 0);
         TM_LCD_SetFont(&TM_Font_7x10);
         at_schrittmotor_print_data(CONFIG_3);
      } break;
      /* Standardparemeterausgabe großer Motor */
      case 6: {
         aktuelle_seite = 6;
         at_lcd_fusszeile();
         TM_LCD_SetXY(0, 0);
         TM_LCD_SetFont(&TM_Font_7x10);
         at_schrittmotor_print_data(CONFIG_4);

      } break;
      /* Parameterausgabe aktueller Anschluss */
      case 7: {
         aktuelle_seite = 7;

         at_lcd_fusszeile();
      } break;

      case 8: {
         aktuelle_seite = 8;
         at_lcd_fusszeile();
         TM_LCD_SetXY(0, 0);
         TM_LCD_SetFont(&TM_Font_7x10);

         /* Statusabfrage aktueller Anschluss */
         at_schrittmotor_print_data(1);
         LCD_INFO("Status:    " BYTE_TO_BINARY_PATTERN,
                  BYTE_TO_BINARY(dSPIN_Get_Status()));
      } break;
      default:
         break;
   }
}

/*
 *******************************************************************************
 * Error Ausgabe
 *******************************************************************************
 */
void at_lcd_error(void) {
   TM_LCD_Fill(LCD_COLOR_WHITE);
   TM_LCD_SetColors(LCD_COLOR_RED, GRAPHIC_COLOR_WHITE);
   TM_LCD_SetFont(&TM_Font_16x26);
   TM_LCD_SetXY(50, 140);
   LCD_INFO("ERROR");
   while (1)
      ;
}

/*
 *******************************************************************************
 * Laufende Debugausgabe auf LCD Display
 *******************************************************************************
 */
void at_lcd_debug(uint8_t* UART_Aux) {
   static uint8_t aktuelle_Zeile = 1;
   int i;

   /* char array MAX_ZEILE + 1 für \0 */
   static char debug_buffer[MAX_ZEILE + 1][MAX_SPALTE + 1];

   if (aktuelle_seite == 2) {
      /* Initialisiere LCD */
      at_lcd_fusszeile();
      TM_LCD_SetFont(&TM_Font_7x10);
      TM_LCD_SetXY(0, 0);
   }
   /*
    * Wandelt das String Array in ein zweidimensionales Array um
    * Hat den Vorteil, dass man nun die Befehle aktuelle_Zeilenweise
    * verschieben kann.
    * Die diversen -1 sind da, weil ich die erste Zeile als 1 definiert
    * habe aber das 0te Array abgerufen wird
    */

   memcpy(&debug_buffer[aktuelle_Zeile - 1], UART_Aux, MAX_SPALTE);

   /*
    * Wenn die letzte Zeile erreicht ist, wird nur noch diese mit
    * neuen
    * Daten befüllt. Alle anderen werden nach oben geschoben
    * !! Ausgabe nur wenn Aktuell Seite == 1 ist !!
    */
   if (aktuelle_Zeile < MAX_ZEILE) {
      for (i = 1; i <= aktuelle_Zeile; i++) {
         if (aktuelle_seite == 7) {
            TM_LCD_Puts(debug_buffer[i - 1]);
         }
      }
      aktuelle_Zeile++;
      /* hier muss noch die sache ausgegeben werden */
   } else {
      for (i = 1; i < MAX_ZEILE; i++) {
         memcpy(&debug_buffer[i - 1], &debug_buffer[i], MAX_SPALTE);
         if (aktuelle_seite == 7) {
            TM_LCD_Puts(debug_buffer[i - 1]);
         }
      }
   }
}
