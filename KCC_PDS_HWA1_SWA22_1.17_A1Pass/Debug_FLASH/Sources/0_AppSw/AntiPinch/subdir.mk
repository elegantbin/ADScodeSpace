################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/0_AppSw/AntiPinch/DoorSys_AntiPinch.c \
../Sources/0_AppSw/AntiPinch/DoorSys_ApAdapt.c \
../Sources/0_AppSw/AntiPinch/DoorSys_ApAdaptCurve.c \
../Sources/0_AppSw/AntiPinch/DoorSys_ApCalSpeed.c \
../Sources/0_AppSw/AntiPinch/DoorSys_ApCheck.c \
../Sources/0_AppSw/AntiPinch/DoorSys_ApLimit.c 

OBJS += \
./Sources/0_AppSw/AntiPinch/DoorSys_AntiPinch.o \
./Sources/0_AppSw/AntiPinch/DoorSys_ApAdapt.o \
./Sources/0_AppSw/AntiPinch/DoorSys_ApAdaptCurve.o \
./Sources/0_AppSw/AntiPinch/DoorSys_ApCalSpeed.o \
./Sources/0_AppSw/AntiPinch/DoorSys_ApCheck.o \
./Sources/0_AppSw/AntiPinch/DoorSys_ApLimit.o 

C_DEPS += \
./Sources/0_AppSw/AntiPinch/DoorSys_AntiPinch.d \
./Sources/0_AppSw/AntiPinch/DoorSys_ApAdapt.d \
./Sources/0_AppSw/AntiPinch/DoorSys_ApAdaptCurve.d \
./Sources/0_AppSw/AntiPinch/DoorSys_ApCalSpeed.d \
./Sources/0_AppSw/AntiPinch/DoorSys_ApCheck.d \
./Sources/0_AppSw/AntiPinch/DoorSys_ApLimit.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/0_AppSw/AntiPinch/%.o: ../Sources/0_AppSw/AntiPinch/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/0_AppSw/AntiPinch/DoorSys_AntiPinch.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


