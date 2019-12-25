################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client.c \
../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_message.c \
../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_misc.c \
../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_transport.c \
../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_debug.c \
../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_message.c 

OBJS += \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client.o \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_message.o \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_misc.o \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_transport.o \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_debug.o \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_message.o 

C_DEPS += \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client.d \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_message.d \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_misc.d \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_transport.d \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_debug.d \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_message.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client.o: ../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L496xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/common -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_message.o: ../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_message.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L496xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/common -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_message.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_misc.o: ../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_misc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L496xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/common -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_misc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_transport.o: ../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_transport.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L496xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/common -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_client_transport.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_debug.o: ../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_debug.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L496xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/common -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_debug.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_message.o: ../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_message.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L496xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/common -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/mqtt_sn/mqtt_sn_message.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

