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

#define TABLE_SIZE 1019 // prime number here!
#define R_CONST 31      // prime number here too!

class Symboltable {
	SymtabEntry *hashTab[TABLE_SIZE];
	int density[TABLE_SIZE] = {0};
	StringTab* strTab;

public:
	Symboltable();
	virtual ~Symboltable();

	int hash(char *lexem);
	SymtabEntry* insert(char *lexem, int size);
	Information* lookup(char* lexem);
	void initSymbols();
	void print();
};


#endif /* SYMBOLTABLE_H_ */
