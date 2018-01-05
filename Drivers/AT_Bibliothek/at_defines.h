/*
 *******************************************************************************
 * File:    at_defines.h
 * Author:  Armin Tirala
 * Version: V4.1
 * Date:    28.12.2017
 * IDE:     Eclipse Neon.3
 * Note:
 * Konfigurations-Headerfile
 * Alle allgemeinen Controllerspezifischen Konfigurationen sind hier definiert
 * Manche aus CubeMX erstellten Konfig. werden hier ueberschrieben!
 * Der Grund ist, dass CubeMX sehr praktisch ist aber ein paar Einstellungen
 * von Hand vorgenommen werden mussten.
 * In diesem File k�nnen �nderungen vorgenommen werden!
 * Manuelle Parametrierung, �berschreibt die Cube Einstellungen
 * Aenderungen der GPIO Ports f�r Chipselect HIER!
 * Grund: die Bibliotheken TM und DSPIN nehmen diese Makrodefinitionen
 * her. Diese alle zu aendern ist nicht sinnvoll, weiters sind manche
 * Parameter mit einer Funktionbeschrieben --> das w�rde in Cube nicht
 * funktionieren
 *******************************************************************************
 */

#ifndef AT_DEFINES_H
#define AT_DEFINES_H

/*
 *******************************************************************************
 * Defines
 *******************************************************************************
 */

#define ENABLE_LCD_INFO
//#define CLK16_enable

#define AT_ERROR HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET)

//#define LETZTE_ZEILE 28
//#define LETZTE_SPALTE 34
#define LESEN 0
#define SCHREIBEN 1
#define FORWARD 1
#define CONFIG_1 99
#define CONFIG_2 98
#define CONFIG_3 97
#define CONFIG_4 96
#define IMAGE_ON
#define ENTPRELL_DELAY HAL_Delay(100);


#define DEBUG_SEITE 7

#define REVERSE 0
/* Der Buffer muss nur so groß sein, dass sich ein Befehl ausgeht ?34? */
#define MAX_BUFFER 50
/* 32 Zeilen, 34 Spalten bei einer Schrift von 7x10 */
#define MAX_ZEILE 31
#define MAX_SPALTE 34
#define MAX_SEITE 8

/*
 *******************************************************************************
 * Makros
 *******************************************************************************
 */

/* Zu Debugzwecken eingebaut */
#ifdef ENABLE_LCD_INFO
char str[30];
#define LCD_INFO(...)            \
   {                             \
      sprintf(str, __VA_ARGS__); \
      TM_LCD_Puts(str);          \
      TM_LCD_Puts("\n");         \
   }
#endif

#define UART_INFO(...)               \
   {                                 \
      sprintf(str, __VA_ARGS__);     \
      TM_USART_Puts(USART1, str);    \
      TM_USART_Puts(USART1, "\n\r"); \
   }

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)                                     \
   (byte & 0x8000 ? '1' : '0'), (byte & 0x4000 ? '1' : '0'),     \
       (byte & 0x2000 ? '1' : '0'), (byte & 0x1000 ? '1' : '0'), \
       (byte & 0x800 ? '1' : '0'), (byte & 0x400 ? '1' : '0'),   \
       (byte & 0x200 ? '1' : '0'), (byte & 0x100 ? '1' : '0'),   \
       (byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'),     \
       (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'),     \
       (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'),     \
       (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0')

#define BYTE_TO_BINARY_PATTERN8 "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY8(byte)                                \
   (byte & 0x80 ? '1' : '0'), (byte & 0x40 ? '1' : '0'),     \
       (byte & 0x20 ? '1' : '0'), (byte & 0x10 ? '1' : '0'), \
       (byte & 0x08 ? '1' : '0'), (byte & 0x04 ? '1' : '0'), \
       (byte & 0x02 ? '1' : '0'), (byte & 0x01 ? '1' : '0')

/*
 *******************************************************************************
 * Defines fuer die TM Bibliothek
 *
 * Wie oben angesprochen werden zB die SPI Paramterierungen
 * durch ein weiteres Makro definiert
 *******************************************************************************
 */
#define STM32F4xx
#define STM32F429_DISCOVERY

#define LCD_USE_STM32F429_DISCOVERY
#define SDRAM_USE_STM32F429_DISCOVERY

/* SPI Schnittstelle */
#define TM_SPI5_PRESCALER SPI_BAUDRATEPRESCALER_8
#define TM_SPI5_DATASIZE SPI_DATASIZE_8BIT
#define TM_SPI5_FIRSTBIT SPI_FIRSTBIT_MSB
#define TM_SPI5_MASTERSLAVE SPI_MODE_MASTER
#define TM_SPI5_MODE TM_SPI_Mode_0

#define TM_SPI3_PRESCALER SPI_BAUDRATEPRESCALER_8
#define TM_SPI3_DATASIZE SPI_DATASIZE_8BIT
#define TM_SPI3_FIRSTBIT SPI_FIRSTBIT_MSB
#define TM_SPI3_MASTERSLAVE SPI_MODE_MASTER
#define TM_SPI3_MODE TM_SPI_Mode_0

/* UART Einstellungen */
#define TM_USART1_HARDWARE_FLOW_CONTROL TM_USART_HardwareFlowControl_None
#define TM_USART1_MODE USART_MODE_TX_RX
#define TM_USART1_PARITY USART_PARITY_NONE
#define TM_USART1_STOP_BITS USART_STOPBITS_1
#define TM_USART1_WORD_LENGTH UART_WORDLENGTH_8B

