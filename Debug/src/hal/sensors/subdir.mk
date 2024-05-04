################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hal/sensors/flame_sensor.c \
../src/hal/sensors/mq9_sensor.c \
../src/hal/sensors/pir_sensor.c \
../src/hal/sensors/water_sensor.c 

OBJS += \
./src/hal/sensors/flame_sensor.o \
./src/hal/sensors/mq9_sensor.o \
./src/hal/sensors/pir_sensor.o \
./src/hal/sensors/water_sensor.o 

C_DEPS += \
./src/hal/sensors/flame_sensor.d \
./src/hal/sensors/mq9_sensor.d \
./src/hal/sensors/pir_sensor.d \
./src/hal/sensors/water_sensor.d 


# Each subdirectory must supply rules for building sources it contributes
src/hal/sensors/%.o: ../src/hal/sensors/%.c src/hal/sensors/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


