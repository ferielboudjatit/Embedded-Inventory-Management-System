################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/X-CUBE-NFC6/Wireless/MID_LIB/RFAL/Default_Config/subdir.mk
-include Middlewares/X-CUBE-NFC6/Wireless/MID_LIB/NDEF/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/subdir.mk
-include Drivers/CMSIS/subdir.mk
-include Drivers/BSP/NFC/subdir.mk
-include Drivers/BSP/Components/subdir.mk
-include Application/User/subdir.mk
-include Application/Startup/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := NFC08A1_PollingTagDetectNDEF
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
NFC08A1_PollingTagDetectNDEF.elf \

MAP_FILES += \
NFC08A1_PollingTagDetectNDEF.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
NFC08A1_PollingTagDetectNDEF.list \


# All Target
all: main-build

# Main-build Target
main-build: NFC08A1_PollingTagDetectNDEF.elf secondary-outputs

# Tool invocations
NFC08A1_PollingTagDetectNDEF.elf NFC08A1_PollingTagDetectNDEF.map: $(OBJS) $(USER_OBJS) C:\Users\boudjatf\OneDrive\ -\ STMicroelectronics\Documents\STM32\ Labs\Stock\ Management\ Final\ Projects\STM32L476_NFC08A1_StockEntryHelp\STM32CubeIDE\STM32L476RGTX_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "NFC08A1_PollingTagDetectNDEF.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\boudjatf\OneDrive - STMicroelectronics\Documents\STM32 Labs\Stock Management Final Projects\STM32L476_NFC08A1_StockEntryHelp\STM32CubeIDE\STM32L476RGTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="NFC08A1_PollingTagDetectNDEF.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

NFC08A1_PollingTagDetectNDEF.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "NFC08A1_PollingTagDetectNDEF.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) NFC08A1_PollingTagDetectNDEF.elf NFC08A1_PollingTagDetectNDEF.list NFC08A1_PollingTagDetectNDEF.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
