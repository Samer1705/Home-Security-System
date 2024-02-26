################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/app/subsystems/water_flood_system/water_flood_system.c 

OBJS += \
./src/app/subsystems/water_flood_system/water_flood_system.o 

C_DEPS += \
./src/app/subsystems/water_flood_system/water_flood_system.d 


# Each subdirectory must supply rules for building sources it contributes
src/app/subsystems/water_flood_system/%.o: ../src/app/subsystems/water_flood_system/%.c src/app/subsystems/water_flood_system/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


