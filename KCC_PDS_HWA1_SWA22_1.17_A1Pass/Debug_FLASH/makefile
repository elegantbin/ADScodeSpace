################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Sources/2_CDrv/CanIf/subdir.mk
-include Sources/2_CDrv/subdir.mk
-include Sources/1_Bsw/TaskOs/subdir.mk
-include Sources/1_Bsw/Serivce/subdir.mk
-include Sources/1_Bsw/SBC/subdir.mk
-include Sources/1_Bsw/Config/subdir.mk
-include Sources/1_Bsw/Components/subdir.mk
-include Sources/1_Bsw/Com/Config/subdir.mk
-include Sources/1_Bsw/Com/CanMsgHandler/subdir.mk
-include Sources/0_AppSw/Config/subdir.mk
-include Sources/0_AppSw/Components/subdir.mk
-include Sources/0_AppSw/AntiPinch/subdir.mk
-include Sources/0_AppSw/subdir.mk
-include Sources/subdir.mk
-include SDK/rtos/osif/subdir.mk
-include SDK/platform/pal/src/spi/subdir.mk
-include SDK/platform/pal/src/pwm/subdir.mk
-include SDK/platform/pal/src/can/subdir.mk
-include SDK/platform/drivers/src/pins/subdir.mk
-include SDK/platform/drivers/src/lpuart/subdir.mk
-include SDK/platform/drivers/src/lpspi/subdir.mk
-include SDK/platform/drivers/src/lpit/subdir.mk
-include SDK/platform/drivers/src/interrupt/subdir.mk
-include SDK/platform/drivers/src/ftm/subdir.mk
-include SDK/platform/drivers/src/flexcan/subdir.mk
-include SDK/platform/drivers/src/flash/subdir.mk
-include SDK/platform/drivers/src/edma/subdir.mk
-include SDK/platform/drivers/src/clock/S32K1xx/subdir.mk
-include SDK/platform/drivers/src/adc/subdir.mk
-include SDK/platform/devices/S32K142/startup/subdir.mk
-include SDK/platform/devices/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Generated_Code/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
KCC_PDS_HWA1_SWA22_1.17_A1Pass.hex \

SECONDARY_SIZE += \
KCC_PDS_HWA1_SWA22_1.17_A1Pass.siz \


# All Target
all: KCC_PDS_HWA1_SWA22_1.17_A1Pass.elf secondary-outputs

# Tool invocations
KCC_PDS_HWA1_SWA22_1.17_A1Pass.elf: $(OBJS) D:/backupFiles-GZ-C-0034/KYD/NXP_SPACE/KCC_PDS_HWA1_SWA22_1.17_A1Pass/Project_Settings/Linker_Files/S32K142_32_flash.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "KCC_PDS_HWA1_SWA22_1.17_A1Pass.elf" "@KCC_PDS_HWA1_SWA22_1.args"  $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

KCC_PDS_HWA1_SWA22_1.17_A1Pass.hex: KCC_PDS_HWA1_SWA22_1.17_A1Pass.elf
	@echo 'Invoking: Standard S32DS Create Flash Image'
	arm-none-eabi-objcopy -O ihex KCC_PDS_HWA1_SWA22_1.17_A1Pass.elf  "KCC_PDS_HWA1_SWA22_1.17_A1Pass.hex"
	@echo 'Finished building: $@'
	@echo ' '

KCC_PDS_HWA1_SWA22_1.17_A1Pass.siz: KCC_PDS_HWA1_SWA22_1.17_A1Pass.elf
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley KCC_PDS_HWA1_SWA22_1.17_A1Pass.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
