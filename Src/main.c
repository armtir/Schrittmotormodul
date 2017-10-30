/**
 ******************************************************************************
 * File Name          : main.c
 * Description        : Main program body
 ******************************************************************************
 ** This notice applies to any and all portions of this file
 * that are not between comment pairs USER CODE BEGIN and
 * USER CODE END. Other portions of this file, whether
 * inserted by the user or by software development tools
 * are owned by their respective copyright owners.
 *
 * COPYRIGHT(c) 2017 STMicroelectronics
 *
 * Redistribution and use in source and binary forms, with or without
 *modification,
 * are permitted provided that the following conditions are met:
 *   1. Redistributions of source code must retain the above copyright notice,
 *      this list of conditions and the following disclaimer.
 *   2. Redistributions in binary form must reproduce the above copyright
 *notice,
 *      this list of conditions and the following disclaimer in the
 *documentation
 *      and/or other materials provided with the distribution.
 *   3. Neither the name of STMicroelectronics nor the names of its contributors
 *      may be used to endorse or promote products derived from this software
 *      without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************
 */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */
#include "at_io_expander.h"
#include "at_lcd.h"
#include "at_schrittmotor.h"
#include "at_uart.h"

#include "tm_stm32_lcd.h"
#include "tm_stm32_spi.h"
#include "tm_stm32_usart.h"
#include "tm_stm32f4_stmpe811.h"

#include "dspin.h"
#include "dspin_config.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
DMA2D_HandleTypeDef hdma2d;

I2C_HandleTypeDef hi2c3;

LTDC_HandleTypeDef hltdc;

SPI_HandleTypeDef hspi3;
SPI_HandleTypeDef hspi5;

UART_HandleTypeDef huart1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

DMA_HandleTypeDef hdma_memtomem_dma2_stream0;
SDRAM_HandleTypeDef hsdram1;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
// TM_STMPE811_t LCD_Config;
TM_STMPE811_t LCD_Config;

// dSPIN_RegsStruct_TypeDef dSPIN_RegsStruct;
/*
 * Globale Variablen
 * Anschluss:
 *    Diese Variable muss leider global sein, weil sie in der Bibliothek von
 *    TM in einer Unterfunktion aufgerufen wird.
 *    Ich m�sste allen Funktionen diesen Parameter �bergeben und das ist eine
 *    Heidenarbeit
 *    Sie wird nur von der UART Funktion und der Initialisierung geschrieben
 *    alle anderen lesen
 *
 * INIT_DONE:
 *    Wird verwendet damit Interrupts nicht bevor der Initialisierungs
 *    Prozess abgeschlossen ist ausgeführt werden
 */
uint8_t anschluss = 0;
uint8_t INIT_DONE = FALSE;

/* Diese hier werden noch als lokale
 * Variablen definiert
 */
uint8_t aktuelle_seite = 0;
uint8_t aktuelle_taste = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_SPI3_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_DMA2D_Init(void);
static void MX_FMC_Init(void);
static void MX_SPI5_Init(void);
static void MX_LTDC_Init(void);
static void MX_I2C3_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
/* UART1_data keine ahnung... */
char UART1_Data = 0;
/* UART Buffer für Ein- und Ausgabe */
/* was das ist weis ich auch nicht... */
/* USER CODE END 0 */

