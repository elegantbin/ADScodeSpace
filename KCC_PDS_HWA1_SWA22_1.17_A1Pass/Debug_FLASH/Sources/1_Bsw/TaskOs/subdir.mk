################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Sources/1_Bsw/TaskOs/OsMain.c \
../Sources/1_Bsw/TaskOs/OsScheduler.c \
../Sources/1_Bsw/TaskOs/OsTaskFu.c \
../Sources/1_Bsw/TaskOs/OsTimerTick.c 

OBJS += \
./Sources/1_Bsw/TaskOs/OsMain.o \
./Sources/1_Bsw/TaskOs/OsScheduler.o \
./Sources/1_Bsw/TaskOs/OsTaskFu.o \
./Sources/1_Bsw/TaskOs/OsTimerTick.o 

C_DEPS += \
./Sources/1_Bsw/TaskOs/OsMain.d \
./Sources/1_Bsw/TaskOs/OsScheduler.d \
./Sources/1_Bsw/TaskOs/OsTaskFu.d \
./Sources/1_Bsw/TaskOs/OsTimerTick.d 


# Each subdirectory must supply rules for building sources it contributes
Sources/1_Bsw/TaskOs/%.o: ../Sources/1_Bsw/TaskOs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Sources/1_Bsw/TaskOs/OsMain.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


