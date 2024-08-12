################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../0_Src/0_AppSw/SWC/AppTorqueControl.c \
../0_Src/0_AppSw/SWC/App_VelocityControl.c \
../0_Src/0_AppSw/SWC/App_VelocityEval.c \
../0_Src/0_AppSw/SWC/MotorMgtSwc.c 

COMPILED_SRCS += \
./0_Src/0_AppSw/SWC/AppTorqueControl.src \
./0_Src/0_AppSw/SWC/App_VelocityControl.src \
./0_Src/0_AppSw/SWC/App_VelocityEval.src \
./0_Src/0_AppSw/SWC/MotorMgtSwc.src 

C_DEPS += \
./0_Src/0_AppSw/SWC/AppTorqueControl.d \
./0_Src/0_AppSw/SWC/App_VelocityControl.d \
./0_Src/0_AppSw/SWC/App_VelocityEval.d \
./0_Src/0_AppSw/SWC/MotorMgtSwc.d 

OBJS += \
./0_Src/0_AppSw/SWC/AppTorqueControl.o \
./0_Src/0_AppSw/SWC/App_VelocityControl.o \
./0_Src/0_AppSw/SWC/App_VelocityEval.o \
./0_Src/0_AppSw/SWC/MotorMgtSwc.o 


# Each subdirectory must supply rules for building sources it contributes
0_Src/0_AppSw/SWC/%.src: ../0_Src/0_AppSw/SWC/%.c 0_Src/0_AppSw/SWC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc27xd "-fD:/F-DISK-BACK/WHB_Backup/Motor/FOC_TEST/TC275_HWA1_FOC_b240227/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/0_Src\/0_AppSw\/SWC\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

0_Src/0_AppSw/SWC/AppTorqueControl.o: ./0_Src/0_AppSw/SWC/AppTorqueControl.src 0_Src/0_AppSw/SWC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/0_AppSw/SWC/App_VelocityControl.o: ./0_Src/0_AppSw/SWC/App_VelocityControl.src 0_Src/0_AppSw/SWC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/0_AppSw/SWC/App_VelocityEval.o: ./0_Src/0_AppSw/SWC/App_VelocityEval.src 0_Src/0_AppSw/SWC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/0_AppSw/SWC/MotorMgtSwc.o: ./0_Src/0_AppSw/SWC/MotorMgtSwc.src 0_Src/0_AppSw/SWC/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-0_Src-2f-0_AppSw-2f-SWC

clean-0_Src-2f-0_AppSw-2f-SWC:
	-$(RM) ./0_Src/0_AppSw/SWC/AppTorqueControl.d ./0_Src/0_AppSw/SWC/AppTorqueControl.o ./0_Src/0_AppSw/SWC/AppTorqueControl.src ./0_Src/0_AppSw/SWC/App_VelocityControl.d ./0_Src/0_AppSw/SWC/App_VelocityControl.o ./0_Src/0_AppSw/SWC/App_VelocityControl.src ./0_Src/0_AppSw/SWC/App_VelocityEval.d ./0_Src/0_AppSw/SWC/App_VelocityEval.o ./0_Src/0_AppSw/SWC/App_VelocityEval.src ./0_Src/0_AppSw/SWC/MotorMgtSwc.d ./0_Src/0_AppSw/SWC/MotorMgtSwc.o ./0_Src/0_AppSw/SWC/MotorMgtSwc.src

.PHONY: clean-0_Src-2f-0_AppSw-2f-SWC

