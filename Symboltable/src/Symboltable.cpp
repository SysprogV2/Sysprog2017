/*
 * Symboltable.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include "../includes/Symboltable.h"

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
	if (hashTab[key] == nullptr) {
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
	int tmp = 0;
	while (tmp < density[key]) {
		tmp++;
		Information* info = entry->getInfo();
		if (info->matches(lexem)) return info;
		entry = entry->getNext();
	}
	return nullptr;
}

void Symboltable::print() {
	int key = 0;
	/* crowling through the whole table */
	while (key < TABLE_SIZE) {
		std::cout << "Bucket #" << key << " :: ";
		SymtabEntry* entry = hashTab[key];
		int tmp = 0;
		/* crawling through the bucket */
		while (tmp < density[key]) {
			Information* info = entry->getInfo();
			std::cout << " -> " << info->getLexem();
			entry = entry->getNext();
			tmp++;
		}
		key++;
		std::cout << std::endl;
	}
}


void Symboltable::initSymbols() {
	/*
	insert("write", 5);
	insert("WRITE", 5);
	insert("read", 4);
	insert("READ", 4);
	*/
	insert("if", 2);
	insert("IF", 2);
	/*
	insert("else", 4);
	insert("ELSE", 4);
	insert("int", 3);
	insert("INT", 3);
	*/
	insert("while", 5);
	insert("WHILE", 5);
}
