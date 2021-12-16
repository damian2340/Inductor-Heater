################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/dma.c \
../Core/Src/gpio.c \
../Core/Src/hrtim.c \
../Core/Src/main.c \
../Core/Src/stm32f3xx_hal_msp.c \
../Core/Src/stm32f3xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/system_stm32f3xx.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/dma.o \
./Core/Src/gpio.o \
./Core/Src/hrtim.o \
./Core/Src/main.o \
./Core/Src/stm32f3xx_hal_msp.o \
./Core/Src/stm32f3xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/system_stm32f3xx.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/dma.d \
./Core/Src/gpio.d \
./Core/Src/hrtim.d \
./Core/Src/main.d \
./Core/Src/stm32f3xx_hal_msp.d \
./Core/Src/stm32f3xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/system_stm32f3xx.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F334x8 -I"E:/Users/damian/Documents/Proyectos/Nucleo-f334_USART_IDLE_DMA/Nueva carpeta/IH/Core/Inc" -I"E:/Users/damian/Documents/Proyectos/Nucleo-f334_USART_IDLE_DMA/Nueva carpeta/IH/Drivers/STM32F3xx_HAL_Driver/Inc" -I"E:/Users/damian/Documents/Proyectos/Nucleo-f334_USART_IDLE_DMA/Nueva carpeta/IH/Drivers/STM32F3xx_HAL_Driver/Inc/Legacy" -I"E:/Users/damian/Documents/Proyectos/Nucleo-f334_USART_IDLE_DMA/Nueva carpeta/IH/Drivers/CMSIS/Device/ST/STM32F3xx/Include" -I"E:/Users/damian/Documents/Proyectos/Nucleo-f334_USART_IDLE_DMA/Nueva carpeta/IH/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


