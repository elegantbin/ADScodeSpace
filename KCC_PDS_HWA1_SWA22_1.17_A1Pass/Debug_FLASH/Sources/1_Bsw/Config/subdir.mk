################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/1_Bsw/Config/OsCfg_Scheduler.c 

OBJS += \
./Sources/1_Bsw/Config/OsCfg_Scheduler.o 

C_DEPS += \
./Sources/1_Bsw/Config/OsCfg_Scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/1_Bsw/Config/%.o: ../Sources/1_Bsw/Config/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/1_Bsw/Config/OsCfg_Scheduler.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


