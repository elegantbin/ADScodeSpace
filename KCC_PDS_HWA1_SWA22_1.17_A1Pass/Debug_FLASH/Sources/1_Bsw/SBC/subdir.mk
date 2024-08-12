################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/1_Bsw/SBC/SBC_Handler.c \
../Sources/1_Bsw/SBC/TLE926x.c \
../Sources/1_Bsw/SBC/TLE926x_SPI.c 

OBJS += \
./Sources/1_Bsw/SBC/SBC_Handler.o \
./Sources/1_Bsw/SBC/TLE926x.o \
./Sources/1_Bsw/SBC/TLE926x_SPI.o 

C_DEPS += \
./Sources/1_Bsw/SBC/SBC_Handler.d \
./Sources/1_Bsw/SBC/TLE926x.d \
./Sources/1_Bsw/SBC/TLE926x_SPI.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/1_Bsw/SBC/%.o: ../Sources/1_Bsw/SBC/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/1_Bsw/SBC/SBC_Handler.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


