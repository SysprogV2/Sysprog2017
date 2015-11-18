/*
 * Symboltable.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef SYMBOLTABLE_H_
#define SYMBOLTABLE_H_


#include "StringTab.h"
#include <iostream>

#define TABLE_SIZE 1019 // prime number here!
#define R_CONST 31      // prime number here too!

class Symboltable {
	char *charPtr[TABLE_SIZE];
	StringTab* sTab;
public:
	Symboltable();
	virtual ~Symboltable();
	int hash(char *lexem);
	char* insert(char *lexem, int size);
	char* lookup(int key);
	void initSymbols();
};

Symboltable::Symboltable() {
	sTab = new StringTab();
}

Symboltable::~Symboltable() {
	// nothing
}

/*
 * from Algorithms, 4th edition by Sedgewick & Wayne
 */
int Symboltable::hash(char *lexem) {
	int hash = 0;
	char *tmpPtr = lexem;
	while (tmpPtr[0] != '\0') {
		hash = (R_CONST * hash + tmpPtr[0]) % TABLE_SIZE;
		tmpPtr++;
	}
	return hash;
}

char* Symboltable::insert(char *lexem, int size) {
	int key = hash(lexem);
	charPtr[key] = sTab->insert(lexem, size);
	return charPtr[key];
}

char* Symboltable::lookup(int key) {
	return charPtr[key];
}

void Symboltable::initSymbols() {
	insert("while", 5);
}
#endif /* SYMBOLTABLE_H_ */
