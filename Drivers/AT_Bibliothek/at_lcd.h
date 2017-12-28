/*
 *******************************************************************************
 * File:    at_defines.h
 * Author:  Armin Tirala
 * Version: V4.1
 * Date:    28.12:2017
 * IDE:     Eclipse Neon.3
 * Note:
 * LCD Treiberbibliothek
 * Enthält Funktionen zur grafischen Ausgabe
 ******************************************************************************
 */

#ifndef AT_LCD_H
#define AT_LCD_H

#include "at_defines.h"
#include "tm_stm32f4_stmpe811.h"

#define MODUL_1_STATE(x)                                                 \
   {                                                                     \
      switch (x) {                                                       \
         case 0:                                                         \
            TM_LCD_DrawFilledRectangle(20, 10, 60, 30, LCD_COLOR_BLACK); \
            break;                                                       \
         case 1:                                                         \
            TM_LCD_DrawFilledRectangle(20, 10, 60, 30, LCD_COLOR_GRAY);  \
            break;                                                       \
         case 2:                                                         \
            TM_LCD_DrawFilledRectangle(20, 10, 60, 30, LCD_COLOR_GREEN); \
            break;                                                       \
      }                                                                  \
   }

#define MODUL_2_STATE(x)                                                 \
   {                                                                     \
      switch (x) {                                                       \
         case 0:                                                         \
            TM_LCD_DrawFilledRectangle(10, 60, 30, 60, LCD_COLOR_BLACK); \
            break;                                                       \
         case 1:                                                         \
            TM_LCD_DrawFilledRectangle(10, 60, 30, 60, LCD_COLOR_GRAY);  \
            break;                                                       \
         case 2:                                                         \
            TM_LCD_DrawFilledRectangle(10, 60, 30, 60, LCD_COLOR_GREEN); \
            break;                                                       \
      }                                                                  \
   }

#define MODUL_3_STATE(x)                                                  \
   {                                                                      \
      switch (x) {                                                        \
         case 0:                                                          \
            TM_LCD_DrawFilledRectangle(10, 145, 30, 60, LCD_COLOR_BLACK); \
            break;                                                        \
         case 1:                                                          \
            TM_LCD_DrawFilledRectangle(10, 145, 30, 60, LCD_COLOR_GRAY);  \
            break;                                                        \
         case 2:                                                          \
            TM_LCD_DrawFilledRectangle(10, 145, 30, 60, LCD_COLOR_GREEN); \
            break;                                                        \
      }                                                                   \
   }

#define MODUL_4_STATE(x)                                                  \
   {                                                                      \
      switch (x) {                                                        \
         case 0:                                                          \
            TM_LCD_DrawFilledRectangle(10, 230, 30, 60, LCD_COLOR_BLACK); \
            break;                                                        \
         case 1:                                                          \
            TM_LCD_DrawFilledRectangle(10, 230, 30, 60, LCD_COLOR_GRAY);  \
            break;                                                        \
         case 2:                                                          \
            TM_LCD_DrawFilledRectangle(10, 230, 30, 60, LCD_COLOR_GREEN); \
            break;                                                        \
      }                                                                   \
   }

#define MODUL_5_STATE(x)                                                   \
   {                                                                       \
      switch (x) {                                                         \
         case 0:                                                           \
            TM_LCD_DrawFilledRectangle(200, 230, 30, 60, LCD_COLOR_BLACK); \
            break;                                                         \
         case 1:                                                           \
            TM_LCD_DrawFilledRectangle(200, 230, 30, 60, LCD_COLOR_GRAY);  \
            break;                                                         \
         case 2:                                                           \
            TM_LCD_DrawFilledRectangle(200, 230, 30, 60, LCD_COLOR_GREEN); \
            break;                                                         \
      }                                                                    \
   }

#define MODUL_6_STATE(x)                                                   \
   {                                                                       \
      switch (x) {                                                         \
         case 0:                                                           \
            TM_LCD_DrawFilledRectangle(200, 145, 30, 60, LCD_COLOR_BLACK); \
            break;                                                         \
         case 1:                                                           \
            TM_LCD_DrawFilledRectangle(200, 145, 30, 60, LCD_COLOR_GRAY);  \
            break;                                                         \
         case 2:                                                           \
            TM_LCD_DrawFilledRectangle(200, 145, 30, 60, LCD_COLOR_GREEN); \
            break;                                                         \
      }                                                                    \
   }

