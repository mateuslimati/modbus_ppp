################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/asn1.c \
../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/base64.c \
../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/base64url.c \
../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/oid.c \
../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/radix64.c 

OBJS += \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/asn1.o \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/base64.o \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/base64url.o \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/oid.o \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/radix64.o 

C_DEPS += \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/asn1.d \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/base64.d \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/base64url.d \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/oid.d \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/radix64.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/asn1.o: ../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/asn1.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L496xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/common -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/asn1.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/base64.o: ../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/base64.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L496xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/common -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/base64.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/base64url.o: ../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/base64url.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L496xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/common -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/base64url.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/oid.o: ../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/oid.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L496xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/common -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/oid.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/radix64.o: ../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/radix64.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L496xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Middlewares/ST/STM32_USB_Host_Library/Class/AUDIO/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/ST/STM32_USB_Host_Library/Core/Inc -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/common -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/encoding/radix64.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

