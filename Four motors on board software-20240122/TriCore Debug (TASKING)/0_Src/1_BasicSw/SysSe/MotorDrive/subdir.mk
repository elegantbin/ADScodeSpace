################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../0_Src/1_BasicSw/SysSe/MotorDrive/Clarke.c \
../0_Src/1_BasicSw/SysSe/MotorDrive/Foc.c \
../0_Src/1_BasicSw/SysSe/MotorDrive/Park.c \
../0_Src/1_BasicSw/SysSe/MotorDrive/Pi.c \
../0_Src/1_BasicSw/SysSe/MotorDrive/SpaceVectorModulation.c \
../0_Src/1_BasicSw/SysSe/MotorDrive/Tables.c \
../0_Src/1_BasicSw/SysSe/MotorDrive/Tables_const.c 

COMPILED_SRCS += \
./0_Src/1_BasicSw/SysSe/MotorDrive/Clarke.src \
./0_Src/1_BasicSw/SysSe/MotorDrive/Foc.src \
./0_Src/1_BasicSw/SysSe/MotorDrive/Park.src \
./0_Src/1_BasicSw/SysSe/MotorDrive/Pi.src \
./0_Src/1_BasicSw/SysSe/MotorDrive/SpaceVectorModulation.src \
./0_Src/1_BasicSw/SysSe/MotorDrive/Tables.src \
./0_Src/1_BasicSw/SysSe/MotorDrive/Tables_const.src 

C_DEPS += \
./0_Src/1_BasicSw/SysSe/MotorDrive/Clarke.d \
./0_Src/1_BasicSw/SysSe/MotorDrive/Foc.d \
./0_Src/1_BasicSw/SysSe/MotorDrive/Park.d \
./0_Src/1_BasicSw/SysSe/MotorDrive/Pi.d \
./0_Src/1_BasicSw/SysSe/MotorDrive/SpaceVectorModulation.d \
./0_Src/1_BasicSw/SysSe/MotorDrive/Tables.d \
./0_Src/1_BasicSw/SysSe/MotorDrive/Tables_const.d 

OBJS += \
./0_Src/1_BasicSw/SysSe/MotorDrive/Clarke.o \
./0_Src/1_BasicSw/SysSe/MotorDrive/Foc.o \
./0_Src/1_BasicSw/SysSe/MotorDrive/Park.o \
./0_Src/1_BasicSw/SysSe/MotorDrive/Pi.o \
./0_Src/1_BasicSw/SysSe/MotorDrive/SpaceVectorModulation.o \
./0_Src/1_BasicSw/SysSe/MotorDrive/Tables.o \
./0_Src/1_BasicSw/SysSe/MotorDrive/Tables_const.o 


# Each subdirectory must supply rules for building sources it contributes
0_Src/1_BasicSw/SysSe/MotorDrive/%.src: ../0_Src/1_BasicSw/SysSe/MotorDrive/%.c 0_Src/1_BasicSw/SysSe/MotorDrive/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -cs --dep-file="$(basename $@).d" --misrac-version=2004 -D__CPU__=tc27xd "-fD:/ADSCodeSpace/Four motors on board software-20240122/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -Y0 -N0 -Z0 -o "$@" "$<" && \
	if [ -f "$(basename $@).d" ]; then sed.exe -r  -e 's/\b(.+\.o)\b/0_Src\/1_BasicSw\/SysSe\/MotorDrive\/\1/g' -e 's/\\/\//g' -e 's/\/\//\//g' -e 's/"//g' -e 's/([a-zA-Z]:\/)/\L\1/g' -e 's/\d32:/@TARGET_DELIMITER@/g; s/\\\d32/@ESCAPED_SPACE@/g; s/\d32/\\\d32/g; s/@ESCAPED_SPACE@/\\\d32/g; s/@TARGET_DELIMITER@/\d32:/g' "$(basename $@).d" > "$(basename $@).d_sed" && cp "$(basename $@).d_sed" "$(basename $@).d" && rm -f "$(basename $@).d_sed" 2>/dev/null; else echo 'No dependency file to process';fi
	@echo 'Finished building: $<'
	@echo ' '

