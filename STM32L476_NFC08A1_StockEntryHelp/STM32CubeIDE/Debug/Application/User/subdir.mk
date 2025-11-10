################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/analogConfigTbl_NFC08A1.c \
C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/app_x-cube-nfcx.c \
C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/demo_ce.c \
C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/logger.c \
C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/main.c \
C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/ndef_demo.c \
C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/ndef_dump.c \
C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/nfc_conf.c \
C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/stm32l4xx_hal_msp.c \
C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/stm32l4xx_it.c \
C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/stm32l4xx_nucleo.c \
C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/stm32l4xx_nucleo_bus.c \
../Application/User/syscalls.c \
../Application/User/sysmem.c 

OBJS += \
./Application/User/analogConfigTbl_NFC08A1.o \
./Application/User/app_x-cube-nfcx.o \
./Application/User/demo_ce.o \
./Application/User/logger.o \
./Application/User/main.o \
./Application/User/ndef_demo.o \
./Application/User/ndef_dump.o \
./Application/User/nfc_conf.o \
./Application/User/stm32l4xx_hal_msp.o \
./Application/User/stm32l4xx_it.o \
./Application/User/stm32l4xx_nucleo.o \
./Application/User/stm32l4xx_nucleo_bus.o \
./Application/User/syscalls.o \
./Application/User/sysmem.o 

C_DEPS += \
./Application/User/analogConfigTbl_NFC08A1.d \
./Application/User/app_x-cube-nfcx.d \
./Application/User/demo_ce.d \
./Application/User/logger.d \
./Application/User/main.d \
./Application/User/ndef_demo.d \
./Application/User/ndef_dump.d \
./Application/User/nfc_conf.d \
./Application/User/stm32l4xx_hal_msp.d \
./Application/User/stm32l4xx_it.d \
./Application/User/stm32l4xx_nucleo.d \
./Application/User/stm32l4xx_nucleo_bus.d \
./Application/User/syscalls.d \
./Application/User/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Application/User/analogConfigTbl_NFC08A1.o: C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/analogConfigTbl_NFC08A1.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DST25R3916B -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application/User/analogConfigTbl_NFC08A1.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/app_x-cube-nfcx.o: C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/app_x-cube-nfcx.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DST25R3916B -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application/User/app_x-cube-nfcx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/demo_ce.o: C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/demo_ce.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DST25R3916B -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application/User/demo_ce.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/logger.o: C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/logger.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DST25R3916B -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application/User/logger.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/main.o: C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/main.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DST25R3916B -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application/User/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/ndef_demo.o: C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/ndef_demo.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DST25R3916B -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application/User/ndef_demo.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/ndef_dump.o: C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/ndef_dump.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DST25R3916B -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application/User/ndef_dump.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/nfc_conf.o: C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/nfc_conf.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DST25R3916B -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application/User/nfc_conf.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32l4xx_hal_msp.o: C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/stm32l4xx_hal_msp.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DST25R3916B -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application/User/stm32l4xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32l4xx_it.o: C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/stm32l4xx_it.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DST25R3916B -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application/User/stm32l4xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32l4xx_nucleo.o: C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/stm32l4xx_nucleo.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DST25R3916B -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application/User/stm32l4xx_nucleo.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/stm32l4xx_nucleo_bus.o: C:/Users/boudjatf/OneDrive\ -\ STMicroelectronics/Documents/STM32\ Labs/Stock\ Management\ Final\ Projects/STM32L476_NFC08A1_StockEntryHelp/Src/stm32l4xx_nucleo_bus.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DST25R3916B -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"Application/User/stm32l4xx_nucleo_bus.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Application/User/%.o Application/User/%.su Application/User/%.cyclo: ../Application/User/%.c Application/User/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DST25R3916B -DUSE_HAL_DRIVER -DSTM32L476xx -c -I../../Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc -I../../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../../Drivers/CMSIS/Include -I../../Drivers/BSP/Components/ST25R3916 -I../../Drivers/BSP/NFC08A1 -I../../Middlewares/ST/ndef/Inc -I../../Middlewares/ST/ndef/Inc/message -I../../Middlewares/ST/ndef/Inc/poller -I../../Middlewares/ST/rfal/Inc -I../../Middlewares/ST/rfal/Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Application-2f-User

clean-Application-2f-User:
	-$(RM) ./Application/User/analogConfigTbl_NFC08A1.cyclo ./Application/User/analogConfigTbl_NFC08A1.d ./Application/User/analogConfigTbl_NFC08A1.o ./Application/User/analogConfigTbl_NFC08A1.su ./Application/User/app_x-cube-nfcx.cyclo ./Application/User/app_x-cube-nfcx.d ./Application/User/app_x-cube-nfcx.o ./Application/User/app_x-cube-nfcx.su ./Application/User/demo_ce.cyclo ./Application/User/demo_ce.d ./Application/User/demo_ce.o ./Application/User/demo_ce.su ./Application/User/logger.cyclo ./Application/User/logger.d ./Application/User/logger.o ./Application/User/logger.su ./Application/User/main.cyclo ./Application/User/main.d ./Application/User/main.o ./Application/User/main.su ./Application/User/ndef_demo.cyclo ./Application/User/ndef_demo.d ./Application/User/ndef_demo.o ./Application/User/ndef_demo.su ./Application/User/ndef_dump.cyclo ./Application/User/ndef_dump.d ./Application/User/ndef_dump.o ./Application/User/ndef_dump.su ./Application/User/nfc_conf.cyclo ./Application/User/nfc_conf.d ./Application/User/nfc_conf.o ./Application/User/nfc_conf.su ./Application/User/stm32l4xx_hal_msp.cyclo ./Application/User/stm32l4xx_hal_msp.d ./Application/User/stm32l4xx_hal_msp.o ./Application/User/stm32l4xx_hal_msp.su ./Application/User/stm32l4xx_it.cyclo ./Application/User/stm32l4xx_it.d ./Application/User/stm32l4xx_it.o ./Application/User/stm32l4xx_it.su ./Application/User/stm32l4xx_nucleo.cyclo ./Application/User/stm32l4xx_nucleo.d ./Application/User/stm32l4xx_nucleo.o ./Application/User/stm32l4xx_nucleo.su ./Application/User/stm32l4xx_nucleo_bus.cyclo ./Application/User/stm32l4xx_nucleo_bus.d ./Application/User/stm32l4xx_nucleo_bus.o ./Application/User/stm32l4xx_nucleo_bus.su ./Application/User/syscalls.cyclo ./Application/User/syscalls.d ./Application/User/syscalls.o ./Application/User/syscalls.su ./Application/User/sysmem.cyclo ./Application/User/sysmem.d ./Application/User/sysmem.o ./Application/User/sysmem.su

.PHONY: clean-Application-2f-User