int main(void) {
   /* USER CODE BEGIN 1 */
   //__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);
   /* USER CODE END 1 */

   /* MCU
    * Configuration----------------------------------------------------------*/

   /* Reset of all peripherals, Initializes the Flash interface and the Systick.
    */
   HAL_Init();

   /* USER CODE BEGIN Init */

   /* USER CODE END Init */

   /* Configure the system clock */
   SystemClock_Config();

   /* USER CODE BEGIN SysInit */

   /* USER CODE END SysInit */

   /* Initialize all configured peripherals */
   MX_GPIO_Init();
   MX_DMA_Init();
   MX_SPI3_Init();
   MX_USART1_UART_Init();
   MX_DMA2D_Init();
   MX_FMC_Init();
   MX_SPI5_Init();
   MX_LTDC_Init();
   MX_I2C3_Init();

   /* USER CODE BEGIN 2 */

   /* Setze alle CS Signale auf Inaktiv
    *
    * Könnte man auch mit Enumeration lösen...
    * Hier aber wurst
    */
   Expander_CS_INAKTIV;
   Anschluss_1_CS_INAKTIV;
   Anschluss_2_CS_INAKTIV;
   Anschluss_3_CS_INAKTIV;
   Anschluss_4_CS_INAKTIV;
   Anschluss_5_CS_INAKTIV;
   Anschluss_6_CS_INAKTIV;
   Anschluss_7_CS_INAKTIV;
   Anschluss_8_CS_INAKTIV;

   /*
    * Initialisierung der einzelen Module
    */
   TM_SPI_Init(EXPANDER_SPI, EXPANDER_SPI_PINS);
   HAL_Delay(100);
   at_lcd_init(&LCD_Config);
   at_lcd_page_0();
   LCD_INFO("Initialisierung");
   HAL_Delay(1000);
   at_schrittmotor_init();
   HAL_Delay(100);
   at_expander_init();
   HAL_Delay(100);
   LCD_INFO("abgeschlossen");
   LCD_INFO("uint8 %d", sizeof(uint8_t));
   LCD_INFO("char %d", sizeof(UART1_Data));
   HAL_Delay(2000);
   TM_LCD_Init();
   HAL_Delay(2000);

   /* Starte HAL UART Interrupt */
   HAL_UART_Receive_IT(&huart1, &UART1_Data, sizeof(UART1_Data));

   INIT_DONE = TRUE;
   /*
    * Die HAL_Delay Funktion taucht im Quellcode leider immer wieder auf.
    * Da viele Abläufe nur mit einer gewissen Verzögerung funktionieren,
    * muss die Funktion drin bleiben. Eine bessere Lösung ist mir noch nicht
    * eingefallen.
    * Laut stm32f4xx_hal.c benutzt HAL_Delay die Systick Funktion.
    */

   // MÜLL glaube ich...
   // at_lcd_start();
   // at_lcd_page_1(0, 0);
   // char UART_Aux[32] = {0};
   // uint8_t i = 97;
   /* USER CODE END 2 */

   /* Infinite loop */
   /* USER CODE BEGIN WHILE */
   while (1) {
      /* USER CODE END WHILE */
      /* USER CODE BEGIN 3 */
      // UART_Aux[0] = i;
      // at_lcd_debug(&UART_Aux);
      // i++;
      // HAL_Delay(1000);
   }
   /* USER CODE END 3 */
}

/*
 * System Clock Configuration
 */
void SystemClock_Config(void) {
   RCC_OscInitTypeDef RCC_OscInitStruct;
   RCC_ClkInitTypeDef RCC_ClkInitStruct;
   RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;

   /*
    *Configure the main internal regulator output voltage
    */
   __HAL_RCC_PWR_CLK_ENABLE();

   __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

   /*
    *Initializes the CPU, AHB and APB busses clocks
    */
   RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
   RCC_OscInitStruct.HSEState = RCC_HSE_ON;
   RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
   RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
   RCC_OscInitStruct.PLL.PLLM = 8;
   RCC_OscInitStruct.PLL.PLLN = 360;
   RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
   RCC_OscInitStruct.PLL.PLLQ = 7;
   if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
      _Error_Handler(__FILE__, __LINE__);
   }

   /*
    *Activate the Over-Drive mode
    */
   if (HAL_PWREx_EnableOverDrive() != HAL_OK) {
      _Error_Handler(__FILE__, __LINE__);
   }

   /*
    *Initializes the CPU, AHB and APB busses clocks
    */
   RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                 RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
   RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
   RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
   RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
   RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

   if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
      _Error_Handler(__FILE__, __LINE__);
   }

   PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
   PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;
   PeriphClkInitStruct.PLLSAI.PLLSAIR = 4;
   PeriphClkInitStruct.PLLSAIDivR = RCC_PLLSAIDIVR_2;
   if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK) {
      _Error_Handler(__FILE__, __LINE__);
   }

   /*
    *Configure the Systick interrupt time
    */
   HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq() / 1000);

   /*
    *Configure the Systick
    */
   HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

   /* SysTick_IRQn interrupt configuration */
   HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* DMA2D init function */
