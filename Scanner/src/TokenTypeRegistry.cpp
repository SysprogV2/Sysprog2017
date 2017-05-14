/*
 * TokenTypeRegistry.cpp
 *
 *  Created on: 06.05.2017
 *      Author: root
 */

#include "../includes/TokenTypeRegistry.h"

char* StringUtil::concat(char* first, char* second) {
	int firstLength = calcLength(first);
	int newLength = firstLength + calcLength(second);
	char* newstring = new char[newLength];
	for (int i = 0; i < newLength; i++) {
		newstring[i] = (i < firstLength ? first[i] : second[i - firstLength]);
	}
	return newstring;
}

int StringUtil::calcLength (char* string) {
	int length = 0;
	while (string[length] != '\0') {
		length++;
	}
	return length;
}

TokenTypeRegistry::TokenTypeRegistry() {
	this->size = 36;
	this->tokenTypes = new bool [this->size];
	for (int i = 0; i < this->size; i++) {
		this->tokenTypes[i] = false;
	}
}

void TokenTypeRegistry::set (Token* token) {
	this->tokenTypes [token->getType()] = true;
}

void TokenTypeRegistry::unset (Token* token) {
	this->tokenTypes [token->getType()] = false;
}

void TokenTypeRegistry::toggle (Token* token) {
	this->tokenTypes [token->getType()] = !this->tokenTypes [token->getType()];
}

bool TokenTypeRegistry::isSet (Token* token) {
	return this->tokenTypes[token->getType()];
}

void TokenTypeRegistry::intersectWith(TokenTypeRegistry* other) {
	for (int i = 0; i < this->size; i++) {
		this->tokenTypes[i] = this->tokenTypes[i] && other->tokenTypes[i];
	}
}

void TokenTypeRegistry::uniteWith(TokenTypeRegistry* other) {
	for (int i = 0; i < this->size; i++) {
		this->tokenTypes[i] = this->tokenTypes[i] || other->tokenTypes[i];
	}
}

char* TokenTypeRegistry::allSetTokenNames() {
	char* names = "";
	for (int i = 0; i < this->size; i++) {
		if (this->tokenTypes[i]) {
			if (names != "") {
				names = StringUtil::concat(names, ", ");
			}
			names = StringUtil::concat(names, Token::nameOf(i));
		}
	}
	return names;
}

TokenTypeRegistry::~TokenTypeRegistry() {
	delete[] this->tokenTypes;
}
