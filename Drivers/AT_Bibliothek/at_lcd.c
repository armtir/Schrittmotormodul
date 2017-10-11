#include "at_lcd.h"
#include "defines.h"
#include "stm32f4xx_hal.h"
#include "tm_stm32_lcd.h"
#include "tm_stm32_fonts.h"
#include "tm_stm32f4_stmpe811.h"
#include "at_schrittmotor.h"
#include "stdint.h"

/*
 * Allgemeine Infos 240 breit 320 hoch
 *
 */



void at_lcd_init(TM_STMPE811_t* testmin) {

/* Initialisiere Touch und Display*/
  TM_LCD_Init();

/* ausrichtung der touch einheit Select touch screen orientation */
  testmin->orientation = TM_STMPE811_Orientation_Portrait_2;

/* Initialisiere und pr�fe ob Touch OK */
  if (TM_STMPE811_Init() != TM_STMPE811_State_Ok) {
    TM_LCD_SetXY  (40, 40);
    TM_LCD_SetFont  (&TM_Font_16x26);
    TM_LCD_Puts   ("TOUCH ERROR");
    while (1)
      ;
  }
}

void at_lcd_button(uint8_t richtung) {
  TM_LCD_SetXY  (0, 0);
  TM_LCD_SetFont  (&TM_Font_16x26);

  if (richtung == 1 || richtung == 3) {
    TM_LCD_DrawFilledRectangle  (10, 260, 80, 40, LCD_COLOR_GRAY);
    TM_LCD_SetColors      (LCD_COLOR_BLACK, GRAPHIC_COLOR_GRAY);
    TM_LCD_SetXY        (20, 266);
    TM_LCD_Puts         ("<");
  }

  if (richtung == 2 || richtung == 3) {
    TM_LCD_DrawFilledRectangle  (150, 260, 80, 40, LCD_COLOR_GRAY);
    TM_LCD_SetColors      (LCD_COLOR_BLACK,  GRAPHIC_COLOR_GRAY);
    TM_LCD_SetXY        (200, 266);
    TM_LCD_Puts         (">");
  }

  TM_LCD_SetFont  (&TM_Font_11x18);
  TM_LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_WHITE);
}

void at_lcd_start(void) {
  TM_LCD_SetXY  (0, 0);
  //drawBitmap(111, 0, fh_logo_big, 128,64,GRAPHIC_COLOR_BLACK,GRAPHIC_COLOR_WHITE);
  TM_LCD_SetXY  (4, 100);
  TM_LCD_Puts   ("Schrittmotorsteuerung");
  TM_LCD_SetXY  (53, 130);
  TM_LCD_Puts   ("Version 2.0");
  TM_LCD_SetXY  (53, 180);
  TM_LCD_Puts   ("c1410535039");
  //HAL_Delay(6000);
  TM_LCD_Init();
}

void at_lcd_page_0(void) {
  aktuelle_seite = 0;
  TM_LCD_Fill   (LCD_COLOR_WHITE);
  TM_LCD_SetXY  (0, 0);
  //drawBitmap(111, 0, fh_logo_big, 128,64,GRAPHIC_COLOR_BLACK,GRAPHIC_COLOR_WHITE);
  TM_LCD_SetXY  (4, 100);
  TM_LCD_Puts   ("Schrittmotorsteuerung");
  TM_LCD_SetXY  (53, 130);
  TM_LCD_Puts   ("Version 1.0");
  TM_LCD_SetXY  (53, 180);
  TM_LCD_Puts   ("c1410535039");
  at_lcd_button (2);
}

void at_lcd_page_1(uint16_t modul, uint16_t mode) {
  aktuelle_seite  = 1;
  TM_LCD_Fill   (LCD_COLOR_WHITE);
  at_lcd_button (3);

  for (int i = 0; i < 4; i++) {
    TM_LCD_SetXY(0, 0);
    TM_LCD_DrawFilledRectangle(10,  (20 + (50 * i)), 15, 30,
    LCD_COLOR_BLACK);
    TM_LCD_DrawFilledRectangle(215, (20 + (50 * i)), 15, 30,
    LCD_COLOR_BLACK);
  }

  TM_LCD_DrawFilledRectangle(10,  20,  15, 30, LCD_COLOR_GRAY);
  TM_LCD_DrawFilledRectangle(70,  30, 100, 50, LCD_COLOR_GRAY);
  TM_LCD_DrawFilledRectangle(70, 100, 100, 50, LCD_COLOR_GRAY);
  TM_LCD_DrawFilledRectangle(70, 170, 100, 50, LCD_COLOR_RED );

  TM_LCD_SetColors(LCD_COLOR_BLACK, GRAPHIC_COLOR_GRAY);
  TM_LCD_SetXY  (102, 45);
  TM_LCD_Puts   ("RUN");
  TM_LCD_SetXY  (97, 115);
  TM_LCD_Puts   ("SYNC");
  TM_LCD_SetColors(LCD_COLOR_BLACK, GRAPHIC_COLOR_RED);
  TM_LCD_SetXY  (97, 185);
  TM_LCD_Puts   ("STOP");

  TM_LCD_SetFont  (&TM_Font_11x18);
  TM_LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_WHITE);

}

