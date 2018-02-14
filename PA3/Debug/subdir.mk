################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../filefunctions.c \
../main.c \
../stringfunctions.c \
../tree.c 

OBJS += \
./filefunctions.o \
./main.o \
./stringfunctions.o \
./tree.o 

C_DEPS += \
./filefunctions.d \
./main.d \
./stringfunctions.d \
./tree.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