static void MX_DMA2D_Init(void) {
   hdma2d.Instance = DMA2D;
   hdma2d.Init.Mode = DMA2D_M2M;
   hdma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
   hdma2d.Init.OutputOffset = 0;
   hdma2d.LayerCfg[1].InputOffset = 0;
   hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
   hdma2d.LayerCfg[1].AlphaMode = DMA2D_COMBINE_ALPHA;
   hdma2d.LayerCfg[1].InputAlpha = 0;
   if (HAL_DMA2D_Init(&hdma2d) != HAL_OK) {
      _Error_Handler(__FILE__, __LINE__);
   }

   if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK) {
      _Error_Handler(__FILE__, __LINE__);
   }
}

/* I2C3 init function */
static void MX_I2C3_Init(void) {
   hi2c3.Instance = I2C3;
   hi2c3.Init.ClockSpeed = 10000;
   hi2c3.Init.DutyCycle = I2C_DUTYCYCLE_2;
   hi2c3.Init.OwnAddress1 = 0;
   hi2c3.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
   hi2c3.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
   hi2c3.Init.OwnAddress2 = 0;
   hi2c3.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
   hi2c3.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
   if (HAL_I2C_Init(&hi2c3) != HAL_OK) {
      _Error_Handler(__FILE__, __LINE__);
   }
}

/* LTDC init function */
static void MX_LTDC_Init(void) {
   LTDC_LayerCfgTypeDef pLayerCfg;

   hltdc.Instance = LTDC;
   hltdc.Init.HSPolarity = LTDC_HSPOLARITY_AL;
   hltdc.Init.VSPolarity = LTDC_VSPOLARITY_AL;
   hltdc.Init.DEPolarity = LTDC_DEPOLARITY_AL;
   hltdc.Init.PCPolarity = LTDC_PCPOLARITY_IPC;
   hltdc.Init.HorizontalSync = 7;
   hltdc.Init.VerticalSync = 3;
   hltdc.Init.AccumulatedHBP = 14;
   hltdc.Init.AccumulatedVBP = 5;
   hltdc.Init.AccumulatedActiveW = 654;
   hltdc.Init.AccumulatedActiveH = 485;
   hltdc.Init.TotalWidth = 660;
   hltdc.Init.TotalHeigh = 487;
   hltdc.Init.Backcolor.Blue = 0;
   hltdc.Init.Backcolor.Green = 0;
   hltdc.Init.Backcolor.Red = 0;
   if (HAL_LTDC_Init(&hltdc) != HAL_OK) {
      _Error_Handler(__FILE__, __LINE__);
   }

   pLayerCfg.WindowX0 = 0;
   pLayerCfg.WindowX1 = 0;
   pLayerCfg.WindowY0 = 0;
   pLayerCfg.WindowY1 = 0;
   pLayerCfg.PixelFormat = LTDC_PIXEL_FORMAT_ARGB8888;
   pLayerCfg.Alpha = 0;
   pLayerCfg.Alpha0 = 0;
   pLayerCfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
   pLayerCfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
   pLayerCfg.FBStartAdress = 0;
   pLayerCfg.ImageWidth = 0;
   pLayerCfg.ImageHeight = 0;
   pLayerCfg.Backcolor.Blue = 0;
   pLayerCfg.Backcolor.Green = 0;
   pLayerCfg.Backcolor.Red = 0;
   if (HAL_LTDC_ConfigLayer(&hltdc, &pLayerCfg, 0) != HAL_OK) {
      _Error_Handler(__FILE__, __LINE__);
   }
}

