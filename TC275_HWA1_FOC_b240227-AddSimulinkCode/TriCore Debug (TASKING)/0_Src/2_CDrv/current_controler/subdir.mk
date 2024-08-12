################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../0_Src/2_CDrv/current_controler/PMSM_CurrentControl_System.c \
../0_Src/2_CDrv/current_controler/PMSM_CurrentControl_System_data.c \
../0_Src/2_CDrv/current_controler/rtGetInf.c \
../0_Src/2_CDrv/current_controler/rtGetNaN.c \
../0_Src/2_CDrv/current_controler/rt_nonfinite.c 

OBJS += \
./0_Src/2_CDrv/current_controler/PMSM_CurrentControl_System.o \
./0_Src/2_CDrv/current_controler/PMSM_CurrentControl_System_data.o \
./0_Src/2_CDrv/current_controler/rtGetInf.o \
./0_Src/2_CDrv/current_controler/rtGetNaN.o \
./0_Src/2_CDrv/current_controler/rt_nonfinite.o 

COMPILED_SRCS += \
./0_Src/2_CDrv/current_controler/PMSM_CurrentControl_System.src \
./0_Src/2_CDrv/current_controler/PMSM_CurrentControl_System_data.src \
./0_Src/2_CDrv/current_controler/rtGetInf.src \
./0_Src/2_CDrv/current_controler/rtGetNaN.src \
./0_Src/2_CDrv/current_controler/rt_nonfinite.src 

C_DEPS += \
./0_Src/2_CDrv/current_controler/PMSM_CurrentControl_System.d \
./0_Src/2_CDrv/current_controler/PMSM_CurrentControl_System_data.d \
./0_Src/2_CDrv/current_controler/rtGetInf.d \
./0_Src/2_CDrv/current_controler/rtGetNaN.d \
./0_Src/2_CDrv/current_controler/rt_nonfinite.d 


# Each subdirectory must supply rules for building sources it contributes
0_Src/2_CDrv/current_controler/%.src: ../0_Src/2_CDrv/current_controler/%.c 0_Src/2_CDrv/current_controler/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc27xd "-fD:/backupFiles-GZ-C-0034/Motor/FOC_TEST/TC275_HWA1_FOC_b240227/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/current_controler/PMSM_CurrentControl_System.o: ./0_Src/2_CDrv/current_controler/PMSM_CurrentControl_System.src 0_Src/2_CDrv/current_controler/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/current_controler/PMSM_CurrentControl_System_data.o: ./0_Src/2_CDrv/current_controler/PMSM_CurrentControl_System_data.src 0_Src/2_CDrv/current_controler/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/current_controler/rtGetInf.o: ./0_Src/2_CDrv/current_controler/rtGetInf.src 0_Src/2_CDrv/current_controler/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/current_controler/rtGetNaN.o: ./0_Src/2_CDrv/current_controler/rtGetNaN.src 0_Src/2_CDrv/current_controler/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/current_controler/rt_nonfinite.o: ./0_Src/2_CDrv/current_controler/rt_nonfinite.src 0_Src/2_CDrv/current_controler/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


