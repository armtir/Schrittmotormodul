/**
 ******************************************************************************
 * @file    defines.h 
 * @author  Armin Tirala
 * @email   a.tirala@gmail.com
 * @version V4.0
 * @date    06.09.2017
 * @ide     Keil uVision V5.23.0.0
 * @brief   Konfigurations-Headerfile
 * @note    
 * Alle allgemeinen Controllerspezifischen Konfigurationen sind hier definiert
 * Manche aus CubeMX erstellten Konfig. werden hier ueberschrieben!
 * Der Grund ist, dass CubeMX sehr praktisch ist aber ein paar Einstellungen von
 * Hand vorgenommen werden mussten.
 * In diesem File k�nnen �nderungen vorgenommen werden!
 * Manuelle Parametrierung, �berschreibt die Cube Einstellungen
 * �nderungen der GPIO Ports f�r Chipselect HIER!
 * Grund: die Bibliotheken TM und DSPIN nehmen diese Makrodefinitionen
 * her. Diese alle zu aendern ist nicht sinnvoll, weiters sind manche 
 * Parameter mit einer Funktionbeschrieben --> das w�rde in Cube nicht
 * funktionieren
 *
 ******************************************************************************
 */

/*die n�chsten schritte:
 einzelne module(files und treiber) abschlie�en
 dann aufbauend auf diesen weitere funktionen einbauen
 zuerst soll aber die basis funktionieren!!!
 
 1. test seite in lcd einbauen und funktionen zum debuggen einbauen
 2. test der einzelnen signale: interrupt, gpio
 3. test der treiber
 4. modifikationen der treiber
 */

/*
 also das ganze ist etwas kompliziert. Der Expander Treiber ist soweit
 einsetzbar, Der Schrittmotor-Treiber noch nicht.



 */

#ifndef DEFINES_FILE
#define DEFINES_FILE

/*
 * Übersicht:
 * 1.TM Makros
 * 2.STM32 Konfiguration
 * 3.DSPIN Konfiguration verbesserungsw�rdig
 *
 * TABS beim Editor bitte auf 4 setzen!!!!!
 */
#define ENABLE_LCD_INFO
//#define CLK16_enable

#define AT_ERROR  HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET)
#define LETZTE_ZEILE  33
#define LETZTE_SPALTE 34
#define LESEN 0
#define SCHREIBEN 1
#define FORWARD 1
#define REVERSE 0 

#ifdef ENABLE_LCD_INFO
char str[30];
#define LCD_INFO(...)        \
	{                        \
	sprintf(str,__VA_ARGS__);\
	TM_LCD_Puts(str);        \
	TM_LCD_Puts("\n");       \
	}
#endif

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)   \
  (byte & 0x8000 ? '1' : '0'), \
  (byte & 0x4000 ? '1' : '0'), \
  (byte & 0x2000 ? '1' : '0'), \
  (byte & 0x1000 ? '1' : '0'), \
  (byte &  0x800 ? '1' : '0'), \
  (byte &  0x400 ? '1' : '0'), \
  (byte &  0x200 ? '1' : '0'), \
  (byte &  0x100 ? '1' : '0'), \
  (byte &   0x80 ? '1' : '0'), \
  (byte &   0x40 ? '1' : '0'), \
  (byte &   0x20 ? '1' : '0'), \
  (byte &   0x10 ? '1' : '0'), \
  (byte &   0x08 ? '1' : '0'), \
  (byte &   0x04 ? '1' : '0'), \
  (byte &   0x02 ? '1' : '0'), \
  (byte &   0x01 ? '1' : '0')



/****************************************************************************
 * Makros f�r die TM Bibliothek
 *
 * Wie oben angesprochen werden zB die SPI Paramterierungen
 * durch ein weiteres Makro definiert
 ******************************************************************************
 */
#define STM32F4xx
#define STM32F429_DISCOVERY

#define LCD_USE_STM32F429_DISCOVERY
#define SDRAM_USE_STM32F429_DISCOVERY

/* SPI Schnittstelle */
#define TM_SPI5_PRESCALER				SPI_BAUDRATEPRESCALER_8
#define TM_SPI5_DATASIZE				SPI_DATASIZE_8BIT
#define TM_SPI5_FIRSTBIT				SPI_FIRSTBIT_MSB
#define TM_SPI5_MASTERSLAVE				SPI_MODE_MASTER
#define TM_SPI5_MODE					TM_SPI_Mode_0

