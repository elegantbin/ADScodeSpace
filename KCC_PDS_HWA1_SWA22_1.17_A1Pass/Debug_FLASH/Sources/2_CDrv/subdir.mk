################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/2_CDrv/AdcIf.c \
../Sources/2_CDrv/DioIf.c \
../Sources/2_CDrv/FlashIf.c \
../Sources/2_CDrv/SpiIf.c \
../Sources/2_CDrv/UartIf.c 

OBJS += \
./Sources/2_CDrv/AdcIf.o \
./Sources/2_CDrv/DioIf.o \
./Sources/2_CDrv/FlashIf.o \
./Sources/2_CDrv/SpiIf.o \
./Sources/2_CDrv/UartIf.o 

C_DEPS += \
./Sources/2_CDrv/AdcIf.d \
./Sources/2_CDrv/DioIf.d \
./Sources/2_CDrv/FlashIf.d \
./Sources/2_CDrv/SpiIf.d \
./Sources/2_CDrv/UartIf.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/2_CDrv/%.o: ../Sources/2_CDrv/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/2_CDrv/AdcIf.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


