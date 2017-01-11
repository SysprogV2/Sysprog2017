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

	insert((char *) "write", 5);
	insert((char *) "WRITE", 5);
	insert((char *) "read", 4);
	insert((char *) "READ", 4);

	insert((char *) "if", 2);
	insert((char *) "IF", 2);

	insert((char *) "else", 4);
	insert((char *) "ELSE", 4);
	insert((char *) "int", 3);
	insert((char *) "INT", 3);

	insert((char *) "while", 5);
	insert((char *) "WHILE", 5);
}

void Symboltable::attachType(char* lexem, CheckableType type) {
	this->lookup(lexem)->setType(type);
}
