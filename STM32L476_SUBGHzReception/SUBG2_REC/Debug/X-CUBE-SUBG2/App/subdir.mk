################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../X-CUBE-SUBG2/App/app_x-cube-subg2.c 

OBJS += \
./X-CUBE-SUBG2/App/app_x-cube-subg2.o 

C_DEPS += \
./X-CUBE-SUBG2/App/app_x-cube-subg2.d 


# Each subdirectory must supply rules for building sources it contributes
X-CUBE-SUBG2/App/%.o X-CUBE-SUBG2/App/%.su X-CUBE-SUBG2/App/%.cyclo: ../X-CUBE-SUBG2/App/%.c X-CUBE-SUBG2/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../Core/Inc -I../X-CUBE-SUBG2/Target -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/CMSIS/Include -I../Drivers/BSP/S2868A1 -I../Drivers/BSP/Components/S2LP -I../Drivers/BSP/Components/S2LP/S2LP_Library/inc -I../X-CUBE-SUBG2/App -I../Drivers/BSP/custom -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@"  -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-X-2d-CUBE-2d-SUBG2-2f-App

clean-X-2d-CUBE-2d-SUBG2-2f-App:
	-$(RM) ./X-CUBE-SUBG2/App/app_x-cube-subg2.cyclo ./X-CUBE-SUBG2/App/app_x-cube-subg2.d ./X-CUBE-SUBG2/App/app_x-cube-subg2.o ./X-CUBE-SUBG2/App/app_x-cube-subg2.su

.PHONY: clean-X-2d-CUBE-2d-SUBG2-2f-App

