################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/AT_Bibliothek/at_io_expander.c \
../Drivers/AT_Bibliothek/at_lcd.c \
../Drivers/AT_Bibliothek/at_schrittmotor.c \
../Drivers/AT_Bibliothek/at_uart.c 

OBJS += \
./Drivers/AT_Bibliothek/at_io_expander.o \
./Drivers/AT_Bibliothek/at_lcd.o \
./Drivers/AT_Bibliothek/at_schrittmotor.o \
./Drivers/AT_Bibliothek/at_uart.o 

C_DEPS += \
./Drivers/AT_Bibliothek/at_io_expander.d \
./Drivers/AT_Bibliothek/at_lcd.d \
./Drivers/AT_Bibliothek/at_schrittmotor.d \
./Drivers/AT_Bibliothek/at_uart.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/AT_Bibliothek/%.o: ../Drivers/AT_Bibliothek/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F429xx -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Inc" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/CMSIS/Include" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/AT_Bibliothek" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/DSPIN_L6472_Treiber" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/TM_Bibliothek" -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


