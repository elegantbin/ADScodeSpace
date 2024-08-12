################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/0_AppSw/Components/DCU.c \
../Sources/0_AppSw/Components/DualHall.c \
../Sources/0_AppSw/Components/IMU.c \
../Sources/0_AppSw/Components/MotAct.c \
../Sources/0_AppSw/Components/MotAct_Startup.c \
../Sources/0_AppSw/Components/Roll_Pitch_Parameter.c \
../Sources/0_AppSw/Components/Switch.c \
../Sources/0_AppSw/Components/TCU.c 

OBJS += \
./Sources/0_AppSw/Components/DCU.o \
./Sources/0_AppSw/Components/DualHall.o \
./Sources/0_AppSw/Components/IMU.o \
./Sources/0_AppSw/Components/MotAct.o \
./Sources/0_AppSw/Components/MotAct_Startup.o \
./Sources/0_AppSw/Components/Roll_Pitch_Parameter.o \
./Sources/0_AppSw/Components/Switch.o \
./Sources/0_AppSw/Components/TCU.o 

C_DEPS += \
./Sources/0_AppSw/Components/DCU.d \
./Sources/0_AppSw/Components/DualHall.d \
./Sources/0_AppSw/Components/IMU.d \
./Sources/0_AppSw/Components/MotAct.d \
./Sources/0_AppSw/Components/MotAct_Startup.d \
./Sources/0_AppSw/Components/Roll_Pitch_Parameter.d \
./Sources/0_AppSw/Components/Switch.d \
./Sources/0_AppSw/Components/TCU.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/0_AppSw/Components/%.o: ../Sources/0_AppSw/Components/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/0_AppSw/Components/DCU.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


