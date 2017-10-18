/**
 ******************************************************************************
 * @file    at_lcd.h
 * @author  Armin Tirala
 *	@email   a.tirala@gmail.com
 * @version V1.0
 * @date    16.05.2017
 * @ide     Keil uVision V5.23.0.0
 * @brief   LCD Treiberbibliothek
 * @note    Enth�lt Funktionen zur grafischen Ausgabe
 * Enth�lt keine Konfigurationsparameter --> nicht �ndern
 ******************************************************************************
 */

#ifndef _USE_LCD_H
#define _USE_LCD_H

#include "defines.h"
#include "tm_stm32f4_stmpe811.h"

/**
 * @brief  Initialisiert das LCD Display und die Touchfunktion
 * @note	 Gibt Fehler aus, wenn nicht korrekt ausgefuehrt
 * @param  Uebergibt die Struktur testmin als Zeiger
 * @retval LCD_OK
 * @retval LCD_NOK
 */
extern void at_lcd_init(TM_STMPE811_t* testmin);

/**
 * @brief  Grafische Ausgabe der Menuetasten
 * @note   none
 * @param  none
 * @retval none
 */
extern void at_lcd_button(uint8_t richtung);

/**
 * @brief  Grafische Ausgabe der ersten Seite
 * @note   Enth�lt Versionsinfos
 * @param  none
 * @retval none
 */
extern void at_lcd_page_0(void);

/**
 * @brief  Grafische des Hauptmenues
 * @note   zeigt Status der Modulschnittstellen an
 * @param  none
 * @retval none
 */
extern void at_lcd_page_1(uint16_t modul, uint16_t mode);

/**
 * @brief  Testfunktion f�r das LCD Display
 * @param  Uebergibt die Struktur testmin als Zeiger.
 * @note	 Gibt Koordinaten und Infos der Touchfunktion zurueck
 * @retval uint16_t x;
 * @retval uint16_t y;
 * @retval TM_STMPE811_State_t pressed;
 * @retval TM_STMPE811_State_t last_pressed;
 * @retval TM_STMPE811_Orientation_t orientation;
 */
extern void at_lcd_test(TM_STMPE811_t* testmin);

extern uint8_t aktuelle_seite;
extern uint8_t aktuelle_taste;

extern void at_lcd_start(void);
extern void at_lcd_page_2(uint16_t modul, uint16_t mode);
extern void at_lcd_state(TM_STMPE811_t* testmin);
extern void at_debug(TM_STMPE811_t* testmin);
extern void at_lcd_error(void);

#endif
