/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */

#ifndef Automat_H_
#define Automat_H_

#include "Stack.h"
#include "Syntax.h"
#include "../../Scanner/includes/Position.h"
#define SIGN_ARRAY_SZ 11

class Automat {
	const char signArray[SIGN_ARRAY_SZ] = {'+', '-', '!', '&', ';',
										   '(', ')','{', '}', '[', ']'};

    /* stores info about automata's current state */
    int currentState;
    int lastFinalState;
    int back;

    /* stores info about current token */
	int lexemLength;
	int tokenLine;
	int tokenColumn;
	bool tokenReady;
	Stack* stack;
	Position *position;

public:

	Syntax* syntax;

    Automat();
    ~Automat();

    int read(char c);
    int mapCharToInt(char c);

    bool isEof(char c);
    bool isRest(char c);
    bool isDigit(char c);
    bool isLetter(char c);
    bool isWspace(char c);
    bool isFinal(int someState);

    char* getLexem();
    bool isTokenReady();
    void freeToken();

    int getFinalState();
	int getLexemLength();
	int getLine();
	int getColumn();
};

int Automat::getLexemLength() {
	return lexemLength;
}

Automat::Automat() {
	tokenReady = false;
    currentState = Syntax::STRT_Z;
    lastFinalState = Syntax::NULL_STATE;
    lexemLength = 0;
    back = 0;
    stack = new Stack();
    position = new Position();
    tokenLine = 0;
    tokenColumn = 0;
    syntax = new Syntax();
}

Automat::~Automat() {
    // whatdo?
}

void Automat::freeToken() {
	tokenReady = false;
	stack->flush();
	lexemLength = 0;
	lastFinalState = Syntax::NULL_STATE;
}

int Automat::read(char currentChar) {
	position->update(currentChar);
	if ( !tokenReady ) {
		currentState = syntax->getState(mapCharToInt(currentChar), currentState);
		//currentState = Syntax::stateTable[mapCharToInt(currentChar)][currentState];
		stack->push(currentChar);
		lexemLength++;
		if (isFinal(currentState)) {
			lastFinalState = currentState;
			back = 0;
		} else {
			back++;
			if (currentState == Syntax::STRT_Z ) {
				tokenReady = true;
				stack->trim(back);
				lexemLength -= back; // adjust lexemLength
				position->update(back);
				tokenLine = position->seekLineWithOffset(lexemLength) + 1;
				tokenColumn = position->seekColumnWithOffset(lexemLength) + 1;
				return back;
			}
		}
	} // if (!tokenReady)
    return 0;
}

/* */
bool Automat::isRest(char c) {
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

bool Automat::isWspace(char c) {
    return (c == '\n') || (c == ' ') ||  (c == '\t');
}

bool Automat::isFinal(int someState) {
    return (someState != Syntax::STRT_Z &&
    		someState != Syntax::LCLN_Z &&
			someState != Syntax::COMM_Z &&
			someState != Syntax::OPNC_Z &&
			someState != Syntax::EOF_Z);
}

bool Automat::isTokenReady() {
	return tokenReady;
}

int Automat::mapCharToInt(char c) {
    if (isLetter(c))      {  return Syntax::ANY_LETTER; }
    else if (isWspace(c)) {  return Syntax::WHITESPACE_SYMB; }
    else if (isDigit(c))  {  return Syntax::ANY_DIGIT; }
    else if (c == '<')    {  return Syntax::LESS_SYMB; }
    else if (c == '>')    {  return Syntax::GREATER_SYMB; }
    else if (c == '*')    {  return Syntax::MULT_SYMB; }
    else if (c == ':')    {  return Syntax::COLON_SYMB; }
    else if (c == '=')    {	 return Syntax::EQUALS_SYMB; }
    else if (isRest(c))   {	 return Syntax::REST_SYMB; }
    else if (c == '\0')   {  return Syntax::EOF_SYMB; }
    else                  {  return Syntax::PROH_SYMB; }
}

int Automat::getFinalState() {
	return lastFinalState;
}

int Automat::getLine() {
	return tokenLine;
}

int Automat::getColumn() {
	return tokenColumn;
}

char* Automat::getLexem() {
	return stack->get();
}


#endif /* Automat_H_ */
