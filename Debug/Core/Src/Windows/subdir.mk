################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Windows/MenuDLG.c \
../Core/Src/Windows/accWin.c \
../Core/Src/Windows/accWinDLG.c \
../Core/Src/Windows/tempWin.c 

OBJS += \
./Core/Src/Windows/MenuDLG.o \
./Core/Src/Windows/accWin.o \
./Core/Src/Windows/accWinDLG.o \
./Core/Src/Windows/tempWin.o 

C_DEPS += \
./Core/Src/Windows/MenuDLG.d \
./Core/Src/Windows/accWin.d \
./Core/Src/Windows/accWinDLG.d \
./Core/Src/Windows/tempWin.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Windows/%.o: ../Core/Src/Windows/%.c Core/Src/Windows/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F746xx -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM7/r0p1 -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/Hardware/Inc -I../STemWinLib/inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

