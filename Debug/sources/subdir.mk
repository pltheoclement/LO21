################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../sources/Operator.cpp \
../sources/binaryOperator.cpp \
../sources/main.cpp \
../sources/ternaryOperator.cpp \
../sources/unaryOperator.cpp 

OBJS += \
./sources/Operator.o \
./sources/binaryOperator.o \
./sources/main.o \
./sources/ternaryOperator.o \
./sources/unaryOperator.o 

CPP_DEPS += \
./sources/Operator.d \
./sources/binaryOperator.d \
./sources/main.d \
./sources/ternaryOperator.d \
./sources/unaryOperator.d 


# Each subdirectory must supply rules for building sources it contributes
sources/%.o: ../sources/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


