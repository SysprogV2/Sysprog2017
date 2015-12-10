/*
 * Stack.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */
#include <iostream>
#include "../includes/Stack.h"
#include <iostream>
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h> //

Stack::Stack() {
	stackHead = 0;
	/*void* tmp;
	int error = posix_memalign(&tmp, 4096, MAX_TOKEN_SIZE);
	if (error != 0) {
	    std::cout << "Couldn't allocate memory. Exiting..." << std::endl;
	    exit(EXIT_FAILURE);
	}
	stack = (char*) tmp;*/
	stack = new char[MAX_TOKEN_SIZE];
}

Stack::~Stack() {
	delete[] stack;
}

void Stack::push(char c) {
	stack[stackHead++] = c;
	stack[stackHead] = '\0';
}

void Stack::trim(int back) {
	//std::cout << "StackHead: " << stackHead << std::endl;
	stackHead -= back;
	stack[stackHead] = '\0';
}

char* Stack::get() {
	//std::cout << "StackHead: " << stackHead << std::endl;
	return stack;
}

void Stack::flush() {
	stackHead = 0;
	stack[0] = '\0';
}