#define TM_SPI3_PRESCALER				SPI_BAUDRATEPRESCALER_8
#define TM_SPI3_DATASIZE				SPI_DATASIZE_8BIT
#define TM_SPI3_FIRSTBIT				SPI_FIRSTBIT_MSB
#define TM_SPI3_MASTERSLAVE				SPI_MODE_MASTER
#define TM_SPI3_MODE					TM_SPI_Mode_0

/* UART Einstellungen */
#define TM_USART1_HARDWARE_FLOW_CONTROL	TM_USART_HardwareFlowControl_None
#define TM_USART1_MODE					USART_MODE_TX_RX
#define TM_USART1_PARITY				USART_PARITY_NONE
#define TM_USART1_STOP_BITS				USART_STOPBITS_1
#define TM_USART1_WORD_LENGTH			UART_WORDLENGTH_8B

/******************************************************************************
 * Pinout der benutzten GPIOS und eigene Makros
 *
 * siehe CubeMX
 ******************************************************************************
 */

/* 
 * Pinning  06092017
 * Linke Stiftleiste
 * Pin		Port	Bezeichnung	Funktion
 * 11		PE6		nCS_1		OUT
 * 12		PC13	nCS_2		OUT
 * 13		PE4		nUSB_Mode	INT
 * 14		PE5		nCS_0		OUT
 * 15		PE2		INT_A		INT
 * 16		PE3		INT_B		INT
 * 28		PB3		CLK			OUT
 * 40		PD2		nCS_3		OUT
 * 43		PC12	MOSI		OUT
 * 44		PC11	MISO		IN
 * 51		PA10	TXD			IN
 * 52		PA9		RXD			OUT
 * 55		PC8		nCS_4		OUT

 * Rechte Stiftleiste
 * Pin		Port	Bezeichnung	Funktion
 * 12		NRST
 * 15		PC3		nCS_8		OUT
 * 21		PA5		nCS_7		OUT
 * 61		PG3		nCS_6		OUT
 * 62		PG2		nCS_5		OUT
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

#define EXPANDER_SPI 				SPI3
#define TREIBER_SPI 				SPI3
#define EXPANDER_SPI_PINS			TM_SPI_PinsPack_2

#define Expander_CS_AKTIV			HAL_GPIO_WritePin(GPIOE,GPIO_Pin_5, GPIO_PIN_RESET)
#define Expander_CS_INAKTIV			HAL_GPIO_WritePin(GPIOE,GPIO_Pin_5, GPIO_PIN_SET)

#define Anschluss_1_CS_AKTIV		HAL_GPIO_WritePin(GPIOE,GPIO_Pin_6, GPIO_PIN_RESET)
#define Anschluss_1_CS_INAKTIV		HAL_GPIO_WritePin(GPIOE,GPIO_Pin_6, GPIO_PIN_SET)

#define Anschluss_2_CS_AKTIV		HAL_GPIO_WritePin(GPIOC,GPIO_Pin_13,GPIO_PIN_RESET)
#define Anschluss_2_CS_INAKTIV		HAL_GPIO_WritePin(GPIOC,GPIO_Pin_13,GPIO_PIN_SET)

#define Anschluss_3_CS_AKTIV		HAL_GPIO_WritePin(GPIOD,GPIO_Pin_2, GPIO_PIN_RESET)
#define Anschluss_3_CS_INAKTIV		HAL_GPIO_WritePin(GPIOD,GPIO_Pin_2, GPIO_PIN_SET)

#define Anschluss_4_CS_AKTIV		HAL_GPIO_WritePin(GPIOC,GPIO_Pin_8, GPIO_PIN_RESET)
#define Anschluss_4_CS_INAKTIV		HAL_GPIO_WritePin(GPIOC,GPIO_Pin_8, GPIO_PIN_SET)

#define Anschluss_5_CS_AKTIV		HAL_GPIO_WritePin(GPIOG,GPIO_Pin_2, GPIO_PIN_RESET)
#define Anschluss_5_CS_INAKTIV		HAL_GPIO_WritePin(GPIOG,GPIO_Pin_2, GPIO_PIN_SET)

#define Anschluss_6_CS_AKTIV		HAL_GPIO_WritePin(GPIOG,GPIO_Pin_3, GPIO_PIN_RESET)
#define Anschluss_6_CS_INAKTIV		HAL_GPIO_WritePin(GPIOG,GPIO_Pin_3, GPIO_PIN_SET)

#define Anschluss_7_CS_AKTIV		HAL_GPIO_WritePin(GPIOA,GPIO_Pin_5, GPIO_PIN_RESET)
#define Anschluss_7_CS_INAKTIV		HAL_GPIO_WritePin(GPIOA,GPIO_Pin_5, GPIO_PIN_SET)

#define Anschluss_8_CS_AKTIV		HAL_GPIO_WritePin(GPIOC,GPIO_Pin_3, GPIO_PIN_RESET)
#define Anschluss_8_CS_INAKTIV		HAL_GPIO_WritePin(GPIOC,GPIO_Pin_3, GPIO_PIN_SET)




// UART

/* Buffer's length must be select according to real messages frequency */
#define RXBUF_LEN            128 // must be power of 2
#define TXBUF_LEN            128 // must be power of 2
#define RXBUF_MSK            (RXBUF_LEN-1)
#define TXBUF_MSK            (TXBUF_LEN-1)
















