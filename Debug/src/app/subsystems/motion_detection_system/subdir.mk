################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/app/subsystems/motion_detection_system/motion_detection_system.c 

OBJS += \
./src/app/subsystems/motion_detection_system/motion_detection_system.o 

C_DEPS += \
./src/app/subsystems/motion_detection_system/motion_detection_system.d 


# Each subdirectory must supply rules for building sources it contributes
src/app/subsystems/motion_detection_system/%.o: ../src/app/subsystems/motion_detection_system/%.c src/app/subsystems/motion_detection_system/subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -g2 -gstabs -O0 -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=8000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


