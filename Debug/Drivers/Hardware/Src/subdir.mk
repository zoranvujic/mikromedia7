################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Hardware/Src/ADXL345.c \
../Drivers/Hardware/Src/SSD1963.c \
../Drivers/Hardware/Src/STMPE610.c 

OBJS += \
./Drivers/Hardware/Src/ADXL345.o \
./Drivers/Hardware/Src/SSD1963.o \
./Drivers/Hardware/Src/STMPE610.o 

C_DEPS += \
./Drivers/Hardware/Src/ADXL345.d \
./Drivers/Hardware/Src/SSD1963.d \
./Drivers/Hardware/Src/STMPE610.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Hardware/Src/%.o: ../Drivers/Hardware/Src/%.c Drivers/Hardware/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/Hardware/Inc -I../STemWinLib/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

