################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../0_Src/2_CDrv/BspTime.c \
../0_Src/2_CDrv/GPT12_Encoder.c \
../0_Src/2_CDrv/GTM_TOM_3_Phase_Inverter_PWM.c \
../0_Src/2_CDrv/MULTICAN_CanfdMsg.c \
../0_Src/2_CDrv/MULTICAN_DebugCanMsg.c \
../0_Src/2_CDrv/MULTICAN_FD.c \
../0_Src/2_CDrv/MultiLED.c \
../0_Src/2_CDrv/SPI_ENCODER.c \
../0_Src/2_CDrv/Torque_Calibration.c \
../0_Src/2_CDrv/Vadc_LowPassPT1.c \
../0_Src/2_CDrv/Vadc_VIT.c 

COMPILED_SRCS += \
./0_Src/2_CDrv/BspTime.src \
./0_Src/2_CDrv/GPT12_Encoder.src \
./0_Src/2_CDrv/GTM_TOM_3_Phase_Inverter_PWM.src \
./0_Src/2_CDrv/MULTICAN_CanfdMsg.src \
./0_Src/2_CDrv/MULTICAN_DebugCanMsg.src \
./0_Src/2_CDrv/MULTICAN_FD.src \
./0_Src/2_CDrv/MultiLED.src \
./0_Src/2_CDrv/SPI_ENCODER.src \
./0_Src/2_CDrv/Torque_Calibration.src \
./0_Src/2_CDrv/Vadc_LowPassPT1.src \
./0_Src/2_CDrv/Vadc_VIT.src 

C_DEPS += \
./0_Src/2_CDrv/BspTime.d \
./0_Src/2_CDrv/GPT12_Encoder.d \
./0_Src/2_CDrv/GTM_TOM_3_Phase_Inverter_PWM.d \
./0_Src/2_CDrv/MULTICAN_CanfdMsg.d \
./0_Src/2_CDrv/MULTICAN_DebugCanMsg.d \
./0_Src/2_CDrv/MULTICAN_FD.d \
./0_Src/2_CDrv/MultiLED.d \
./0_Src/2_CDrv/SPI_ENCODER.d \
./0_Src/2_CDrv/Torque_Calibration.d \
./0_Src/2_CDrv/Vadc_LowPassPT1.d \
./0_Src/2_CDrv/Vadc_VIT.d 

OBJS += \
./0_Src/2_CDrv/BspTime.o \
./0_Src/2_CDrv/GPT12_Encoder.o \
./0_Src/2_CDrv/GTM_TOM_3_Phase_Inverter_PWM.o \
./0_Src/2_CDrv/MULTICAN_CanfdMsg.o \
./0_Src/2_CDrv/MULTICAN_DebugCanMsg.o \
./0_Src/2_CDrv/MULTICAN_FD.o \
./0_Src/2_CDrv/MultiLED.o \
./0_Src/2_CDrv/SPI_ENCODER.o \
./0_Src/2_CDrv/Torque_Calibration.o \
./0_Src/2_CDrv/Vadc_LowPassPT1.o \
./0_Src/2_CDrv/Vadc_VIT.o 


# Each subdirectory must supply rules for building sources it contributes
0_Src/2_CDrv/%.src: ../0_Src/2_CDrv/%.c 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc27xd "-fD:/ADSCodeSpace/TC275_HWA1_FOC_b240227-AddSimulinkCode/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/0_Src\/2_CDrv\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/BspTime.o: ./0_Src/2_CDrv/BspTime.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/GPT12_Encoder.o: ./0_Src/2_CDrv/GPT12_Encoder.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/GTM_TOM_3_Phase_Inverter_PWM.o: ./0_Src/2_CDrv/GTM_TOM_3_Phase_Inverter_PWM.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/MULTICAN_CanfdMsg.o: ./0_Src/2_CDrv/MULTICAN_CanfdMsg.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/MULTICAN_DebugCanMsg.o: ./0_Src/2_CDrv/MULTICAN_DebugCanMsg.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/MULTICAN_FD.o: ./0_Src/2_CDrv/MULTICAN_FD.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/MultiLED.o: ./0_Src/2_CDrv/MultiLED.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/SPI_ENCODER.o: ./0_Src/2_CDrv/SPI_ENCODER.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/Torque_Calibration.o: ./0_Src/2_CDrv/Torque_Calibration.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/Vadc_LowPassPT1.o: ./0_Src/2_CDrv/Vadc_LowPassPT1.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/Vadc_VIT.o: ./0_Src/2_CDrv/Vadc_VIT.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-0_Src-2f-2_CDrv

clean-0_Src-2f-2_CDrv:
	-$(RM) ./0_Src/2_CDrv/BspTime.d ./0_Src/2_CDrv/BspTime.o ./0_Src/2_CDrv/BspTime.src ./0_Src/2_CDrv/GPT12_Encoder.d ./0_Src/2_CDrv/GPT12_Encoder.o ./0_Src/2_CDrv/GPT12_Encoder.src ./0_Src/2_CDrv/GTM_TOM_3_Phase_Inverter_PWM.d ./0_Src/2_CDrv/GTM_TOM_3_Phase_Inverter_PWM.o ./0_Src/2_CDrv/GTM_TOM_3_Phase_Inverter_PWM.src ./0_Src/2_CDrv/MULTICAN_CanfdMsg.d ./0_Src/2_CDrv/MULTICAN_CanfdMsg.o ./0_Src/2_CDrv/MULTICAN_CanfdMsg.src ./0_Src/2_CDrv/MULTICAN_DebugCanMsg.d ./0_Src/2_CDrv/MULTICAN_DebugCanMsg.o ./0_Src/2_CDrv/MULTICAN_DebugCanMsg.src ./0_Src/2_CDrv/MULTICAN_FD.d ./0_Src/2_CDrv/MULTICAN_FD.o ./0_Src/2_CDrv/MULTICAN_FD.src ./0_Src/2_CDrv/MultiLED.d ./0_Src/2_CDrv/MultiLED.o ./0_Src/2_CDrv/MultiLED.src ./0_Src/2_CDrv/SPI_ENCODER.d ./0_Src/2_CDrv/SPI_ENCODER.o ./0_Src/2_CDrv/SPI_ENCODER.src ./0_Src/2_CDrv/Torque_Calibration.d ./0_Src/2_CDrv/Torque_Calibration.o ./0_Src/2_CDrv/Torque_Calibration.src ./0_Src/2_CDrv/Vadc_LowPassPT1.d ./0_Src/2_CDrv/Vadc_LowPassPT1.o ./0_Src/2_CDrv/Vadc_LowPassPT1.src ./0_Src/2_CDrv/Vadc_VIT.d ./0_Src/2_CDrv/Vadc_VIT.o ./0_Src/2_CDrv/Vadc_VIT.src

.PHONY: clean-0_Src-2f-2_CDrv

