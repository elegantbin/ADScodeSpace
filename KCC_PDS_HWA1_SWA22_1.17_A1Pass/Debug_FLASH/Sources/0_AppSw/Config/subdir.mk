################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/0_AppSw/Config/DoorSysCfg.c \
../Sources/0_AppSw/Config/DoorSysCfg_Assist.c 

OBJS += \
./Sources/0_AppSw/Config/DoorSysCfg.o \
./Sources/0_AppSw/Config/DoorSysCfg_Assist.o 

C_DEPS += \
./Sources/0_AppSw/Config/DoorSysCfg.d \
./Sources/0_AppSw/Config/DoorSysCfg_Assist.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/0_AppSw/Config/%.o: ../Sources/0_AppSw/Config/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/0_AppSw/Config/DoorSysCfg.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


