/*
 * Stack.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#include "../includes/Stack.h"
Stack::Stack() {
	stackHead = 0;
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
	stackHead -= back;
	stack[stackHead] = '\0';
}

char* Stack::get() {
	return stack;
}

void Stack::flush() {
	stackHead = 0;
	stack[0] = '\0';
}


