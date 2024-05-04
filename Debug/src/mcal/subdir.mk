################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/mcal/atmega32_eeprom.c \
../src/mcal/atmega32_gpio.c \
../src/mcal/atmega32_interrupt.c \
../src/mcal/atmega32_timer0.c \
../src/mcal/atmega32_timer1.c \
../src/mcal/atmega32_timer2.c \
../src/mcal/atmega32_uart.c 

OBJS += \
./src/mcal/atmega32_eeprom.o \
./src/mcal/atmega32_gpio.o \
./src/mcal/atmega32_interrupt.o \
./src/mcal/atmega32_timer0.o \
./src/mcal/atmega32_timer1.o \
./src/mcal/atmega32_timer2.o \
./src/mcal/atmega32_uart.o 

C_DEPS += \
./src/mcal/atmega32_eeprom.d \
./src/mcal/atmega32_gpio.d \
./src/mcal/atmega32_interrupt.d \
./src/mcal/atmega32_timer0.d \
./src/mcal/atmega32_timer1.d \
./src/mcal/atmega32_timer2.d \
./src/mcal/atmega32_uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/mcal/%.o: ../src/mcal/%.c src/mcal/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


