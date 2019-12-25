################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_client.c \
../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_client_misc.c \
../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_server.c \
../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_server_misc.c 

OBJS += \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_client.o \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_client_misc.o \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_server.o \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_server_misc.o 

C_DEPS += \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_client.d \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_client_misc.d \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_server.d \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_server_misc.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_client.o: ../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_client.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L496xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/common -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_client.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_client_misc.o: ../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_client_misc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L496xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/common -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_client_misc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_server.o: ../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_server.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L496xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/common -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_server.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_server_misc.o: ../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_server_misc.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L496xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/common -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp/tftp/tftp_server_misc.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