0_Src/1_BasicSw/SysSe/MotorDrive/Clarke.o: ./0_Src/1_BasicSw/SysSe/MotorDrive/Clarke.src 0_Src/1_BasicSw/SysSe/MotorDrive/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/1_BasicSw/SysSe/MotorDrive/Foc.o: ./0_Src/1_BasicSw/SysSe/MotorDrive/Foc.src 0_Src/1_BasicSw/SysSe/MotorDrive/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/1_BasicSw/SysSe/MotorDrive/Park.o: ./0_Src/1_BasicSw/SysSe/MotorDrive/Park.src 0_Src/1_BasicSw/SysSe/MotorDrive/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/1_BasicSw/SysSe/MotorDrive/Pi.o: ./0_Src/1_BasicSw/SysSe/MotorDrive/Pi.src 0_Src/1_BasicSw/SysSe/MotorDrive/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/1_BasicSw/SysSe/MotorDrive/SpaceVectorModulation.o: ./0_Src/1_BasicSw/SysSe/MotorDrive/SpaceVectorModulation.src 0_Src/1_BasicSw/SysSe/MotorDrive/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/1_BasicSw/SysSe/MotorDrive/Tables.o: ./0_Src/1_BasicSw/SysSe/MotorDrive/Tables.src 0_Src/1_BasicSw/SysSe/MotorDrive/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

0_Src/1_BasicSw/SysSe/MotorDrive/Tables_const.o: ./0_Src/1_BasicSw/SysSe/MotorDrive/Tables_const.src 0_Src/1_BasicSw/SysSe/MotorDrive/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean-0_Src-2f-1_BasicSw-2f-SysSe-2f-MotorDrive

clean-0_Src-2f-1_BasicSw-2f-SysSe-2f-MotorDrive:
	-$(RM) ./0_Src/1_BasicSw/SysSe/MotorDrive/Clarke.d ./0_Src/1_BasicSw/SysSe/MotorDrive/Clarke.o ./0_Src/1_BasicSw/SysSe/MotorDrive/Clarke.src ./0_Src/1_BasicSw/SysSe/MotorDrive/Foc.d ./0_Src/1_BasicSw/SysSe/MotorDrive/Foc.o ./0_Src/1_BasicSw/SysSe/MotorDrive/Foc.src ./0_Src/1_BasicSw/SysSe/MotorDrive/Park.d ./0_Src/1_BasicSw/SysSe/MotorDrive/Park.o ./0_Src/1_BasicSw/SysSe/MotorDrive/Park.src ./0_Src/1_BasicSw/SysSe/MotorDrive/Pi.d ./0_Src/1_BasicSw/SysSe/MotorDrive/Pi.o ./0_Src/1_BasicSw/SysSe/MotorDrive/Pi.src ./0_Src/1_BasicSw/SysSe/MotorDrive/SpaceVectorModulation.d ./0_Src/1_BasicSw/SysSe/MotorDrive/SpaceVectorModulation.o ./0_Src/1_BasicSw/SysSe/MotorDrive/SpaceVectorModulation.src ./0_Src/1_BasicSw/SysSe/MotorDrive/Tables.d ./0_Src/1_BasicSw/SysSe/MotorDrive/Tables.o ./0_Src/1_BasicSw/SysSe/MotorDrive/Tables.src ./0_Src/1_BasicSw/SysSe/MotorDrive/Tables_const.d ./0_Src/1_BasicSw/SysSe/MotorDrive/Tables_const.o ./0_Src/1_BasicSw/SysSe/MotorDrive/Tables_const.src

.PHONY: clean-0_Src-2f-1_BasicSw-2f-SysSe-2f-MotorDrive

