/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */

#ifndef Automat_H_
#define Automat_H_

#define SIGN_ARRAY_SZ 12
#define STACK_SIZE 32

#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif /* IOSTREAM_H */


#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif /* IOSTREAM_H */

class Automat {
	const char signArray[SIGN_ARRAY_SZ] = {'+', '-', '*', '!', '&', ';', '(', ')','{', '}', '[', ']'};
    enum States {START_STATE, ID_STATE, INT_STATE,
    			LESS_STATE, GREATER_STATE, COLON_STATE, EQUALS_STATE,
				ANY_SIGN_STATE, LESSCOLON_STATE,LESSCOLONLESS_STATE,
				ASSIGN_STATE, EOF_STATE, NULL_STATE};
    enum Symbols {ANY_LETTER, ANY_DIGIT, LESS, GREATER, COLON,
    			EQUALS, REST_SIGNS, EOF_SYMB, WHITESPACE, PROH_SIGN};
    int stateTable[9][12] = {
    			// STRT		 ID			INT			  <				>		   :			=			<ANY>		 <:			  <:>		   :=         Eof
    /* a-Z */	{ID_STATE, ID_STATE, START_STATE, START_STATE, START_STATE,START_STATE, START_STATE, START_STATE,START_STATE, START_STATE, START_STATE, EOF_STATE},
	/* 0-9 */	{INT_STATE, ID_STATE, INT_STATE, START_STATE, START_STATE,START_STATE, START_STATE, START_STATE,START_STATE, START_STATE, START_STATE, EOF_STATE},
	/*  <  */ 	{LESS_STATE, START_STATE, START_STATE, START_STATE, START_STATE,START_STATE, START_STATE, START_STATE,START_STATE, START_STATE, START_STATE, EOF_STATE},
	/*  >  */	{GREATER_STATE, START_STATE, START_STATE, START_STATE, START_STATE,START_STATE, START_STATE, START_STATE, LESSCOLONLESS_STATE, START_STATE, START_STATE, EOF_STATE},
	/*  :  */ 	{COLON_STATE, START_STATE, START_STATE, LESSCOLON_STATE, START_STATE,START_STATE, START_STATE, START_STATE,START_STATE, START_STATE, START_STATE, EOF_STATE},
	/*  =  */ 	{EQUALS_STATE, START_STATE, START_STATE, START_STATE, START_STATE, ASSIGN_STATE, START_STATE, START_STATE,START_STATE, START_STATE, START_STATE, EOF_STATE},
	/* RST */	{ANY_SIGN_STATE, START_STATE, START_STATE, START_STATE, START_STATE, START_STATE, START_STATE, START_STATE, START_STATE, START_STATE, START_STATE, EOF_STATE},
    /* EOF */	{EOF_STATE, EOF_STATE, EOF_STATE, EOF_STATE, EOF_STATE, EOF_STATE, EOF_STATE, EOF_STATE, EOF_STATE, EOF_STATE, EOF_STATE, EOF_STATE}
    /* WSP *///  ,{START_STATE, START_STATE, START_STATE, START_STATE, START_STATE,START_STATE, START_STATE, START_STATE,START_STATE, START_STATE, START_STATE, START_STATE}
    /* PRH */
    };

    int currentState;
    int lastFinalState;
    int back;
    char *stack;
    int stackHead;

public:
    Automat();
    ~Automat();
    int read(char c);
    bool isEof(char c);
    bool isSign(char c);
    bool isDigit(char c);
    bool isLetter(char c);
    bool isWhitespace(char c);
    bool isFinal(int someState);
    int mapCharToInt(char c);
    void stackPush(char c);
    void stackTrim(int back);
    void stackFlush();
    char * stackGet();
};







Automat::Automat() {
    currentState = START_STATE;
    lastFinalState = NULL_STATE;
    back = 0;
    stack = new char[STACK_SIZE];
    stackHead = 0;
}


Automat::~Automat() {
    /* free mem  */
	/* free stack */
}


int Automat::read(char currentChar) {
	stackPush(currentChar);
    currentState = stateTable[mapCharToInt(currentChar)][currentState];

    if (isFinal(currentState)) {
        lastFinalState = currentState;
        back = 0;
    } else {
        back++;
        if (currentState == START_STATE || currentState == EOF_STATE) {
        	stackTrim(back);
        	std::cout << "> " <<  stackGet() << std::endl;
            lastFinalState = NULL_STATE;
            int tmpBack = back;
            back = 0;
            stackFlush();
            return tmpBack;
        }
    }

    return 0;
}


bool Automat::isSign(char c) {
	for (int i = 0; i < SIGN_ARRAY_SZ; i++) {
		if (c == signArray[i]) return true;
	}
    return false;
}


bool Automat::isDigit(char c) {
    return (c >= '0') && (c <= '9');
}


bool Automat::isLetter(char c) {
    return ((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z'));
}


bool Automat::isWhitespace(char c) {
    return (c == '\n') || (c == ' ') ||  (c == '\t');
}

bool Automat::isFinal(int someState) {
    return (someState != LESSCOLON_STATE && someState != START_STATE && someState != EOF_STATE);
}

int Automat::mapCharToInt(char c) {
    if (isLetter(c)) {
        return ANY_LETTER;
    } else if (isDigit(c)) {
        return ANY_DIGIT;
    } else if (c == '<') {
            return LESS;
    } else if (c == '>') {
            return GREATER;
    } else if (c == ':') {
        return COLON;
    } else if (c == '=') {
        return EQUALS;
    } else if (c == '\0') {
        return EOF_SYMB;
    } else if (isSign(c)){
        return REST_SIGNS;
    } else if (isWhitespace(c)){
        return WHITESPACE;
    } else {
        return PROH_SIGN;
    }
}

void Automat::stackPush(char c) {
	stack[stackHead++] = c;
	stack[stackHead] = '\0';
}

void Automat::stackTrim(int back) {
	stackHead -= back;
	stack[stackHead] = '\0';
}

char * Automat::stackGet() {
	return stack;
}

void Automat::stackFlush() {
	stackHead = 0;
	for (int i = 0; i < STACK_SIZE; i++) {
		stack[i] = '\0';
	}
}






#endif /* Automat_H_ */