/* SPI3 init function */
static void MX_SPI3_Init(void) {
   /* SPI3 parameter configuration*/
   hspi3.Instance = SPI3;
   hspi3.Init.Mode = SPI_MODE_MASTER;
   hspi3.Init.Direction = SPI_DIRECTION_2LINES;
   hspi3.Init.DataSize = SPI_DATASIZE_8BIT;
   hspi3.Init.CLKPolarity = SPI_POLARITY_LOW;
   hspi3.Init.CLKPhase = SPI_PHASE_1EDGE;
   hspi3.Init.NSS = SPI_NSS_SOFT;
   hspi3.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
   hspi3.Init.FirstBit = SPI_FIRSTBIT_MSB;
   hspi3.Init.TIMode = SPI_TIMODE_DISABLE;
   hspi3.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
   hspi3.Init.CRCPolynomial = 10;
   if (HAL_SPI_Init(&hspi3) != HAL_OK) {
      _Error_Handler(__FILE__, __LINE__);
   }
}

/* SPI5 init function */
static void MX_SPI5_Init(void) {
   /* SPI5 parameter configuration*/
   hspi5.Instance = SPI5;
   hspi5.Init.Mode = SPI_MODE_MASTER;
   hspi5.Init.Direction = SPI_DIRECTION_2LINES;
   hspi5.Init.DataSize = SPI_DATASIZE_8BIT;
   hspi5.Init.CLKPolarity = SPI_POLARITY_LOW;
   hspi5.Init.CLKPhase = SPI_PHASE_1EDGE;
   hspi5.Init.NSS = SPI_NSS_SOFT;
   hspi5.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
   hspi5.Init.FirstBit = SPI_FIRSTBIT_MSB;
   hspi5.Init.TIMode = SPI_TIMODE_DISABLE;
   hspi5.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
   hspi5.Init.CRCPolynomial = 10;
   if (HAL_SPI_Init(&hspi5) != HAL_OK) {
      _Error_Handler(__FILE__, __LINE__);
   }
}

/* USART1 init function */
static void MX_USART1_UART_Init(void) {
   huart1.Instance = USART1;
   huart1.Init.BaudRate = 115200;
   huart1.Init.WordLength = UART_WORDLENGTH_8B;
   huart1.Init.StopBits = UART_STOPBITS_1;
   huart1.Init.Parity = UART_PARITY_NONE;
   huart1.Init.Mode = UART_MODE_TX_RX;
   huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
   huart1.Init.OverSampling = UART_OVERSAMPLING_16;
   if (HAL_UART_Init(&huart1) != HAL_OK) {
      _Error_Handler(__FILE__, __LINE__);
   }
}

/*
 * Enable DMA controller clock
 * Configure DMA for memory to memory transfers
 * hdma_memtomem_dma2_stream0
 */
