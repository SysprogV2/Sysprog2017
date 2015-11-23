/*
 * Automat.h
 *
 *  Created on: Jul 5, 2012
 *      Author: knad0001
 */

#ifndef Automat_H_
#define Automat_H_

#include "Stack.h"
#include "Position.h"
#include "Syntax.h"

#define SIGN_ARRAY_SZ 11

class Automat {
	const char signArray[SIGN_ARRAY_SZ] = {'+', '-', '!', '&', ';', '(', ')','{', '}', '[', ']'};

    /* stores info about automata's current state */
    int currentState;
    int lastFinalState;
    int back;

    /* stores info about current lexem */
	int lexemLength;
	int lexemLine;
	int lexemColumn;
	bool lexemReady;
	Stack* stack;
	Position *position;
	Syntax* syntax;
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
    bool isLexemReady();
    void reset();

    int getFinalState();
	int getLexemLength();
	int getLine();
	int getColumn();
};

#endif
