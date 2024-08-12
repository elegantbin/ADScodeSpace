################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/1_Bsw/Com/Config/CanIfCfg_Msg.c 

OBJS += \
./Sources/1_Bsw/Com/Config/CanIfCfg_Msg.o 

C_DEPS += \
./Sources/1_Bsw/Com/Config/CanIfCfg_Msg.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/1_Bsw/Com/Config/%.o: ../Sources/1_Bsw/Com/Config/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/1_Bsw/Com/Config/CanIfCfg_Msg.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