#define MODUL_7_STATE(x)                                                  \
   {                                                                      \
      switch (x) {                                                        \
         case 0:                                                          \
            TM_LCD_DrawFilledRectangle(200, 60, 30, 60, LCD_COLOR_BLACK); \
            break;                                                        \
         case 1:                                                          \
            TM_LCD_DrawFilledRectangle(200, 60, 30, 60, LCD_COLOR_GRAY);  \
            break;                                                        \
         case 2:                                                          \
            TM_LCD_DrawFilledRectangle(200, 60, 30, 60, LCD_COLOR_GREEN); \
            break;                                                        \
      }                                                                   \
   }

#define MODUL_8_STATE(x)                                                  \
   {                                                                      \
      switch (x) {                                                        \
         case 0:                                                          \
            TM_LCD_DrawFilledRectangle(160, 10, 60, 30, LCD_COLOR_BLACK); \
            break;                                                        \
         case 1:                                                          \
            TM_LCD_DrawFilledRectangle(160, 10, 60, 30, LCD_COLOR_GRAY);  \
            break;                                                        \
         case 2:                                                          \
            TM_LCD_DrawFilledRectangle(160, 10, 60, 30, LCD_COLOR_GREEN); \
            break;                                                        \
      }                                                                   \
   }

#define UP                                                          \
   {                                                                \
      TM_LCD_DrawFilledRectangle(70, 180, 100, 50, LCD_COLOR_GRAY); \
      TM_LCD_SetColors(LCD_COLOR_BLACK, GRAPHIC_COLOR_GRAY);        \
      TM_LCD_SetXY(107, 195);                                       \
      TM_LCD_Puts("/\\");                                           \
   }

#define DOWN                                                        \
   {                                                                \
      TM_LCD_DrawFilledRectangle(70, 240, 100, 50, LCD_COLOR_GRAY); \
      TM_LCD_SetColors(LCD_COLOR_BLACK, GRAPHIC_COLOR_GRAY);        \
      TM_LCD_SetXY(107, 255);                                       \
      TM_LCD_Puts("\\/");                                           \
   }

#define ON_OFF(x)                                                         \
   {                                                                      \
      switch (x) {                                                        \
         case 0:                                                          \
            TM_LCD_DrawFilledRectangle(70, 80, 100, 50, LCD_COLOR_GRAY);  \
            TM_LCD_SetColors(LCD_COLOR_BLACK, GRAPHIC_COLOR_GRAY);        \
            TM_LCD_SetXY(107, 95);                                        \
            TM_LCD_Puts("OFF");                                           \
            break;                                                        \
         case 1:                                                          \
            TM_LCD_DrawFilledRectangle(70, 80, 100, 50, LCD_COLOR_GREEN); \
            TM_LCD_SetColors(LCD_COLOR_BLACK, GRAPHIC_COLOR_GREEN);       \
            TM_LCD_SetXY(107, 95);                                        \
            TM_LCD_Puts("ON");                                            \
            break;                                                        \
      }                                                                   \
   }

#define KONFIG_1                                                   \
   {                                                               \
      TM_LCD_DrawFilledRectangle(70, 60, 100, 50, LCD_COLOR_GRAY); \
      TM_LCD_SetColors(LCD_COLOR_BLACK, GRAPHIC_COLOR_GRAY);       \
      TM_LCD_SetXY(80, 75);                                        \
      TM_LCD_Puts("Konfig 1");                                     \
   }

#define KONFIG_2                                                    \
   {                                                                \
      TM_LCD_DrawFilledRectangle(70, 120, 100, 50, LCD_COLOR_GRAY); \
      TM_LCD_SetColors(LCD_COLOR_BLACK, GRAPHIC_COLOR_GRAY);        \
      TM_LCD_SetXY(80, 135);                                        \
      TM_LCD_Puts("Konfig 2");                                      \
   }

#define KONFIG_3                                                    \
   {                                                                \
      TM_LCD_DrawFilledRectangle(70, 180, 100, 50, LCD_COLOR_GRAY); \
      TM_LCD_SetColors(LCD_COLOR_BLACK, GRAPHIC_COLOR_GRAY);        \
      TM_LCD_SetXY(80, 195);                                        \
      TM_LCD_Puts("Konfig 3");                                      \
   }

#define KONFIG_4                                                    \
   {                                                                \
      TM_LCD_DrawFilledRectangle(70, 240, 100, 50, LCD_COLOR_GRAY); \
      TM_LCD_SetColors(LCD_COLOR_BLACK, GRAPHIC_COLOR_GRAY);        \
      TM_LCD_SetXY(80, 255);                                        \
      TM_LCD_Puts("Konfig 4");                                      \
   }