static void MX_DMA_Init(void) {
   /* DMA controller clock enable */
   __HAL_RCC_DMA2_CLK_ENABLE();

   /* Configure DMA request hdma_memtomem_dma2_stream0 on DMA2_Stream0 */
   hdma_memtomem_dma2_stream0.Instance = DMA2_Stream0;
   hdma_memtomem_dma2_stream0.Init.Channel = DMA_CHANNEL_0;
   hdma_memtomem_dma2_stream0.Init.Direction = DMA_MEMORY_TO_MEMORY;
   hdma_memtomem_dma2_stream0.Init.PeriphInc = DMA_PINC_ENABLE;
   hdma_memtomem_dma2_stream0.Init.MemInc = DMA_MINC_ENABLE;
   hdma_memtomem_dma2_stream0.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
   hdma_memtomem_dma2_stream0.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
   hdma_memtomem_dma2_stream0.Init.Mode = DMA_NORMAL;
   hdma_memtomem_dma2_stream0.Init.Priority = DMA_PRIORITY_LOW;
   hdma_memtomem_dma2_stream0.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
   hdma_memtomem_dma2_stream0.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
   hdma_memtomem_dma2_stream0.Init.MemBurst = DMA_MBURST_SINGLE;
   hdma_memtomem_dma2_stream0.Init.PeriphBurst = DMA_PBURST_SINGLE;
   if (HAL_DMA_Init(&hdma_memtomem_dma2_stream0) != HAL_OK) {
      _Error_Handler(__FILE__, __LINE__);
   }

   /* DMA interrupt init */
   /* DMA2_Stream2_IRQn interrupt configuration */
   HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
   HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);
   /* DMA2_Stream7_IRQn interrupt configuration */
   HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
   HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
}
/* FMC initialization function */
static void MX_FMC_Init(void) {
   FMC_SDRAM_TimingTypeDef SdramTiming;

   /*
    * Perform the SDRAM1 memory initialization sequence
    */
   hsdram1.Instance = FMC_SDRAM_DEVICE;
   /* hsdram1.Init */
   hsdram1.Init.SDBank = FMC_SDRAM_BANK2;
   hsdram1.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
   hsdram1.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
   hsdram1.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
   hsdram1.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_2;
   hsdram1.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_1;
   hsdram1.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
   hsdram1.Init.SDClockPeriod = FMC_SDRAM_CLOCK_DISABLE;
   hsdram1.Init.ReadBurst = FMC_SDRAM_RBURST_DISABLE;
   hsdram1.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
   /* SdramTiming */
   SdramTiming.LoadToActiveDelay = 16;
   SdramTiming.ExitSelfRefreshDelay = 16;
   SdramTiming.SelfRefreshTime = 16;
   SdramTiming.RowCycleDelay = 16;
   SdramTiming.WriteRecoveryTime = 16;
   SdramTiming.RPDelay = 16;
   SdramTiming.RCDDelay = 16;

   if (HAL_SDRAM_Init(&hsdram1, &SdramTiming) != HAL_OK) {
      _Error_Handler(__FILE__, __LINE__);
   }
}

/*
 * Configure pins as
 * Analog
 * Input
 * Output
 * EVENT_OUT
 * EXTI
 PB12   ------> USB_OTG_HS_ID
 PB13   ------> USB_OTG_HS_VBUS
 PB14   ------> USB_OTG_HS_DM
 PB15   ------> USB_OTG_HS_DP
 */
