################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Generated_Code/CAN0can_pal1.c \
../Generated_Code/Cpu.c \
../Generated_Code/DriveMadConv1.c \
../Generated_Code/Flash1.c \
../Generated_Code/SPI0spi1.c \
../Generated_Code/clockMan1.c \
../Generated_Code/dmaController1.c \
../Generated_Code/flexTimer_ic1.c \
../Generated_Code/flexTimer_ic2.c \
../Generated_Code/flexTimer_mc1.c \
../Generated_Code/lpit1.c \
../Generated_Code/lpuart1.c \
../Generated_Code/pin_mux.c \
../Generated_Code/pwm_pal1.c 

OBJS += \
./Generated_Code/CAN0can_pal1.o \
./Generated_Code/Cpu.o \
./Generated_Code/DriveMadConv1.o \
./Generated_Code/Flash1.o \
./Generated_Code/SPI0spi1.o \
./Generated_Code/clockMan1.o \
./Generated_Code/dmaController1.o \
./Generated_Code/flexTimer_ic1.o \
./Generated_Code/flexTimer_ic2.o \
./Generated_Code/flexTimer_mc1.o \
./Generated_Code/lpit1.o \
./Generated_Code/lpuart1.o \
./Generated_Code/pin_mux.o \
./Generated_Code/pwm_pal1.o 

C_DEPS += \
./Generated_Code/CAN0can_pal1.d \
./Generated_Code/Cpu.d \
./Generated_Code/DriveMadConv1.d \
./Generated_Code/Flash1.d \
./Generated_Code/SPI0spi1.d \
./Generated_Code/clockMan1.d \
./Generated_Code/dmaController1.d \
./Generated_Code/flexTimer_ic1.d \
./Generated_Code/flexTimer_ic2.d \
./Generated_Code/flexTimer_mc1.d \
./Generated_Code/lpit1.d \
./Generated_Code/lpuart1.d \
./Generated_Code/pin_mux.d \
./Generated_Code/pwm_pal1.d 


# Each subdirectory must supply rules for building sources it contributes
Generated_Code/%.o: ../Generated_Code/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@Generated_Code/CAN0can_pal1.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


