################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Automat/src/Automat.cpp \
../Automat/src/Stack.cpp \
../Automat/src/Syntax.cpp \
../Automat/src/TestAutomat.cpp 

OBJS += \
./Automat/src/Automat.o \
./Automat/src/Stack.o \
./Automat/src/Syntax.o \
./Automat/src/TestAutomat.o 

CPP_DEPS += \
./Automat/src/Automat.d \
./Automat/src/Stack.d \
./Automat/src/Syntax.d \
./Automat/src/TestAutomat.d 


# Each subdirectory must supply rules for building sources it contributes
Automat/src/%.o: ../Automat/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


