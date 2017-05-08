################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Parser/src/Errors.cpp \
../Parser/src/ParseTree.cpp \
../Parser/src/Parser.cpp \
../Parser/src/TokenSequence.cpp 

OBJS += \
./Parser/src/Errors.o \
./Parser/src/ParseTree.o \
./Parser/src/Parser.o \
./Parser/src/TokenSequence.o 

CPP_DEPS += \
./Parser/src/Errors.d \
./Parser/src/ParseTree.d \
./Parser/src/Parser.d \
./Parser/src/TokenSequence.d 


# Each subdirectory must supply rules for building sources it contributes
Parser/src/%.o: ../Parser/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


