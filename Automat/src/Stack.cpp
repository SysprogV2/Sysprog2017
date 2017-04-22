/*
 * Stack.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */
#include <iostream>
#include "../includes/Stack.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include "../../Compatibility/compab.h"

Stack::Stack() {
	stackHead = 0;
	void* tmp;
	int error = posix_memalign(&tmp, 4096, MAX_TOKEN_SIZE);
	if (error != 0) {
	    std::cout << MEM_ALLOC_ERR << std::endl;
	    exit(EXIT_FAILURE);
	}
	stack = (char*) tmp;
}

Stack::~Stack() {
	delete[] stack;
}

void Stack::push(char c) {
	if (stackHead < MAX_TOKEN_SIZE) {
		stack[stackHead++] = c;
	} else {
		std::cout << STACK_OVERFLOW_ERR << std::endl;
		stackHead = 0;
		stack[stackHead] = '\0';
	}
}

void Stack::trim(int back) {
	stackHead -= back;
	stack[stackHead] = '\0';
}

char* Stack::get() {
	stack[stackHead] = '\0';
	return stack;
}

void Stack::flush() {
	stackHead = 0;
	stack[0] = '\0';
}


