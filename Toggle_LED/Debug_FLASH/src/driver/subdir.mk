################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/driver/GPIO.c \
../src/driver/Port.c 

OBJS += \
./src/driver/GPIO.o \
./src/driver/Port.o 

C_DEPS += \
./src/driver/GPIO.d \
./src/driver/Port.d 


# Each subdirectory must supply rules for building sources it contributes
src/driver/%.o: ../src/driver/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/driver/GPIO.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


