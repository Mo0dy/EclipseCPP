################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/lib/FastLED/FastLED.cpp \
../src/lib/FastLED/bitswap.cpp \
../src/lib/FastLED/colorpalettes.cpp \
../src/lib/FastLED/colorutils.cpp \
../src/lib/FastLED/hsv2rgb.cpp \
../src/lib/FastLED/lib8tion.cpp \
../src/lib/FastLED/noise.cpp \
../src/lib/FastLED/power_mgt.cpp \
../src/lib/FastLED/wiring.cpp 

OBJS += \
./src/lib/FastLED/FastLED.o \
./src/lib/FastLED/bitswap.o \
./src/lib/FastLED/colorpalettes.o \
./src/lib/FastLED/colorutils.o \
./src/lib/FastLED/hsv2rgb.o \
./src/lib/FastLED/lib8tion.o \
./src/lib/FastLED/noise.o \
./src/lib/FastLED/power_mgt.o \
./src/lib/FastLED/wiring.o 

CPP_DEPS += \
./src/lib/FastLED/FastLED.d \
./src/lib/FastLED/bitswap.d \
./src/lib/FastLED/colorpalettes.d \
./src/lib/FastLED/colorutils.d \
./src/lib/FastLED/hsv2rgb.d \
./src/lib/FastLED/lib8tion.d \
./src/lib/FastLED/noise.d \
./src/lib/FastLED/power_mgt.d \
./src/lib/FastLED/wiring.d 


# Each subdirectory must supply rules for building sources it contributes
src/lib/FastLED/%.o: ../src/lib/FastLED/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: AVR C++ Compiler'
	avr-g++ -IC:/Arduino/hardware/arduino/avr/variants/standard -IC:/Arduino/hardware/arduino/avr/cores/arduino -I"C:\MyDocuments\Code\EclipseCPP\LED_Library\src" -I"C:\MyDocuments\Code\EclipseCPP\LED_Library\src\lib\FastLED" -I"C:\MyDocuments\Code\EclipseCPP\LED_Library\src\lib\LEDMatrix" -I"C:\Arduino\hardware\arduino\avr\libraries\EEPROM\src" -I"C:\MyDocuments\Code\EclipseCPP\LED_Library\src\lib" -Wall -g3 -gstabs -Os -ffunction-sections -fdata-sections -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -std=c++11 -fno-threadsafe-statics -mmcu=atmega328p -DF_CPU=16000000UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


