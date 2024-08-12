################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../0_Src/2_CDrv/ADC.c \
../0_Src/2_CDrv/AppVadc.c \
../0_Src/2_CDrv/BackgroundADC.c \
../0_Src/2_CDrv/BspTime.c \
../0_Src/2_CDrv/CommutaionCtontrol.c \
../0_Src/2_CDrv/CurrentADC.c \
../0_Src/2_CDrv/CurrentPI.c \
../0_Src/2_CDrv/DIPorts.c \
../0_Src/2_CDrv/EncoderGpt12.c \
../0_Src/2_CDrv/FuzzyPID.c \
../0_Src/2_CDrv/GTM_ATOM_PWM_6Step.c \
../0_Src/2_CDrv/MULTICAN.c \
../0_Src/2_CDrv/MULTICAN_FD.c \
../0_Src/2_CDrv/PositionControl.c \
../0_Src/2_CDrv/SPI_ENCODER.c \
../0_Src/2_CDrv/TempDetect.c \
../0_Src/2_CDrv/TorqueControl.c \
../0_Src/2_CDrv/VelocityPI.c 

COMPILED_SRCS += \
./0_Src/2_CDrv/ADC.src \
./0_Src/2_CDrv/AppVadc.src \
./0_Src/2_CDrv/BackgroundADC.src \
./0_Src/2_CDrv/BspTime.src \
./0_Src/2_CDrv/CommutaionCtontrol.src \
./0_Src/2_CDrv/CurrentADC.src \
./0_Src/2_CDrv/CurrentPI.src \
./0_Src/2_CDrv/DIPorts.src \
./0_Src/2_CDrv/EncoderGpt12.src \
./0_Src/2_CDrv/FuzzyPID.src \
./0_Src/2_CDrv/GTM_ATOM_PWM_6Step.src \
./0_Src/2_CDrv/MULTICAN.src \
./0_Src/2_CDrv/MULTICAN_FD.src \
./0_Src/2_CDrv/PositionControl.src \
./0_Src/2_CDrv/SPI_ENCODER.src \
./0_Src/2_CDrv/TempDetect.src \
./0_Src/2_CDrv/TorqueControl.src \
./0_Src/2_CDrv/VelocityPI.src 

C_DEPS += \
./0_Src/2_CDrv/ADC.d \
./0_Src/2_CDrv/AppVadc.d \
./0_Src/2_CDrv/BackgroundADC.d \
./0_Src/2_CDrv/BspTime.d \
./0_Src/2_CDrv/CommutaionCtontrol.d \
./0_Src/2_CDrv/CurrentADC.d \
./0_Src/2_CDrv/CurrentPI.d \
./0_Src/2_CDrv/DIPorts.d \
./0_Src/2_CDrv/EncoderGpt12.d \
./0_Src/2_CDrv/FuzzyPID.d \
./0_Src/2_CDrv/GTM_ATOM_PWM_6Step.d \
./0_Src/2_CDrv/MULTICAN.d \
./0_Src/2_CDrv/MULTICAN_FD.d \
./0_Src/2_CDrv/PositionControl.d \
./0_Src/2_CDrv/SPI_ENCODER.d \
./0_Src/2_CDrv/TempDetect.d \
./0_Src/2_CDrv/TorqueControl.d \
./0_Src/2_CDrv/VelocityPI.d 

OBJS += \
./0_Src/2_CDrv/ADC.o \
./0_Src/2_CDrv/AppVadc.o \
./0_Src/2_CDrv/BackgroundADC.o \
./0_Src/2_CDrv/BspTime.o \
./0_Src/2_CDrv/CommutaionCtontrol.o \
./0_Src/2_CDrv/CurrentADC.o \
./0_Src/2_CDrv/CurrentPI.o \
./0_Src/2_CDrv/DIPorts.o \
./0_Src/2_CDrv/EncoderGpt12.o \
./0_Src/2_CDrv/FuzzyPID.o \
./0_Src/2_CDrv/GTM_ATOM_PWM_6Step.o \
./0_Src/2_CDrv/MULTICAN.o \
./0_Src/2_CDrv/MULTICAN_FD.o \
./0_Src/2_CDrv/PositionControl.o \
./0_Src/2_CDrv/SPI_ENCODER.o \
./0_Src/2_CDrv/TempDetect.o \
./0_Src/2_CDrv/TorqueControl.o \
./0_Src/2_CDrv/VelocityPI.o 


