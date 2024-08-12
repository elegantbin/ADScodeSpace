################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System.c \
../0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System_data.c \
../0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetInf.c \
../0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetNaN.c \
../0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rt_nonfinite.c 

COMPILED_SRCS += \
./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System.src \
./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System_data.src \
./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetInf.src \
./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetNaN.src \
./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rt_nonfinite.src 

C_DEPS += \
./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System.d \
./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System_data.d \
./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetInf.d \
./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetNaN.d \
./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rt_nonfinite.d 

OBJS += \
./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System.o \
./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System_data.o \
./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetInf.o \
./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetNaN.o \
./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rt_nonfinite.o 


# Each subdirectory must supply rules for building sources it contributes
0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/%.src: ../0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/%.c 0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc27xd "-fD:/ADSCodeSpace/TC275_HWA1_FOC_b240227-AddSimulinkCode/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/0_Src\/1_SrvSw\/SysSe\/MotorDrive\/Current_Controller\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System.o: ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System.src 0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System_data.o: ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System_data.src 0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetInf.o: ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetInf.src 0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetNaN.o: ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetNaN.src 0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rt_nonfinite.o: ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rt_nonfinite.src 0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-0_Src-2f-1_SrvSw-2f-SysSe-2f-MotorDrive-2f-Current_Controller

clean-0_Src-2f-1_SrvSw-2f-SysSe-2f-MotorDrive-2f-Current_Controller:
	-$(RM) ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System.d ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System.o ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System.src ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System_data.d ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System_data.o ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/PMSM_CurrentControl_System_data.src ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetInf.d ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetInf.o ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetInf.src ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetNaN.d ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetNaN.o ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rtGetNaN.src ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rt_nonfinite.d ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rt_nonfinite.o ./0_Src/1_SrvSw/SysSe/MotorDrive/Current_Controller/rt_nonfinite.src

.PHONY: clean-0_Src-2f-1_SrvSw-2f-SysSe-2f-MotorDrive-2f-Current_Controller

