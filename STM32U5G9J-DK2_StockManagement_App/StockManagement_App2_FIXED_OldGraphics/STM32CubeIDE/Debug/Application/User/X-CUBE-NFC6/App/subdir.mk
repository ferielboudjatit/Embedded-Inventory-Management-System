################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/TouchGFXProjects/StockManagement_App2_FIXED_OldGraphics/StockManagement_App2_FIXED_OldGraphics/X-CUBE-NFC6/App/app_x-cube-nfcx.c 

C_DEPS += \
./Application/User/X-CUBE-NFC6/App/app_x-cube-nfcx.d 

OBJS += \
./Application/User/X-CUBE-NFC6/App/app_x-cube-nfcx.o 


# Each subdirectory must supply rules for building sources it contributes
Application/User/X-CUBE-NFC6/App/app_x-cube-nfcx.o: C:/TouchGFXProjects/StockManagement_App2_FIXED_OldGraphics/StockManagement_App2_FIXED_OldGraphics/X-CUBE-NFC6/App/app_x-cube-nfcx.c Application/User/X-CUBE-NFC6/App/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32U5G9xx -DST25R3916B -c -I../../Core/Inc -I../../TouchGFX/App -I../../TouchGFX/target/generated -I../../TouchGFX/target -I../../Drivers/STM32U5xx_HAL_Driver/Inc -I../../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../../Drivers/CMSIS/Include -I../../Middlewares/Third_Party/FreeRTOS/Source/include/ -I../../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM33_NTZ/non_secure/ -I../../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS_V2/ -I../../Middlewares/Third_Party/CMSIS/RTOS2/Include/ -I../../Drivers/BSP -I../../Middlewares/ST/touchgfx/framework/include -I../../TouchGFX/generated/fonts/include -I../../TouchGFX/generated/gui_generated/include -I../../TouchGFX/generated/images/include -I../../TouchGFX/generated/texts/include -I../../TouchGFX/generated/videos/include -I../../TouchGFX/gui/include -I../../X-CUBE-SUBG2/Target -I../../X-CUBE-SUBG2/App -I../../X-CUBE-NFC6/Target -I../../X-CUBE-NFC6/App -I../../Drivers/BSP/S2868A1 -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/Components/S2LP -I../../Drivers/BSP/Components/S2LP/S2LP_Library/inc -I../../Middlewares_patch/rfal/Src -I../../Middlewares_patch/rfal/Inc -I../../Middlewares_patch/ndef/Inc/poller -I../../Middlewares_patch/ndef/Inc/message -I../../Middlewares_patch/ndef/Inc -I../../Middlewares_patch/ST/touchgfx_components/gpu2d/NemaGFX/include -I../../Middlewares_patch/ST/touchgfx_components/gpu2d/TouchGFXNema/include -I../../Middlewares/ST/touchgfx_components/gpu2d/NemaGFX/include -I../../Middlewares/ST/touchgfx_components/gpu2d/TouchGFXNema/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User-2f-X-2d-CUBE-2d-NFC6-2f-App

clean-Application-2f-User-2f-X-2d-CUBE-2d-NFC6-2f-App:
	-$(RM) ./Application/User/X-CUBE-NFC6/App/app_x-cube-nfcx.cyclo ./Application/User/X-CUBE-NFC6/App/app_x-cube-nfcx.d ./Application/User/X-CUBE-NFC6/App/app_x-cube-nfcx.o ./Application/User/X-CUBE-NFC6/App/app_x-cube-nfcx.su

.PHONY: clean-Application-2f-User-2f-X-2d-CUBE-2d-NFC6-2f-App

