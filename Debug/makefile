################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Startup/subdir.mk
-include Src/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
-include Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
-include Drivers/STM32L4xx_HAL_Driver/Src/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/web_socket/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/sntp/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/snmp/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/smtp/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/ppp/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/netbios/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/modbus/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mibs/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mdns/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/llmnr/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/ipv6/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/ipv4/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/icecast/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/http/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/drivers/switch/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/drivers/phy/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/drivers/loopback/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/dns_sd/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/dns/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/dhcpv6/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/dhcp/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/core/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/coap/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_ssl/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/xof/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/rng/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/pkix/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/pkc/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/mpi/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/mac/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/kdf/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/hash/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/ecc/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/cipher_mode/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/cipher/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/aead/subdir.mk
-include Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/common/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
modbus_ppp.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
modbus_ppp.list \


# All Target
all: modbus_ppp.elf secondary-outputs

# Tool invocations
modbus_ppp.elf: $(OBJS) $(USER_OBJS) /home/mateus/STM32CubeIDE/workspace_1.0.2/modbus_ppp/STM32L496ZGTXP_FLASH.ld
	arm-none-eabi-gcc -o "modbus_ppp.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"/home/mateus/STM32CubeIDE/workspace_1.0.2/modbus_ppp/STM32L496ZGTXP_FLASH.ld" --specs=nosys.specs -Wl,-Map="modbus_ppp.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

modbus_ppp.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "modbus_ppp.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
