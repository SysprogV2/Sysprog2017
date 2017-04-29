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

class Automat {
    /* stores info about automata's current state */
    int currentState;
    int lastFinalState;


    /* stores position */
    int gLine;
    int gCol;
    int tmpCol;

    /* stores info about current lexem */
	int lexemLength;
	int lexemLine;
	int lexemColumn;
	bool lexemReady;
	Stack* stack;
	Syntax* syntax;
public:

int back;

    Automat();
    ~Automat();

    int read(char c);
    int mapCharToSymbolName(char c);

    bool isEof(char c);
    bool isDigit(char c);
    bool isLetter(char c);
    bool isWspace(char c);
    bool isFinal(int someState);

    const char* getLexem();
    bool isLexemReady();
    void reset();

    int getFinalState();
	int getLexemLength();
	int getLine();
	int getColumn();

	void updatePos(char c);
	void updatePosition(int back);
};

#endif
