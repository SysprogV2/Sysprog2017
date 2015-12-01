/*
 * Symboltable.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include "../includes/Symboltable.h"
#include "../includes/SymtabEntry.h"
#include "../../Scanner/includes/Information.h"

Symboltable::Symboltable() {

	strTab = new StringTab();
	/*
	for (int i = 0; i < TABLE_SIZE; i++) {
		sTable[i] = new SymtabEntry();
	}
	*/
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

SymtabEntry* Symboltable::insert(char *lexem, int size) {
	int key = hash(lexem);
	if (hashTab[key] == NULL) {
		hashTab[key] = new SymtabEntry();
	} else {
		SymtabEntry prev = hashTab[key];
		hashTab[key] = new SymtabEntry(prev);

	}
	char* lexemPtr = strTab->insert(lexem, size);
	hashTab[key]->setInfo(new Information(lexemPtr));
	return hashTab[key];
}

/* checks if the given lexem is already in the table */
/* returns NULL if not 								 */
/* returns corresponding Information* object if it is*/
Information* Symboltable::lookup(char* lexem) {
	int key = hash(lexem);
	SymtabEntry* entry = hashTab[key];
	while (entry != NULL) {
		Information* info = entry->getInfo();
		if (info->matches(lexem)) return info;
		entry = entry->getNext();
	}
	return NULL;
}

void Symboltable::initSymbols() {
	insert("write", 5);
	insert("read", 4);
	insert("if", 2);
	insert("else", 5);
	insert("while", 5);
	insert("int", 5);
}
