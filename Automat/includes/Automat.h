/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */

#ifndef Automat_H_
#define Automat_H_

#define SIGN_ARRAY_SZ 11
#define MAX_TOKEN_SIZE 32 /* CAN ONLY ACCEPT TOKENS THAT ARE 32c LONG OR LESS!!!! */

#ifndef IOSTREAM_H
#define IOSTREAM_H
#include <iostream>
#endif /* IOSTREAM_H */


#ifndef STDIO_H
#define STDIO_H
#include <stdio.h>
#endif /* IOSTREAM_H */

#include "../../Scanner/includes/Position.h"

class Automat {
	const char signArray[SIGN_ARRAY_SZ] = {'+', '-', '!', '&', ';', '(', ')','{', '}', '[', ']'};
	enum States {STRT_Z, IDEN_Z, INTG_Z, LESS_Z, GREA_Z, COLN_Z, 
				 EQLS_Z, ASGN_Z, LCLN_Z, LCLL_Z, ASSG_Z, EOF_Z, 
				 WSP_Z, MULT_Z, OPNC_Z, COMM_Z, CLSC_Z, PROH_Z, 
				 NULL_STATE};
    enum Symbols {ANY_LETTER, ANY_DIGIT, MULT_SYMB, LESS_SYMB,
    			  GREATER_SYMB, COLON_SYMB, EQUALS_SYMB, REST_SYMB,
				  EOF_SYMB, WHITESPACE_SYMB, PROH_SYMB};
    int stateTable[11][18] = {
    			// STRT   ID       INT	  < 		>      :	   =	 <ANY>	   <:	  <:>	   :=      Eof     WSP     *       :*   <comment>  *:    PROH_Z
    /* a-Z */	{IDEN_Z, IDEN_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
	/* 0-9 */	{INTG_Z, IDEN_Z, INTG_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
	/*  *  */	{MULT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, OPNC_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, COMM_Z, COMM_Z, STRT_Z, STRT_Z},
	/*  <  */ 	{LESS_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
	/*  >  */	{GREA_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, LCLL_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
	/*  :  */ 	{COLN_Z, STRT_Z, STRT_Z, LCLN_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, CLSC_Z, STRT_Z, STRT_Z},
	/*  =  */ 	{EQLS_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, ASSG_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
	/* Rst */	{ASGN_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
	/* Eof */	{EOF_Z,  STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
	/* wsp */	{WSP_Z,  STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, WSP_Z,  STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
    /* Prh */	{PROH_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z}
    };

    /* stores info about automata state */
    int currentState;
    int lastFinalState;
    int back;

    /* stores info about current token */
	int tokenType;
	int tokenLength;
	int tokenLine;
	int tokenColumn;
	bool tokenReady;
	char *stack;
    int stackHead;
	Position *position;

public:
    Automat();
    ~Automat();
    int read(char c);

    bool isEof(char c);
    bool isRestSign(char c);
    bool isDigit(char c);
    bool isLetter(char c);
    bool isWhitespace(char c);
    bool isFinal(int someState);
    int mapCharToInt(char c);

    void stackPush(char c);
    void stackTrim(int back);
    void stackFlush();
    char * stackGet();

    bool isTokenReady();
    void freeToken();
    int getTokenType();
	int getTokenLength();
	int getLine();
	int getColumn();
};

int Automat::getTokenLength() {
	return tokenLength;
}

Automat::Automat() {
	tokenReady = false;
    currentState = STRT_Z;
    lastFinalState = NULL_STATE;
    tokenLength = 0;
    back = 0;
    stack = new char[MAX_TOKEN_SIZE];
    stackHead = 0;
    position = new Position();
    tokenLine = 0;
    tokenColumn = 0;
}

Automat::~Automat() {
    delete stack;
}

void Automat::freeToken() {
	tokenReady = false;
	stackFlush();
}

int Automat::read(char currentChar) {
	/* pos */
	position->update(currentChar);
	if ( !tokenReady ) {
		currentState = stateTable[mapCharToInt(currentChar)][currentState];
		stackPush(currentChar);
		tokenLength++;
		if (isFinal(currentState)) {
			lastFinalState = currentState;
			back = 0;
		} else {
			back++;
			if (currentState == STRT_Z ) {
				stackTrim(back);
				tokenType = lastFinalState;
				tokenReady = true;
				lastFinalState = NULL_STATE;
				tokenLength -= back; // adjust tokenLength
				position->update(back);
				tokenLine = position->seekLineWithOffset(tokenLength) + 1;
				tokenColumn = position->seekColumnWithOffset(tokenLength) + 1;
				/* std::cout << std::endl << "DEBUG: " << position->seekLineWithOffset(tokenLength) + 1
				        << " " << position->seekColumnWithOffset(tokenLength) + 1 << " "
						<< "   length: " << (tokenLength) << " " << std::endl; */
				tokenLength = 0;
				return back;
			}
		}
	} // if (!tokenReady)
    return 0;
}







bool Automat::isRestSign(char c) {
	for (int i = 0; i < SIGN_ARRAY_SZ; i++) {
		if (c == signArray[i]) return true;
	}
    return false;
}

bool Automat::isDigit(char c) {
    return (c >= '0') && (c <= '9');
}

bool Automat::isLetter(char c) {
    return ((c >= 'a') && (c <= 'z')) ||
    		((c >= 'A') && (c <= 'Z'));
}

bool Automat::isWhitespace(char c) {
    return (c == '\n') || (c == ' ') ||  (c == '\t');
}

bool Automat::isFinal(int someState) {
    return (someState != LCLN_Z &&
			someState != STRT_Z &&
			someState != EOF_Z &&
			someState != COMM_Z &&
			someState != OPNC_Z);
}

bool Automat::isTokenReady() {
	return tokenReady;
}

int Automat::mapCharToInt(char c) {
    if (isLetter(c)) {
        return ANY_LETTER;
    } else if (isDigit(c)) {
        return ANY_DIGIT;
    } else if (c == '<') {
        return LESS_SYMB;
    } else if (c == '>') {
        return GREATER_SYMB;
    } else if (c == '*') {
        return MULT_SYMB;
    } else if (c == ':') {
        return COLON_SYMB;
    } else if (c == '=') {
        return EQUALS_SYMB;
    } else if (c == '\0') {
        return EOF_SYMB;
    } else if (isRestSign(c)){
        return REST_SYMB;
    } else if (isWhitespace(c)){
        return WHITESPACE_SYMB;
    } else {
        return PROH_SYMB;
    }
}

int Automat::getTokenType() {
	return tokenType;
}

int Automat::getLine() {
	return tokenLine;
}

int Automat::getColumn() {
	return tokenColumn;
}







/* TODO: replace all these stupid functions into separate class */
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
	stack[0] = '\0';
}


#endif /* Automat_H_ */
