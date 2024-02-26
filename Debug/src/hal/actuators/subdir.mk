################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hal/actuators/buzzer.c \
../src/hal/actuators/dc_motor.c \
../src/hal/actuators/keypad.c \
../src/hal/actuators/lcd.c \
../src/hal/actuators/led.c \
../src/hal/actuators/solenoid_lock.c 

OBJS += \
./src/hal/actuators/buzzer.o \
./src/hal/actuators/dc_motor.o \
./src/hal/actuators/keypad.o \
./src/hal/actuators/lcd.o \
./src/hal/actuators/led.o \
./src/hal/actuators/solenoid_lock.o 

C_DEPS += \
./src/hal/actuators/buzzer.d \
./src/hal/actuators/dc_motor.d \
./src/hal/actuators/keypad.d \
./src/hal/actuators/lcd.d \
./src/hal/actuators/led.d \
./src/hal/actuators/solenoid_lock.d 


# Each subdirectory must supply rules for building sources it contributes
src/hal/actuators/%.o: ../src/hal/actuators/%.c src/hal/actuators/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


