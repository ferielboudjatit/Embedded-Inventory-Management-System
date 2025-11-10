################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Commands.c \
../Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Csma.c \
../Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Fifo.c \
../Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_General.c \
../Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Gpio.c \
../Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PacketHandler.c \
../Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktBasic.c \
../Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktStack.c \
../Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktWMbus.c \
../Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Qi.c \
../Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Radio.c \
../Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Timer.c \
../Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Timer_ex.c \
../Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Types.c 

OBJS += \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Commands.o \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Csma.o \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Fifo.o \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_General.o \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Gpio.o \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PacketHandler.o \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktBasic.o \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktStack.o \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktWMbus.o \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Qi.o \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Radio.o \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Timer.o \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Timer_ex.o \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Types.o 

C_DEPS += \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Commands.d \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Csma.d \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Fifo.d \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_General.d \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Gpio.d \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PacketHandler.d \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktBasic.d \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktStack.d \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktWMbus.d \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Qi.d \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Radio.d \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Timer.d \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Timer_ex.d \
./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Types.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/BSP/Components/S2LP/S2LP_Library/src/%.o Drivers/BSP/Components/S2LP/S2LP_Library/src/%.su Drivers/BSP/Components/S2LP/S2LP_Library/src/%.cyclo: ../Drivers/BSP/Components/S2LP/S2LP_Library/src/%.c Drivers/BSP/Components/S2LP/S2LP_Library/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../X-CUBE-SUBG2/Target -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/S2868A1 -I../Drivers/BSP/Components/S2LP -I../Drivers/BSP/Components/S2LP/S2LP_Library/inc -I../X-CUBE-SUBG2/App -I../Drivers/BSP/custom -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-BSP-2f-Components-2f-S2LP-2f-S2LP_Library-2f-src

clean-Drivers-2f-BSP-2f-Components-2f-S2LP-2f-S2LP_Library-2f-src:
	-$(RM) ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Commands.cyclo ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Commands.d ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Commands.o ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Commands.su ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Csma.cyclo ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Csma.d ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Csma.o ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Csma.su ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Fifo.cyclo ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Fifo.d ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Fifo.o ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Fifo.su ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_General.cyclo ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_General.d ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_General.o ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_General.su ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Gpio.cyclo ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Gpio.d ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Gpio.o ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Gpio.su ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PacketHandler.cyclo ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PacketHandler.d ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PacketHandler.o ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PacketHandler.su ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktBasic.cyclo ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktBasic.d ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktBasic.o ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktBasic.su ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktStack.cyclo ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktStack.d ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktStack.o ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktStack.su ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktWMbus.cyclo ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktWMbus.d ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktWMbus.o ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_PktWMbus.su ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Qi.cyclo ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Qi.d ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Qi.o ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Qi.su ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Radio.cyclo ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Radio.d ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Radio.o ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Radio.su ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Timer.cyclo ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Timer.d ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Timer.o ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Timer.su ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Timer_ex.cyclo ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Timer_ex.d ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Timer_ex.o ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Timer_ex.su ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Types.cyclo ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Types.d ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Types.o ./Drivers/BSP/Components/S2LP/S2LP_Library/src/S2LP_Types.su

.PHONY: clean-Drivers-2f-BSP-2f-Components-2f-S2LP-2f-S2LP_Library-2f-src

