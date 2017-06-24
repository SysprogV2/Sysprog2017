/*
 * Symboltable.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_


#include "StringTab.h"
#include "SymtabEntry.h"
#include "../../Scanner/includes/Information.h"
#include <iostream>

#define TABLE_SIZE 1019 // prime number here! btw 2^x - 1 is always prime
#define R_CONST 31      // prime number here too!

class Symboltable {
	SymtabEntry *hashTab[TABLE_SIZE];
	int* density;
	StringTab* strTab;

public:
	Symboltable();
	virtual ~Symboltable();

//	int hash( char *lexem);
	static int hash(char *lexem);
	SymtabEntry* insert(char *lexem, int size, Token* token);
	Information* lookup(int key);
	Information* lookup(char* lexem);
	void attachType (char* lexem, CheckableType type);
	void initSymbols();
	void print();
};


#endif /* SYMBOLTABLE_H_ */
