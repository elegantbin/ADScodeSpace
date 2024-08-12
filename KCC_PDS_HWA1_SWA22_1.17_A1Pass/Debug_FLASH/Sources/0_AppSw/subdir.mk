################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/0_AppSw/DoorSys.c \
../Sources/0_AppSw/DoorSysDef.c \
../Sources/0_AppSw/DoorSys_Assit.c \
../Sources/0_AppSw/DoorSys_Block.c \
../Sources/0_AppSw/DoorSys_EBrake.c \
../Sources/0_AppSw/DoorSys_Pos.c \
../Sources/0_AppSw/DoorSys_Tip2Run.c \
../Sources/0_AppSw/DoorSys_Velocity.c \
../Sources/0_AppSw/DoorSys_VelocityControl.c 

OBJS += \
./Sources/0_AppSw/DoorSys.o \
./Sources/0_AppSw/DoorSysDef.o \
./Sources/0_AppSw/DoorSys_Assit.o \
./Sources/0_AppSw/DoorSys_Block.o \
./Sources/0_AppSw/DoorSys_EBrake.o \
./Sources/0_AppSw/DoorSys_Pos.o \
./Sources/0_AppSw/DoorSys_Tip2Run.o \
./Sources/0_AppSw/DoorSys_Velocity.o \
./Sources/0_AppSw/DoorSys_VelocityControl.o 

C_DEPS += \
./Sources/0_AppSw/DoorSys.d \
./Sources/0_AppSw/DoorSysDef.d \
./Sources/0_AppSw/DoorSys_Assit.d \
./Sources/0_AppSw/DoorSys_Block.d \
./Sources/0_AppSw/DoorSys_EBrake.d \
./Sources/0_AppSw/DoorSys_Pos.d \
./Sources/0_AppSw/DoorSys_Tip2Run.d \
./Sources/0_AppSw/DoorSys_Velocity.d \
./Sources/0_AppSw/DoorSys_VelocityControl.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/0_AppSw/%.o: ../Sources/0_AppSw/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/0_AppSw/DoorSys.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