/*
 *******************************************************************************
 * Pinout der benutzten GPIOS und eigene Makros
 * siehe CubeMX
 *******************************************************************************
 */

/*
 * Pinning  06092017
 * Linke Stiftleiste
 * Pin   Port     Bezeichnung Funktion
 * 11    PE6      nCS_1    OUT
 * 12    PC13     nCS_2    OUT
 * 13    PE4      nUSB_Mode INT
 * 14    PE5      nCS_0    OUT
 * 15    PE2      INT_A    INT
 * 16    PE3      INT_B    INT
 * 28    PB3      CLK      OUT
 * 40    PD2      nCS_3    OUT
 * 43    PC12     MOSI     OUT
 * 44    PC11     MISO     IN
 * 51    PA10     TXD      IN
 * 52    PA9      RXD      OUT
 * 55    PC8      nCS_4    OUT

 * Rechte Stiftleiste
 * Pin   Port  Bezeichnung Funktion
 * 12    NRST
 * 15    PC3      nCS_8    OUT
 * 21    PA5      nCS_7    OUT
 * 61    PG3      nCS_6    OUT
 * 62    PG2      nCS_5    OUT
 */

/*
 * Wenn definiert, dann werden die Expander im 16Bit
 * Modus betrieben sonst im 8Bit
 * Da die Treiber nur f�r 8Bit funktionieren, ist diese Funktion
 * nutzlos
 */
//#define Expander_16Bit_Mode

/* Wenn aktiviert, dann Debugmodus aktiv
 * Ansonsten auskommentieren
 */
#define Debuging

#define EXPANDER_SPI SPI3
#define TREIBER_SPI SPI3
#define EXPANDER_SPI_PINS TM_SPI_PinsPack_2

#define Expander_CS_AKTIV HAL_GPIO_WritePin(GPIOE, GPIO_Pin_5, GPIO_PIN_RESET)
#define Expander_CS_INAKTIV HAL_GPIO_WritePin(GPIOE, GPIO_Pin_5, GPIO_PIN_SET)

#define Anschluss_1_CS_AKTIV \
   HAL_GPIO_WritePin(GPIOE, GPIO_Pin_6, GPIO_PIN_RESET)
#define Anschluss_1_CS_INAKTIV \
   HAL_GPIO_WritePin(GPIOE, GPIO_Pin_6, GPIO_PIN_SET)

#define Anschluss_2_CS_AKTIV \
   HAL_GPIO_WritePin(GPIOC, GPIO_Pin_13, GPIO_PIN_RESET)
#define Anschluss_2_CS_INAKTIV \
   HAL_GPIO_WritePin(GPIOC, GPIO_Pin_13, GPIO_PIN_SET)

#define Anschluss_3_CS_AKTIV \
   HAL_GPIO_WritePin(GPIOD, GPIO_Pin_2, GPIO_PIN_RESET)
#define Anschluss_3_CS_INAKTIV \
   HAL_GPIO_WritePin(GPIOD, GPIO_Pin_2, GPIO_PIN_SET)

#define Anschluss_4_CS_AKTIV \
   HAL_GPIO_WritePin(GPIOC, GPIO_Pin_8, GPIO_PIN_RESET)
#define Anschluss_4_CS_INAKTIV \
   HAL_GPIO_WritePin(GPIOC, GPIO_Pin_8, GPIO_PIN_SET)

#define Anschluss_5_CS_AKTIV \
   HAL_GPIO_WritePin(GPIOG, GPIO_Pin_2, GPIO_PIN_RESET)
#define Anschluss_5_CS_INAKTIV \
   HAL_GPIO_WritePin(GPIOG, GPIO_Pin_2, GPIO_PIN_SET)

#define Anschluss_6_CS_AKTIV \
   HAL_GPIO_WritePin(GPIOG, GPIO_Pin_3, GPIO_PIN_RESET)
#define Anschluss_6_CS_INAKTIV \
   HAL_GPIO_WritePin(GPIOG, GPIO_Pin_3, GPIO_PIN_SET)

#define Anschluss_7_CS_AKTIV \
   HAL_GPIO_WritePin(GPIOA, GPIO_Pin_5, GPIO_PIN_RESET)
#define Anschluss_7_CS_INAKTIV \
   HAL_GPIO_WritePin(GPIOA, GPIO_Pin_5, GPIO_PIN_SET)

#define Anschluss_8_CS_AKTIV \
   HAL_GPIO_WritePin(GPIOC, GPIO_Pin_3, GPIO_PIN_RESET)
#define Anschluss_8_CS_INAKTIV \
   HAL_GPIO_WritePin(GPIOC, GPIO_Pin_3, GPIO_PIN_SET)

// UART

/* Buffer's length must be select according to real messages frequency */
#define RXBUF_LEN 128  // must be power of 2
#define TXBUF_LEN 128  // must be power of 2
#define RXBUF_MSK (RXBUF_LEN - 1)
#define TXBUF_MSK (TXBUF_LEN - 1)

/*******************************************************************************
 * Parameter fuer DSPIN Bibliothek
 *******************************************************************************
 */
#define DMA2_STREAM3_DISABLE_IRQHANDLER
#define DMAx_STREAMy_DISABLE_IRQHANDLER

#endif
