################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/1_Bsw/Serivce/Pi.c 

OBJS += \
./Sources/1_Bsw/Serivce/Pi.o 

C_DEPS += \
./Sources/1_Bsw/Serivce/Pi.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/1_Bsw/Serivce/%.o: ../Sources/1_Bsw/Serivce/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/1_Bsw/Serivce/Pi.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


