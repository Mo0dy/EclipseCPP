################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/example.cpp 

OBJS += \
./src/example.o 

CPP_DEPS += \
./src/example.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -IC:/Arduino/hardware/arduino/avr/variants/standard -IC:/Arduino/hardware/arduino/avr/cores/arduino -I"C:\MyDocuments\Code\EclipseCPP\LED_Library\src" -I"C:\MyDocuments\Code\EclipseCPP\LED_Library\src\lib\FastLED" -I"C:\MyDocuments\Code\EclipseCPP\LED_Library\src\lib\LEDMatrix" -I"C:\Arduino\hardware\arduino\avr\libraries\EEPROM\src" -I"C:\MyDocuments\Code\EclipseCPP\LED_Library\src\lib" -Wall -g3 -gstabs -Os -ffunction-sections -fdata-sections -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -std=c++11 -fno-threadsafe-statics -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