static void MX_GPIO_Init(void) {
   GPIO_InitTypeDef GPIO_InitStruct;

   /* GPIO Ports Clock Enable */
   __HAL_RCC_GPIOE_CLK_ENABLE();
   __HAL_RCC_GPIOC_CLK_ENABLE();
   __HAL_RCC_GPIOF_CLK_ENABLE();
   __HAL_RCC_GPIOH_CLK_ENABLE();
   __HAL_RCC_GPIOA_CLK_ENABLE();
   __HAL_RCC_GPIOB_CLK_ENABLE();
   __HAL_RCC_GPIOG_CLK_ENABLE();
   __HAL_RCC_GPIOD_CLK_ENABLE();

   /*Configure GPIO pin Output Level */
   HAL_GPIO_WritePin(GPIOE, SCK_0_Pin | SCK_1_Pin, GPIO_PIN_RESET);

   /*Configure GPIO pin Output Level */
   HAL_GPIO_WritePin(GPIOC, SCK_2_Pin | SCK_4_Pin | RED_LED_Pin | SCK_7_Pin,
                     GPIO_PIN_RESET);

   /*Configure GPIO pin Output Level */
   HAL_GPIO_WritePin(SCK_3_GPIO_Port, SCK_3_Pin, GPIO_PIN_RESET);

   /*Configure GPIO pin Output Level */
   HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | SCK_8_Pin,
                     GPIO_PIN_RESET);

   /*Configure GPIO pin Output Level */
   HAL_GPIO_WritePin(GPIOG, SCK_5_Pin | SCK_6_Pin | LED_Green_Pin | LED_Red_Pin,
                     GPIO_PIN_RESET);

   /*Configure GPIO pins : INT_A_Pin INT_B_Pin nUSB_Mode_Pin */
   GPIO_InitStruct.Pin = INT_A_Pin | INT_B_Pin | nUSB_Mode_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

   /*Configure GPIO pins : SCK_0_Pin SCK_1_Pin */
   GPIO_InitStruct.Pin = SCK_0_Pin | SCK_1_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

   /*Configure GPIO pins : SCK_2_Pin SCK_4_Pin RED_LED_Pin SCK_7_Pin */
   GPIO_InitStruct.Pin = SCK_2_Pin | SCK_4_Pin | RED_LED_Pin | SCK_7_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

   /*Configure GPIO pins : Blauer_Taster_Pin Touch_Panel_Interrupt_Pin */
   GPIO_InitStruct.Pin = Blauer_Taster_Pin | Touch_Panel_Interrupt_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

   /*Configure GPIO pin : SCK_3_Pin */
   GPIO_InitStruct.Pin = SCK_3_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(SCK_3_GPIO_Port, &GPIO_InitStruct);

   /*Configure GPIO pin : PB2 */
   GPIO_InitStruct.Pin = GPIO_PIN_2;
   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

   /*Configure GPIO pins : PB12 PB14 PB15 */
   GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_14 | GPIO_PIN_15;
   GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
   GPIO_InitStruct.Alternate = GPIO_AF12_OTG_HS_FS;
   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

   /*Configure GPIO pin : PB13 */
   GPIO_InitStruct.Pin = GPIO_PIN_13;
   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

   /*Configure GPIO pin : PD11 */
   GPIO_InitStruct.Pin = GPIO_PIN_11;
   GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

   /*Configure GPIO pins : PD12 PD13 SCK_8_Pin */
   GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | SCK_8_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

   /*Configure GPIO pins : SCK_5_Pin SCK_6_Pin LED_Green_Pin LED_Red_Pin */
   GPIO_InitStruct.Pin = SCK_5_Pin | SCK_6_Pin | LED_Green_Pin | LED_Red_Pin;
   GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
   GPIO_InitStruct.Pull = GPIO_NOPULL;
   GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

   /* EXTI interrupt init*/
   HAL_NVIC_SetPriority(EXTI0_IRQn, 4, 5);
   HAL_NVIC_EnableIRQ(EXTI0_IRQn);

   HAL_NVIC_SetPriority(EXTI2_IRQn, 2, 2);
   HAL_NVIC_EnableIRQ(EXTI2_IRQn);

   HAL_NVIC_SetPriority(EXTI3_IRQn, 2, 4);
   HAL_NVIC_EnableIRQ(EXTI3_IRQn);

   HAL_NVIC_SetPriority(EXTI4_IRQn, 5, 5);
   HAL_NVIC_EnableIRQ(EXTI4_IRQn);

   HAL_NVIC_SetPriority(EXTI15_10_IRQn, 3, 0);
   HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/* USER CODE BEGIN 4 */
