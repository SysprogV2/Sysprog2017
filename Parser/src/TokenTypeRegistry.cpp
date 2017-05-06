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

void TokenTypeRegistry::setAll (TokenSequence* sequence) {
	for (int i = 0; i < sequence->getSize(); i++) {
		this->set(sequence->tokenAt(i, false));
	}
}

void TokenTypeRegistry::unsetAll (TokenSequence* sequence) {
	for (int i = 0; i < sequence->getSize(); i++) {
		this->unset(sequence->tokenAt(i, false));
	}
}

void TokenTypeRegistry::toggleAll (TokenSequence* sequence) {
	for (int i = 0; i < sequence->getSize(); i++) {
		this->toggle(sequence->tokenAt(i, false));
	}
}

bool TokenTypeRegistry::isSet (Token* token) {
	return this->tokenTypes[token->getType()];
}

bool TokenTypeRegistry::areSet (TokenSequence* sequence, CheckoutMode mode) {
	int registeredTokens = 0;
	switch (mode) {
	case AND:
		for (int i = 0; i < sequence->getSize(); i++) {
			if (!this->isSet(sequence->tokenAt(i, false))) return false;
		}
		return true;
	case OR:
		for (int i = 0; i < sequence->getSize(); i++) {
			if (this->isSet(sequence->tokenAt(i, false))) return true;
		}
		return false;
	case NOR:
		for (int i = 0; i < sequence->getSize(); i++) {
			if (this->isSet(sequence->tokenAt(i, false))) return false;
		}
		return true;
	case NAND:
		for (int i = 0; i < sequence->getSize(); i++) {
			if (!this->isSet(sequence->tokenAt(i, false))) return true;
		}
		return false;
	case XOR:
		for (int i = 0; i < sequence->getSize(); i++) {
			if (this->isSet(sequence->tokenAt(i, false))) registeredTokens++;
		}
		return registeredTokens % 2 == 1;
	case XNOR:
		for (int i = 0; i < sequence->getSize(); i++) {
			if (this->isSet(sequence->tokenAt(i, false))) registeredTokens++;
		}
		return registeredTokens % 2 == 0;
	default:
		return false;
	}
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
				names = names + ", ";
			}
			names = names + Token::nameOf(i);
		}
	}
	return names;
}

TokenTypeRegistry::~TokenTypeRegistry() {
	delete[] this->tokenTypes;
}
