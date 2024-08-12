################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../0_Src/2_CDrv/MTPA/PMSM_MTPA_Module.c \
../0_Src/2_CDrv/MTPA/PMSM_MTPA_Module_data.c 

OBJS += \
./0_Src/2_CDrv/MTPA/PMSM_MTPA_Module.o \
./0_Src/2_CDrv/MTPA/PMSM_MTPA_Module_data.o 

COMPILED_SRCS += \
./0_Src/2_CDrv/MTPA/PMSM_MTPA_Module.src \
./0_Src/2_CDrv/MTPA/PMSM_MTPA_Module_data.src 

C_DEPS += \
./0_Src/2_CDrv/MTPA/PMSM_MTPA_Module.d \
./0_Src/2_CDrv/MTPA/PMSM_MTPA_Module_data.d 


# Each subdirectory must supply rules for building sources it contributes
0_Src/2_CDrv/MTPA/%.src: ../0_Src/2_CDrv/MTPA/%.c 0_Src/2_CDrv/MTPA/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING C/C++ Compiler'
	cctc -D__CPU__=tc27xd "-fD:/backupFiles-GZ-C-0034/Motor/FOC_TEST/TC275_HWA1_FOC_b240227/TriCore Debug (TASKING)/TASKING_C_C___Compiler-Include_paths.opt" --iso=99 --c++14 --language=+volatile --exceptions --anachronisms --fp-model=3 -O0 --tradeoff=4 --compact-max-size=200 -g -Wc-w544 -Wc-w557 -Ctc27xd -o "$@"  "$<"  -cs --dep-file="$(@:.src=.d)" --misrac-version=2012 -N0 -Z0 -Y0 2>&1;
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/MTPA/PMSM_MTPA_Module.o: ./0_Src/2_CDrv/MTPA/PMSM_MTPA_Module.src 0_Src/2_CDrv/MTPA/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '

0_Src/2_CDrv/MTPA/PMSM_MTPA_Module_data.o: ./0_Src/2_CDrv/MTPA/PMSM_MTPA_Module_data.src 0_Src/2_CDrv/MTPA/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: TASKING Assembler'
	astc -Og -Os --no-warnings= --error-limit=42 -o  "$@" "$<" --list-format=L1 --optimize=gs
	@echo 'Finished building: $<'
	@echo ' '