/*
 *******************************************************************************
 * GPIO Interrupt Callbackfunktionen
 *******************************************************************************
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
   /*
    * Interrupt blauer Taster (Level 4)
    * Der blaue Taster hat keine spezifische Funktion.
    * Er kann zum Debugen o.ä. eingesetzt werden.
    */
   if (GPIO_Pin == GPIO_PIN_0 && INIT_DONE) {
      // at_expander_stck();
      at_debug(&LCD_Config);
      HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
   }

   /*
    * Interrupt IO Expander A FLAG (Level 2)
    * Flag: Signalisiert, dass einer der Schrittmotortreiber
    * einen Fehler signalisiert
    */
   if (GPIO_Pin == GPIO_PIN_2 && INIT_DONE) {
      uint8_t test = 0;
      /*
       * Warten bis spi pipe frei ist
       * Besser wäre hier: HAL_SPI_STATE_BUSY_TX_RX abfragen
       */
      HAL_Delay(10);

      test = at_expander_readdata(ExpanderA, INTFA, 0x00);
      at_expander_readdata(ExpanderA, INTCAPA, 0x00);
      LCD_INFO("Flag:" BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(test));
   }

   /*
    * Interrupt IO Expander B BUSY (Level 5)
    * Signalisiert ob Befehle noch abgearbeitet werden
    */
   if (GPIO_Pin == GPIO_PIN_3 && INIT_DONE) {
      uint8_t test = 0;
      /* Warten bis spi pipe frei ist */
      HAL_Delay(10);
      test = at_expander_readdata(ExpanderB, INTFA, 0x00);
      at_expander_readdata(ExpanderB, INTCAPA, 0x00);

      LCD_INFO("Busy:" BYTE_TO_BINARY_PATTERN, BYTE_TO_BINARY(test));
   }

   /*
    * Interrupt USB Kabel eingesteckt (Level 5)
    * Für nähere Infos siehe Stromlaufplan
    * Bei eingestecktem USB Kabel PC --> 5V wird der Step-Down Konverter
    * deaktiviert
    */
   if (GPIO_Pin == GPIO_PIN_4 && INIT_DONE) {
      at_lcd_error();
   }

   /*
    * Interrupt Touchdisplay (Level 4)
    * Bei Tastendruck aktiv
    */
   if (GPIO_Pin == GPIO_PIN_15 && INIT_DONE) {
      // at_lcd_test(&LCD_Config);
      at_lcd_state(&LCD_Config);
      HAL_Delay(100);
      // touch detection delay register verhindert "prellen" --> wäre besser
      /* Setze Interrupt zurück */
      TM_I2C_Write(STMPE811_I2C, 0x82, 0x0B, 0x01);
   }
}
/*
 *******************************************************************************
 * UART Empfang Callbackfunktion
 *******************************************************************************
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef* huart) {
   static uint8_t init = 1;
   static uint16_t len = 0;
   char UART_Buffer[MAX_BUFFER];

   /*
    * Initialisierungsvorgang mittels static Variable
    * Buffer initialisieren
    * Warten bis kein Müll mehr daherkommt... (zu Beginn wird irgendwas in den 
    * Buffer geschrieben)
    */

   if (init == 1 || UART1_Data == '~') {
      UART1_Data = 0;
      memset(UART_Buffer, 0, MAX_BUFFER);
      init = 0;
   }

   /* Fülle Buffer mittels Callbackfunktion */
   if (huart->Instance == USART1) {
      /* Solange kein Zeilenumbruch CR (0x0D) weiter Buffer befüllen  */
      if (UART1_Data != 0x0D) {
         UART_Buffer[len] = UART1_Data;
         /* len ist gleich die Stringlänge */
         len++;
         /* Wenn CR erreicht \0 rein schreiben und auf Display und UART */
      } else {
         UART_Buffer[len] = '\0';
         // at_uart_interpreter(&UART_Buffer);
         at_lcd_debug(&UART_Buffer);
         HAL_UART_Transmit(&huart1, UART_Buffer, len, 1000);

         /* len und Buffer zurücksetzen */
         memset(UART_Buffer, 0, MAX_BUFFER);
         len = 0;
      }

      HAL_UART_Receive_IT(&huart1, &UART1_Data, sizeof(UART1_Data));
   }
}

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @param  None
 * @retval None
 */
void _Error_Handler(char* file, int line) {
   /* USER CODE BEGIN Error_Handler_Debug */

   /* User can add his own implementation to report the HAL error return state
    */
   while (1) {
   }
   /* USER CODE END Error_Handler_Debug */
}

#ifdef USE_FULL_ASSERT

/**
 * @brief Reports the name of the source file and the source line number
 * where the assert_param error has occurred.
 * @param file: pointer to the source file name
 * @param line: assert_param error line source number
 * @retval None
 */
void assert_failed(uint8_t* file, uint32_t line) {
   /* USER CODE BEGIN 6 */
   /* User can add his own implementation to report the file name and line
    number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
   /* USER CODE END 6 */
}

#endif

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
