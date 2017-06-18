/*
 * TokenTypeRegistry.cpp
 *
 *  Created on: 06.05.2017
 *      Author: root
 */

#include "../includes/TokenTypeRegistry.h"

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
	return token != nullptr && this->tokenTypes[token->getType()];
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
	char *names = (char *) "";
	for (int i = 0; i < this->size; i++) {
		if (this->tokenTypes[i]) {
			if (names != "") {
				names = StringUtil::concat(names, (char *) ", ");
			}
			names = StringUtil::concat(names, Token::nameOf(i));
		}
	}
	return names;
}

TokenTypeRegistry::~TokenTypeRegistry() {
	delete[] this->tokenTypes;
}