void at_lcd_page_2(uint16_t modul, uint16_t mode) {
  aktuelle_seite   = 2;
  TM_LCD_Fill   (LCD_COLOR_WHITE);
  at_lcd_button (1);

  for (int i = 0; i < 4; i++) {
    TM_LCD_SetXY(0, 0);
    TM_LCD_DrawFilledRectangle(10,  (20 + (50 * i)), 15, 30,
    LCD_COLOR_BLACK);
    TM_LCD_DrawFilledRectangle(215, (20 + (50 * i)), 15, 30,
    LCD_COLOR_BLACK);
  }
  TM_LCD_DrawFilledRectangle(10, 170,  15, 30, LCD_COLOR_GRAY);
  TM_LCD_DrawFilledRectangle(70,  30, 100, 50, LCD_COLOR_GRAY);
  TM_LCD_DrawFilledRectangle(70, 100, 100, 50, LCD_COLOR_GRAY);
  TM_LCD_DrawFilledRectangle(70, 170, 100, 50, LCD_COLOR_GRAY);

  TM_LCD_SetColors(LCD_COLOR_BLACK, GRAPHIC_COLOR_GRAY);
  TM_LCD_SetXY  (102, 45);
  TM_LCD_Puts   ("VOLL");
  TM_LCD_SetXY  (97, 115);
  TM_LCD_Puts   ("HALB");
  TM_LCD_SetXY  (97, 185);
  TM_LCD_Puts   ("MIKRO");

  TM_LCD_SetFont  (&TM_Font_11x18);
  TM_LCD_SetColors(LCD_COLOR_BLACK, LCD_COLOR_WHITE);

}

void at_lcd_state(TM_STMPE811_t* testmin) {

  TM_STMPE811_ReadTouch(testmin);
  TM_STMPE811_ReadTouch(testmin);

  if    (TM_STMPE811_TouchInRectangle(testmin,  70,  30, 100, 50))
    aktuelle_taste = 1;
  else if (TM_STMPE811_TouchInRectangle(testmin,  70, 100, 100, 50))
    aktuelle_taste = 2;
  else if (TM_STMPE811_TouchInRectangle(testmin,  70, 170, 100, 50))
    aktuelle_taste = 3;
  else if (TM_STMPE811_TouchInRectangle(testmin,  10, 260,  80, 40))
    aktuelle_taste = 4;
  else if (TM_STMPE811_TouchInRectangle(testmin, 150, 260,  80, 40))
    aktuelle_taste = 5;

  switch (aktuelle_taste) {
  case 1: { //run voll
    if    (aktuelle_seite == 1) at_schrittmotor_run();
    else if (aktuelle_seite == 2) at_schritt_konfig(0);
    break;
  }
  case 2: { //sync halb
    if    (aktuelle_seite == 1) at_schrittmotor_sync();
    else if (aktuelle_seite == 2) at_schritt_konfig(1);
    break;
  }
  case 3: { //stop mikro
    if    (aktuelle_seite == 1) at_schrittmotor_stop();
    else if (aktuelle_seite == 2) at_schritt_konfig(4);
    break;
  }
  case 4: { //links
    if    (aktuelle_seite == 1) at_lcd_page_0();
    else if (aktuelle_seite == 2) at_lcd_page_1(1, 2);
    break;
  }
  case 5: { //rechts
    if    (aktuelle_seite == 0) at_lcd_page_1(1, 2);
    else if (aktuelle_seite == 1) at_lcd_page_2(1, 2);
    break;
  }
  default:
    break;
  }

}

