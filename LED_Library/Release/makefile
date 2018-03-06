################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/lib/LEDMatrix/subdir.mk
-include src/lib/FastLED/subdir.mk
-include src/lib/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
LED_Library.lss \

FLASH_IMAGE += \
LED_Library.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: LED_Library.elf secondary-outputs

# Tool invocations
LED_Library.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C++ Linker'
	avr-g++ -Wl,-Map,LED_Library.map,--cref -mrelax -Wl,--gc-sections -Wl,--gc-sections -mrelax -L"C:\MyDocuments\Code\EclipseCPP/corelib" -mmcu=atmega328p -o "LED_Library.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

LED_Library.lss: LED_Library.elf
	@echo 'Invoking: AVR Create Extended Listing'
	avr-objdump -h -S LED_Library.elf  >"LED_Library.lss"
	@echo 'Finished building: $@'
	@echo ' '

LED_Library.hex: LED_Library.elf
	@echo 'Create Flash image (ihex format)'
	avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex LED_Library.elf  "LED_Library.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: LED_Library.elf
	@echo 'Invoking: Print Size'
	avr-size --format=avr --mcu=atmega328p LED_Library.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(C_UPPER_DEPS)$(S_DEPS)$(LSS)$(C_DEPS)$(FLASH_IMAGE)$(CC_DEPS)$(ELFS)$(C++_DEPS)$(OBJS)$(CXX_DEPS)$(ASM_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(CPP_DEPS) LED_Library.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
