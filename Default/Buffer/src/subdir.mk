################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Buffer/src/Buffer.cpp \
../Buffer/src/TestBuffer.cpp 

OBJS += \
./Buffer/src/Buffer.o \
./Buffer/src/TestBuffer.o 

CPP_DEPS += \
./Buffer/src/Buffer.d \
./Buffer/src/TestBuffer.d 


# Each subdirectory must supply rules for building sources it contributes
Buffer/src/%.o: ../Buffer/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


