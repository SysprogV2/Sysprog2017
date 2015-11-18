/*
 * Stack.h
 *
 *  Created on: Nov 12, 2015
 *      Author: arty
 */

#ifndef BUFFER_INCLUDES_STACK_H_
#define BUFFER_INCLUDES_STACK_H_

#define MAX_TOKEN_SIZE 32

class Stack {
	char *stack;
	int stackHead;
public:
	Stack();
	virtual ~Stack();
	void push(char c);
    void trim(int back);
    void flush();
    char* get();
};

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
#endif /* BUFFER_INCLUDES_STACK_H_ */