void at_lcd_test(TM_STMPE811_t* testmin) {
  char str[30];
/*
 * FIFO Problem, deshalb zweimal aufgefrufen
 * f�r mehr infos siehe en.CD00203648.pdf
 * single point reading
 * dazu muss man die tm bibliothek �ndern...
 */
  TM_STMPE811_ReadTouch(testmin);
  TM_STMPE811_ReadTouch(testmin);
/*
 * live tracking --> funktion nicht in callback sondern in while(1) packen
 * und das hier wieder auskommentieren:
 */

//if (TM_STMPE811_ReadTouch(testmin) == TM_STMPE811_State_Pressed) {
  if (1) {
    if (TM_STMPE811_TouchInRectangle    (testmin, 10, 260, 80, 40)) {
      sprintf(str, "Button Pressed\n\nX: %03d\nY: %03d", testmin->x, testmin->y);
      TM_LCD_SetXY(40, 60);
      TM_LCD_Puts(str);
      at_schrittmotor_test();
    } else if (TM_STMPE811_TouchInRectangle (testmin, 150, 260, 80, 40)) {
      sprintf(str, "Button Pressed\n\nX: %03d\nY: %03d", testmin->x, testmin->y);
      TM_LCD_SetXY(40, 60);
      TM_LCD_Puts(str);
      at_schrittmotor_stop();
    } else {
      sprintf(str, "Pressed       \n\nX: %03d\nY: %03d", testmin->x, testmin->y);
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

void at_debug(TM_STMPE811_t* testmin) {




  uint8_t test1 = 0;
  int test2 = 0;

/*
 * Initialisiere i als statische Variable
 * --> fixer Speicherplatz nur beim
 * 34 Zeichen bei 7x10 und 33 zeilen
 */
  static uint8_t i = 0;
  i++;
  if (i >= 6)    i = 0;

  TM_LCD_SetXY  (0, 0);
  TM_LCD_SetFont  (&TM_Font_7x10);
  TM_LCD_Fill   (LCD_COLOR_WHITE);
  test1 =  TM_LCD_GetCurrentX;
  test2 =  &TM_LCD_GetCurrentY;
  LCD_INFO("y=%d x=%d",test1, test2);
  switch (i) {
  case 1:{
    at_schrittmotor_print_data(101);
    for(int i=0;i<100; i++){
      LCD_INFO    ("Zeile: %d", i);
    }
  }
    break;
  case 2:{
    at_schrittmotor_print_data(102);}
    break;
  case 3:{
    at_schrittmotor_print_data(1);}
    break;
  case 4:
    //LCD_INFO("Status:    "BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(dSPIN_Get_Status()));
    at_stck(0x10);
    LCD_INFO    ("stck!");


    test1 =  TM_LCD_GetCurrentX;
    test2 = TM_LCD_GetCurrentY;
    LCD_INFO("y=%d x=%d",test1, test2);

    break;
  default:
    break;
  }

}

void at_lcd_error(void) {

  TM_LCD_Fill   (LCD_COLOR_WHITE);
  TM_LCD_SetColors(LCD_COLOR_RED, GRAPHIC_COLOR_WHITE);
  TM_LCD_SetFont  (&TM_Font_16x26);
  TM_LCD_SetXY  (50, 140);
  LCD_INFO    ("USB ERROR");
  LCD_INFO    ("RESET!");

}


void at_lcd_debug(uint8_t *UART_Aux) {

TM_LCD_Fill (LCD_COLOR_WHITE);
TM_LCD_SetXY  (0, 0);
  
static initialisierung = 1;
static char debug_buffer[33][34];
static j=1;

/*
 * Wandelt das String Array in ein zweidimensionales Array um
 * Hat den Vorteil, dass man nun die Befehle zeilenweise verschieben kann
 */

for (int i=0; i<LETZTE_SPALTE; i++) {
  memcpy(&debug_buffer[j][i], &UART_Aux[i], sizeof(UART_Aux[0]));
}
/*
 * Wenn abgeschlossen wird die Zeile um j++ erhoeht.
 * Und die gespeicherten Zeilen durch eine for-Schleife ausgegeben
 */

if(j < LETZTE_ZEILE){
   j++;
}
else{
   for(j=LETZTE_ZEILE; j>0; j--) {
     //  debug_buffer[j-1] = debug_buffer[j];
   }
}

for (int i=0; i<LETZTE_ZEILE; i++) {
  LCD_INFO(debug_buffer[i]);
}



// 17 zeilen bei grosser schrift oder halt 16
HAL_Delay(1000);




}

