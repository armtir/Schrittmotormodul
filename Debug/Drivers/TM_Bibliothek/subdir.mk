################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/TM_Bibliothek/tm_stm32_buffer.c \
../Drivers/TM_Bibliothek/tm_stm32_delay.c \
../Drivers/TM_Bibliothek/tm_stm32_dma.c \
../Drivers/TM_Bibliothek/tm_stm32_dma2d_graphic.c \
../Drivers/TM_Bibliothek/tm_stm32_fonts.c \
../Drivers/TM_Bibliothek/tm_stm32_gpio.c \
../Drivers/TM_Bibliothek/tm_stm32_i2c.c \
../Drivers/TM_Bibliothek/tm_stm32_lcd.c \
../Drivers/TM_Bibliothek/tm_stm32_sdram.c \
../Drivers/TM_Bibliothek/tm_stm32_spi.c \
../Drivers/TM_Bibliothek/tm_stm32_usart.c \
../Drivers/TM_Bibliothek/tm_stm32_usart_dma.c \
../Drivers/TM_Bibliothek/tm_stm32f4_stmpe811.c 

OBJS += \
./Drivers/TM_Bibliothek/tm_stm32_buffer.o \
./Drivers/TM_Bibliothek/tm_stm32_delay.o \
./Drivers/TM_Bibliothek/tm_stm32_dma.o \
./Drivers/TM_Bibliothek/tm_stm32_dma2d_graphic.o \
./Drivers/TM_Bibliothek/tm_stm32_fonts.o \
./Drivers/TM_Bibliothek/tm_stm32_gpio.o \
./Drivers/TM_Bibliothek/tm_stm32_i2c.o \
./Drivers/TM_Bibliothek/tm_stm32_lcd.o \
./Drivers/TM_Bibliothek/tm_stm32_sdram.o \
./Drivers/TM_Bibliothek/tm_stm32_spi.o \
./Drivers/TM_Bibliothek/tm_stm32_usart.o \
./Drivers/TM_Bibliothek/tm_stm32_usart_dma.o \
./Drivers/TM_Bibliothek/tm_stm32f4_stmpe811.o 

C_DEPS += \
./Drivers/TM_Bibliothek/tm_stm32_buffer.d \
./Drivers/TM_Bibliothek/tm_stm32_delay.d \
./Drivers/TM_Bibliothek/tm_stm32_dma.d \
./Drivers/TM_Bibliothek/tm_stm32_dma2d_graphic.d \
./Drivers/TM_Bibliothek/tm_stm32_fonts.d \
./Drivers/TM_Bibliothek/tm_stm32_gpio.d \
./Drivers/TM_Bibliothek/tm_stm32_i2c.d \
./Drivers/TM_Bibliothek/tm_stm32_lcd.d \
./Drivers/TM_Bibliothek/tm_stm32_sdram.d \
./Drivers/TM_Bibliothek/tm_stm32_spi.d \
./Drivers/TM_Bibliothek/tm_stm32_usart.d \
./Drivers/TM_Bibliothek/tm_stm32_usart_dma.d \
./Drivers/TM_Bibliothek/tm_stm32f4_stmpe811.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/TM_Bibliothek/%.o: ../Drivers/TM_Bibliothek/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F429xx -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Inc" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/CMSIS/Include" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/AT_Bibliothek" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/DSPIN_L6472_Treiber" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/TM_Bibliothek" -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


