/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */

#ifndef Automat_H_
#define Automat_H_

#include "Stack.h"
#include "../../Scanner/includes/Position.h"
#define SIGN_ARRAY_SZ 11

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
    /*            STRT    ID       INT	  < 		>      :	   =	 <ANY>	   <:	  <:>	   :=      Eof     WSP     *       :*   <comment>  *:    PROH_Z */
    /* a-Z */	{IDEN_Z, IDEN_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
	/* 0-9 */	{INTG_Z, IDEN_Z, INTG_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
	/*  *  */	{MULT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, OPNC_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, COMM_Z, COMM_Z, STRT_Z, STRT_Z},
	/*  <  */ 	{LESS_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
	/*  >  */	{GREA_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, LCLL_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
	/*  :  */ 	{COLN_Z, STRT_Z, STRT_Z, LCLN_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, CLSC_Z, STRT_Z, STRT_Z},
	/*  =  */ 	{EQLS_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, ASSG_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
	/* RST */	{ASGN_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
	/* EOF */	{EOF_Z,  STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
	/* WSP */	{WSP_Z,  STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, WSP_Z,  STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
    /* PRH */	{PROH_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z}
    };

    /* stores info about automata's current state */
    int currentState;
    int lastFinalState;
    int back;

    /* stores info about current token */
	int tokenType;
	int lexemLength;
	int tokenLine;
	int tokenColumn;
	bool tokenReady;
	Stack* stack;
	Position *position;

public:
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

    int getLexemType();
	int getLexemLength();
	int getLine();
	int getColumn();
};

int Automat::getLexemLength() {
	return lexemLength;
}

Automat::Automat() {
	tokenReady = false;
    currentState = STRT_Z;
    lastFinalState = NULL_STATE;
    lexemLength = 0;
    back = 0;
    stack = new Stack();
    position = new Position();
    tokenLine = 0;
    tokenColumn = 0;
}

Automat::~Automat() {
    // whatdo?
}

void Automat::freeToken() {
	tokenReady = false;
	stack->flush();
	lexemLength = 0;
}

int Automat::read(char currentChar) {
	position->update(currentChar);
	if ( !tokenReady ) {
		currentState = stateTable[mapCharToInt(currentChar)][currentState];
		stack->push(currentChar);
		lexemLength++;
		if (isFinal(currentState)) {
			lastFinalState = currentState;
			back = 0;
		} else {
			back++;
			if (currentState == STRT_Z ) {
				stack->trim(back);
				lexemLength -= back; // adjust lexemLength

				tokenType = lastFinalState;
				tokenReady = true;
				lastFinalState = NULL_STATE;

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
    return (someState != STRT_Z &&
    		someState != LCLN_Z &&
			someState != COMM_Z &&
			someState != OPNC_Z &&
			someState != EOF_Z);
}

bool Automat::isTokenReady() {
	return tokenReady;
}

int Automat::mapCharToInt(char c) {
    if (isLetter(c))      {  return ANY_LETTER; }
    else if (isWspace(c)) {  return WHITESPACE_SYMB; }
    else if (isDigit(c))  {  return ANY_DIGIT; }
    else if (c == '<')    {  return LESS_SYMB; }
    else if (c == '>')    {  return GREATER_SYMB; }
    else if (c == '*')    {  return MULT_SYMB; }
    else if (c == ':')    {  return COLON_SYMB; }
    else if (c == '=')    {	 return EQUALS_SYMB; }
    else if (isRest(c))   {	 return REST_SYMB; }
    else if (c == '\0')   {  return EOF_SYMB; }
    else                  {  return PROH_SYMB; }
}

int Automat::getLexemType() {
	return tokenType;
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