/******************************************************************************
 * Parameter f�r DSPIN Bibliothek
 * 
 * Grundeinstellungen f�r DSPIN.o f�r STM32
 * muss noch aussortiert werden... 
 * es wird darauf geachtet, den treiber dspin so wenig wie m�glich zu 
 * ver�ndern
 ******************************************************************************
 */

//#define MODUL_0 (1)
/* DSPIN Parameter */
//Aus dspin (pre_include.h) raus kopiert 8 MHZ
// wird aber nirgends gebraucht...
//#define HSE_VALUE    ((uint32_t)8000000) /*!< Value of the External oscillator in Hz */
//im dma.h empfohlen anzugeben...
//Disable DMA2 Stream3 IRQ handler for TM DMA library
#define DMA2_STREAM3_DISABLE_IRQHANDLER

//For all other DMAs and STREAMS, syntax is similar:
#define DMAx_STREAMy_DISABLE_IRQHANDLER
//Where X is 1 or 2 for DMA1 or DMA2 and y is 0 to 7 for STREAM0 to STREAM7 on specific DMA

/* RCC Parameter */
/* I've added these defines in options for target in Keil uVision for each target different settings */
//#define RCC_OSCILLATORTYPE    RCC_OSCILLATORTYPE_HSE /*!< Used to select system oscillator type */
//#define RCC_PLLM              8                      /*!< Used for PLL M parameter */
//#define RCC_PLLN              360                    /*!< Used for PLL N parameter */
//#define RCC_PLLP              2                      /*!< Used for PLL P parameter */
//#define RCC_PLLQ              7                      /*!< Used for PLL Q parameter */
//#define RCC_PLLR              10                     /*!< Used for PLL R parameter, available on STM32F446xx */
//#ifdef MODUL_0 //algemeine einstellung deshalb modul 0 
//	#define dSPIN_nSS_Pin		GPIO_Pin_4
//	#define dSPIN_nSS_Port		GPIOA
//	#define dSPIN_BUSY_Pin		GPIO_Pin_11
//	#define dSPIN_BUSY_Port		GPIOB
//
//	#define dSPIN_FLAG_Pin		GPIO_Pin_10
//	#define dSPIN_FLAG_Port		GPIOB
//
//	#define dSPIN_STBY_RESET_Pin    GPIO_Pin_5
//	#define dSPIN_STBY_RESET_Port   GPIOC
//	#define TIM_PWM                 TIM5
//	 
//				/* List all the peripherals, which CLKs have to be enabled! */
//				/* Note : RCC_APB2Periph_AFIO is mandatory for interrupt enabling */
//	#define dSPIN_PERIPHERAL_CLKs_APB1      (RCC_APB1Periph_TIM5)
//	#define dSPIN_PERIPHERAL_CLKs_APB2	(RCC_APB2Periph_SPI1 | \
//																								 RCC_APB2Periph_GPIOA | \
//																								 RCC_APB2Periph_GPIOB | \
//																								 RCC_APB2Periph_GPIOC | \
//																								 RCC_APB2Periph_AFIO)
//	#endif //modul 0 testeinstellung
#endif
/**
 * @}
 */
