/*
 * Automat.cpp
 *
 */
//
// Created by Arty on 10/13/2015.
//

#include "../includes/Automat.h"

Automat::Automat() {
	lexemReady = false;
    currentState = Syntax::STRT_Z;
    lastFinalState = Syntax::NULL_STATE;
    lexemLength = 0;
    back = 0;
    stack = new Stack();
    position = new Position();
    lexemLine = 0;
    lexemColumn = 0;
    syntax = new Syntax();
}

Automat::~Automat() {
    delete stack;
    delete position;
    delete syntax;
}

int Automat::read(char currentChar) {
	position->update(currentChar);
	if ( !lexemReady ) {
		currentState = syntax->getState(mapCharToInt(currentChar), currentState);
		stack->push(currentChar);
		lexemLength++;
		if (isFinal(currentState)) {
			lastFinalState = currentState;
			back = 0;
		} else {
			back++;
			if (currentState == Syntax::STRT_Z ) {
				lexemReady = true;
				stack->trim(back);
				lexemLength -= back; // adjust lexemLength
				position->update(back);
				position->getPos(lexemLength, lexemLine, lexemColumn);
				return back;
			}
		}
	}
    return 0;
}

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

bool Automat::isLexemReady() {
	return lexemReady;
}

void Automat::reset() {
	lexemReady = false;
	stack->flush();
	lexemLength = 0;
	lastFinalState = Syntax::NULL_STATE;
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
	return lexemLine;
}

int Automat::getColumn() {
	return lexemColumn;
}

char* Automat::getLexem() {
	return stack->get();
}

int Automat::getLexemLength() {
	return lexemLength;
}



