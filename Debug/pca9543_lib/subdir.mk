################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../pca9543_lib/pca9543.c 

OBJS += \
./pca9543_lib/pca9543.o 

C_DEPS += \
./pca9543_lib/pca9543.d 


# Each subdirectory must supply rules for building sources it contributes
pca9543_lib/%.o pca9543_lib/%.su: ../pca9543_lib/%.c pca9543_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xC -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../as5600/ -I../pca9543 -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-pca9543_lib

clean-pca9543_lib:
	-$(RM) ./pca9543_lib/pca9543.d ./pca9543_lib/pca9543.o ./pca9543_lib/pca9543.su

.PHONY: clean-pca9543_lib

