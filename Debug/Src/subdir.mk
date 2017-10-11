################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c 

OBJS += \
./Src/main.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o 

C_DEPS += \
./Src/main.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F429xx -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Inc" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/CMSIS/Include" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/AT_Bibliothek" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/DSPIN_L6472_Treiber" -I"/mnt/Speicher/STM32_IDE/STM32_Projekte/Schrittmotor_V4/Drivers/TM_Bibliothek" -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