# Each subdirectory must supply rules for building sources it contributes
0_Src/2_CDrv/%.src: ../0_Src/2_CDrv/%.c 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc27xd "-fD:/ADSCodeSpace/Four motors on board software-20240122/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/0_Src\/2_CDrv\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/ADC.o: ./0_Src/2_CDrv/ADC.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/AppVadc.o: ./0_Src/2_CDrv/AppVadc.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/BackgroundADC.o: ./0_Src/2_CDrv/BackgroundADC.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/BspTime.o: ./0_Src/2_CDrv/BspTime.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/CommutaionCtontrol.o: ./0_Src/2_CDrv/CommutaionCtontrol.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/CurrentADC.o: ./0_Src/2_CDrv/CurrentADC.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/CurrentPI.o: ./0_Src/2_CDrv/CurrentPI.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/DIPorts.o: ./0_Src/2_CDrv/DIPorts.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/EncoderGpt12.o: ./0_Src/2_CDrv/EncoderGpt12.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/FuzzyPID.o: ./0_Src/2_CDrv/FuzzyPID.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/GTM_ATOM_PWM_6Step.o: ./0_Src/2_CDrv/GTM_ATOM_PWM_6Step.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/MULTICAN.o: ./0_Src/2_CDrv/MULTICAN.src 0_Src/2_CDrv/subdir.mk
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

0_Src/2_CDrv/PositionControl.o: ./0_Src/2_CDrv/PositionControl.src 0_Src/2_CDrv/subdir.mk
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

0_Src/2_CDrv/TempDetect.o: ./0_Src/2_CDrv/TempDetect.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/TorqueControl.o: ./0_Src/2_CDrv/TorqueControl.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/VelocityPI.o: ./0_Src/2_CDrv/VelocityPI.src 0_Src/2_CDrv/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-0_Src-2f-2_CDrv

clean-0_Src-2f-2_CDrv:
	-$(RM) ./0_Src/2_CDrv/ADC.d ./0_Src/2_CDrv/ADC.o ./0_Src/2_CDrv/ADC.src ./0_Src/2_CDrv/AppVadc.d ./0_Src/2_CDrv/AppVadc.o ./0_Src/2_CDrv/AppVadc.src ./0_Src/2_CDrv/BackgroundADC.d ./0_Src/2_CDrv/BackgroundADC.o ./0_Src/2_CDrv/BackgroundADC.src ./0_Src/2_CDrv/BspTime.d ./0_Src/2_CDrv/BspTime.o ./0_Src/2_CDrv/BspTime.src ./0_Src/2_CDrv/CommutaionCtontrol.d ./0_Src/2_CDrv/CommutaionCtontrol.o ./0_Src/2_CDrv/CommutaionCtontrol.src ./0_Src/2_CDrv/CurrentADC.d ./0_Src/2_CDrv/CurrentADC.o ./0_Src/2_CDrv/CurrentADC.src ./0_Src/2_CDrv/CurrentPI.d ./0_Src/2_CDrv/CurrentPI.o ./0_Src/2_CDrv/CurrentPI.src ./0_Src/2_CDrv/DIPorts.d ./0_Src/2_CDrv/DIPorts.o ./0_Src/2_CDrv/DIPorts.src ./0_Src/2_CDrv/EncoderGpt12.d ./0_Src/2_CDrv/EncoderGpt12.o ./0_Src/2_CDrv/EncoderGpt12.src ./0_Src/2_CDrv/FuzzyPID.d ./0_Src/2_CDrv/FuzzyPID.o ./0_Src/2_CDrv/FuzzyPID.src ./0_Src/2_CDrv/GTM_ATOM_PWM_6Step.d ./0_Src/2_CDrv/GTM_ATOM_PWM_6Step.o ./0_Src/2_CDrv/GTM_ATOM_PWM_6Step.src ./0_Src/2_CDrv/MULTICAN.d ./0_Src/2_CDrv/MULTICAN.o ./0_Src/2_CDrv/MULTICAN.src ./0_Src/2_CDrv/MULTICAN_FD.d ./0_Src/2_CDrv/MULTICAN_FD.o ./0_Src/2_CDrv/MULTICAN_FD.src ./0_Src/2_CDrv/PositionControl.d ./0_Src/2_CDrv/PositionControl.o ./0_Src/2_CDrv/PositionControl.src ./0_Src/2_CDrv/SPI_ENCODER.d ./0_Src/2_CDrv/SPI_ENCODER.o ./0_Src/2_CDrv/SPI_ENCODER.src ./0_Src/2_CDrv/TempDetect.d ./0_Src/2_CDrv/TempDetect.o ./0_Src/2_CDrv/TempDetect.src ./0_Src/2_CDrv/TorqueControl.d ./0_Src/2_CDrv/TorqueControl.o ./0_Src/2_CDrv/TorqueControl.src ./0_Src/2_CDrv/VelocityPI.d ./0_Src/2_CDrv/VelocityPI.o ./0_Src/2_CDrv/VelocityPI.src

.PHONY: clean-0_Src-2f-2_CDrv

