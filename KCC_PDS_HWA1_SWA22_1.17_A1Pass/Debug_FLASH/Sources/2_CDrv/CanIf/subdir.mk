################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/2_CDrv/CanIf/CanIf.c \
../Sources/2_CDrv/CanIf/CanIf_DebugMsg.c \
../Sources/2_CDrv/CanIf/CanIf_Msg.c 

OBJS += \
./Sources/2_CDrv/CanIf/CanIf.o \
./Sources/2_CDrv/CanIf/CanIf_DebugMsg.o \
./Sources/2_CDrv/CanIf/CanIf_Msg.o 

C_DEPS += \
./Sources/2_CDrv/CanIf/CanIf.d \
./Sources/2_CDrv/CanIf/CanIf_DebugMsg.d \
./Sources/2_CDrv/CanIf/CanIf_Msg.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/2_CDrv/CanIf/%.o: ../Sources/2_CDrv/CanIf/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/2_CDrv/CanIf/CanIf.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


