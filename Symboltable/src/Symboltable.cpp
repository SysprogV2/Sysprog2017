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
	initSymbols();
}

Symboltable::~Symboltable() {
	delete strTab;
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
	density[key]++;
	hashTab[key]->setInfo(new Information(lexemPtr));
	return hashTab[key];
}

/* checks if the given lexem is already in the table */
/* returns NULL if not 								 */
/* returns corresponding Information* object if it is*/
Information* Symboltable::lookup(char* lexem) {
	int key = hash(lexem);
	SymtabEntry* entry = hashTab[key];
	int koo = 0;
	while (koo < density[key]) {
		koo++;
		Information* info = entry->getInfo();
		bool m = info->matches(lexem);
		if (m) return info;
		entry = entry->getNext();
	}
	return NULL;
}

void Symboltable::print() {
	int key = 0;
	/* crowling through the whole table */
	while (key < TABLE_SIZE) {
		//std::cout << "Bucket #" << key << " :: ";
		SymtabEntry* entry = hashTab[key];
		int koo = 0;
		/* crawling through the bucket */
		while (koo < density[key]) {
			Information* info = entry->getInfo();
			std::cout << " " << info->getLexem();
			entry = entry->getNext();
			koo++;
		}
		key++;
		std::cout << std::endl;
	}
}


void Symboltable::initSymbols() {
	insert("write", 5);
	insert("WRITE", 5);
	insert("read", 4);
	insert("READ", 4);
	insert("if", 2);
	insert("IF", 2);
	insert("else", 4);
	insert("ELSE", 4);
	insert("int", 3);
	insert("INT", 3);
	insert("while", 5);
	insert("WHILE", 5);
}
