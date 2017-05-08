################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Symboltable/src/StringTab.cpp \
../Symboltable/src/Symboltable.cpp \
../Symboltable/src/SymtabEntry.cpp \
../Symboltable/src/TestStringTab.cpp \
../Symboltable/src/TestSymboltable.cpp 

OBJS += \
./Symboltable/src/StringTab.o \
./Symboltable/src/Symboltable.o \
./Symboltable/src/SymtabEntry.o \
./Symboltable/src/TestStringTab.o \
./Symboltable/src/TestSymboltable.o 

CPP_DEPS += \
./Symboltable/src/StringTab.d \
./Symboltable/src/Symboltable.d \
./Symboltable/src/SymtabEntry.d \
./Symboltable/src/TestStringTab.d \
./Symboltable/src/TestSymboltable.d 


# Each subdirectory must supply rules for building sources it contributes
Symboltable/src/%.o: ../Symboltable/src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


