################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/rng/yarrow.c 

OBJS += \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/rng/yarrow.o 

C_DEPS += \
./Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/rng/yarrow.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/rng/yarrow.o: ../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/rng/yarrow.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DDEBUG -DSTM32L496xx -c -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -I../Inc -I../Drivers/CMSIS/Include -I../Drivers/CMSIS/Device/ST/STM32L4xx/Include -I../Drivers/STM32L4xx_HAL_Driver/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Drivers/STM32L4xx_HAL_Driver/Inc/Legacy -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_tcp -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/common -I../Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto -I../Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc -I../Middlewares/ST/STM32_USB_Device_Library/Core/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Drivers/CycloneTCP_SSL_Crypto_Open_1_9_6/cyclone_crypto/rng/yarrow.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

