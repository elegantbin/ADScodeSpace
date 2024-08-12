################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/1_Bsw/Components/Current.c 

OBJS += \
./Sources/1_Bsw/Components/Current.o 

C_DEPS += \
./Sources/1_Bsw/Components/Current.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/1_Bsw/Components/%.o: ../Sources/1_Bsw/Components/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/1_Bsw/Components/Current.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


