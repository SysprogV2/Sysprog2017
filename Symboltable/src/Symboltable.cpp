/*
 * Symboltable.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include "../includes/Symboltable.h"
#include "../../Scanner/includes/Token.h"

Symboltable::Symboltable() {
	density = new int[TABLE_SIZE];
	density[0] = 0;

	strTab = new StringTab();
//	initSymbols();
}

Symboltable::~Symboltable() {
	delete strTab;
	delete[] density;
}

///*
// * from Algorithms, 4th edition by Sedgewick & Wayne
// */
//int Symboltable::hash(const char *lexem) {
//	int hash = 0;
//	const char *tmpPtr = lexem;
//	while (tmpPtr[0] != '\0') {
//		hash = (R_CONST * hash + tmpPtr[0]) % TABLE_SIZE;
//		tmpPtr++;
//	}
//	return hash;
//}

static int Symboltable::hash(char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash % TABLE_SIZE;
}

SymtabEntry* Symboltable::insert(char *lexem, int size, Token* token) {
//	size++;
	int key = hash(lexem);
	if (hashTab[key] == nullptr) {
		hashTab[key] = new SymtabEntry();
	} else {
		SymtabEntry* prev = hashTab[key];
		hashTab[key] = new SymtabEntry(prev);
	}
	char* lexemPtr = strTab->insert(lexem, size);
	density[key]++;
	hashTab[key]->setInfo(new Information(lexemPtr, token));
	return hashTab[key];
}


/* checks if the given lexem is already in the table */
/* returns NULL if not 								 */
/* returns corresponding Information* object if it is*/
Information* Symboltable::lookup(int key) {
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

/* checks if the given lexem is already in the table */
/* returns NULL if not 								 */
/* returns corresponding Information* object if it is*/
Information* Symboltable::lookup(char* lexem) {
	return lookup(hash(lexem));
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

void Symboltable::attachType(char* lexem, CheckableType type) {
	this->lookup(lexem)->setType(type);
}
