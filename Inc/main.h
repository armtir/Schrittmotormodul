/**
  ******************************************************************************
  * File Name          : main.h
  * Description        : This file contains the common defines of the application
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H
  /* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

/*
 * Armin 230917
 * Hätte man nicht in CubeMX ändern sollen
 * unnötige Defines...
 */

#define INT_A_Pin GPIO_PIN_2
#define INT_A_GPIO_Port GPIOE
#define INT_A_EXTI_IRQn EXTI2_IRQn
#define INT_B_Pin GPIO_PIN_3
#define INT_B_GPIO_Port GPIOE
#define INT_B_EXTI_IRQn EXTI3_IRQn
#define nUSB_Mode_Pin GPIO_PIN_4
#define nUSB_Mode_GPIO_Port GPIOE
#define nUSB_Mode_EXTI_IRQn EXTI4_IRQn
#define SCK_0_Pin GPIO_PIN_5
#define SCK_0_GPIO_Port GPIOE
#define SCK_1_Pin GPIO_PIN_6
#define SCK_1_GPIO_Port GPIOE
#define SCK_2_Pin GPIO_PIN_13
#define SCK_2_GPIO_Port GPIOC
#define SCK_4_Pin GPIO_PIN_3
#define SCK_4_GPIO_Port GPIOC
#define Blauer_Taster_Pin GPIO_PIN_0
#define Blauer_Taster_GPIO_Port GPIOA
#define Blauer_Taster_EXTI_IRQn EXTI0_IRQn
#define SCK_3_Pin GPIO_PIN_5
#define SCK_3_GPIO_Port GPIOA
#define RED_LED_Pin GPIO_PIN_5
#define RED_LED_GPIO_Port GPIOC
#define SCK_5_Pin GPIO_PIN_2
#define SCK_5_GPIO_Port GPIOG
#define SCK_6_Pin GPIO_PIN_3
#define SCK_6_GPIO_Port GPIOG
#define SCK_7_Pin GPIO_PIN_8
#define SCK_7_GPIO_Port GPIOC
#define Touch_Panel_Interrupt_Pin GPIO_PIN_15
#define Touch_Panel_Interrupt_GPIO_Port GPIOA
#define Touch_Panel_Interrupt_EXTI_IRQn EXTI15_10_IRQn
#define SCK_8_Pin GPIO_PIN_2
#define SCK_8_GPIO_Port GPIOD
#define LED_Green_Pin GPIO_PIN_13
#define LED_Green_GPIO_Port GPIOG
#define LED_Red_Pin GPIO_PIN_14
#define LED_Red_GPIO_Port GPIOG

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __MAIN_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