#define KONFIG_1_SEL                                                \
   {                                                                \
      TM_LCD_DrawFilledRectangle(70, 60, 100, 50, LCD_COLOR_GREEN); \
      TM_LCD_SetColors(LCD_COLOR_BLACK, GRAPHIC_COLOR_GREEN);       \
      TM_LCD_SetXY(80, 75);                                         \
      TM_LCD_Puts("Konfig 1");                                      \
   }

#define KONFIG_2_SEL                                                 \
   {                                                                 \
      TM_LCD_DrawFilledRectangle(70, 120, 100, 50, LCD_COLOR_GREEN); \
      TM_LCD_SetColors(LCD_COLOR_BLACK, GRAPHIC_COLOR_GREEN);        \
      TM_LCD_SetXY(80, 135);                                         \
      TM_LCD_Puts("Konfig 2");                                       \
   }

#define KONFIG_3_SEL                                                 \
   {                                                                 \
      TM_LCD_DrawFilledRectangle(70, 180, 100, 50, LCD_COLOR_GREEN); \
      TM_LCD_SetColors(LCD_COLOR_BLACK, GRAPHIC_COLOR_GREEN);        \
      TM_LCD_SetXY(80, 195);                                         \
      TM_LCD_Puts("Konfig 3");                                       \
   }

#define KONFIG_4_SEL                                                 \
   {                                                                 \
      TM_LCD_DrawFilledRectangle(70, 240, 100, 50, LCD_COLOR_GREEN); \
      TM_LCD_SetColors(LCD_COLOR_BLACK, GRAPHIC_COLOR_GREEN);        \
      TM_LCD_SetXY(80, 255);                                         \
      TM_LCD_Puts("Konfig 4");                                       \
   }

#define KONFIG_1_TOUCH TM_STMPE811_TouchInRectangle(LCD_Config, 70, 60, 100, 50)
#define KONFIG_2_TOUCH \
   TM_STMPE811_TouchInRectangle(LCD_Config, 70, 120, 100, 50)
#define KONFIG_3_TOUCH \
   TM_STMPE811_TouchInRectangle(LCD_Config, 70, 180, 100, 50)
#define KONFIG_4_TOUCH \
   TM_STMPE811_TouchInRectangle(LCD_Config, 70, 240, 100, 50)

#define MODUL_1_TOUCH TM_STMPE811_TouchInRectangle(LCD_Config, 20, 10, 60, 30)
#define MODUL_2_TOUCH TM_STMPE811_TouchInRectangle(LCD_Config, 10, 60, 30, 60)
#define MODUL_3_TOUCH TM_STMPE811_TouchInRectangle(LCD_Config, 10, 145, 30, 60)
#define MODUL_4_TOUCH TM_STMPE811_TouchInRectangle(LCD_Config, 10, 230, 30, 60)
#define MODUL_5_TOUCH TM_STMPE811_TouchInRectangle(LCD_Config, 200, 230, 30, 60)
#define MODUL_6_TOUCH TM_STMPE811_TouchInRectangle(LCD_Config, 200, 145, 30, 60)
#define MODUL_7_TOUCH TM_STMPE811_TouchInRectangle(LCD_Config, 200, 60, 30, 60)
#define MODUL_8_TOUCH TM_STMPE811_TouchInRectangle(LCD_Config, 160, 10, 60, 30)

#define UP_TOUCH TM_STMPE811_TouchInRectangle(LCD_Config, 70, 180, 100, 50)
#define DOWN_TOUCH TM_STMPE811_TouchInRectangle(LCD_Config, 70, 240, 100, 50)
#define ON_OFF_TOUCH TM_STMPE811_TouchInRectangle(LCD_Config, 70, 80, 100, 50)

extern void at_lcd_init(TM_STMPE811_t* testmin);
extern void at_lcd_state(TM_STMPE811_t* testmin);
extern void at_lcd_seite(TM_STMPE811_t* testmin);

extern void at_lcd_page_0(void);
extern void at_lcd_page_1(uint16_t modul, uint16_t mode);
extern void at_lcd_page_2(uint16_t modul, uint16_t mode);

extern void at_lcd_error(void);
extern void at_lcd_test(TM_STMPE811_t* testmin);

extern uint8_t aktuelle_seite;
extern uint8_t aktuelle_taste;
extern uint8_t aktive_ports;
extern uint8_t serie[9];

#endif
