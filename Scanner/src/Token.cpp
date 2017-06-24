/*
 * Token.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#include "../includes/Token.h"
#include "../../Symboltable/includes/Symboltable.h"

#include <iostream>
#include <cstdarg>

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

char* StringUtil::format(char *fmt, ...) {
	va_list args;
	char* buf = new char[1000]; // TODO: potential memory leak!
	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args );
	va_end(args);
	return buf;
}

char* Token::nameOf(int tokenType) {
	switch (tokenType) {
	case 1:
		return (char *) "identifier";
	case 2:
		return (char *) "integer";
	case 3:
	case 4:
	case 6:
	case 7:
	case 9:
		return (char *) "comparision";
	case 5:
		return (char *) "division";
	case 10:
		return (char *) "assignment";
	case 13:
		return (char *) "multiplication";
	case 19:
		return (char *) "addition";
	case 20:
		return (char *) "negative signum or substraction";
	case 21:
		return (char *) "boolean negator";
	case 22:
		return (char *) "\"and\" mask";
	case 23:
		return (char *) "semicolon";
	case 24:
		return (char *) "opening paranthesis (\"(\")";
	case 25:
		return (char *) "closing paranthesis (\")\")";
	case 26:
		return (char *) "opening brace (\"{\")";
	case 27:
		return (char *) "closing brace (\"}\")";
	case 28:
		return (char *) "opening bracket (\"[\")";
	case 29:
		return (char *) "closing bracket (\"]\")";
	case 30:
		return (char *) "keyword \"if\"";
	case 31:
		return (char *) "keyword \"while\"";
	case 32:
		return (char *) "keyword \"int\"";
	case 33:
		return (char *) "keyword \"write\"";
	case 34:
		return (char *) "keyword \"else\"";
	case 35:
		return (char *) "keyword \"read\"";
	default:
		return StringUtil::format((char *) "unidentifiable token (%d)", tokenType);
	}
}

Token::Token(int type, int line, int column) {
	this->signArray = new const char[14] {'+','-','!','&',';','(',')','{','}','[',']'};
		// TODO: test if 14
	this->tType = type;
	this->line = line;
	this->column = column;
	this->value = 0;
	this->symbol = 'a';
	this->information = nullptr;
	this->errorMessage = nullptr;
}

Token::Token(int state, int l, int c, Information* info) {
	this->signArray = new const char[14] {'+','-','!','&',';','(',')','{','}','[',']'};

	this->tType = state;
	this->value = 0;
	this->symbol = 'a';
	this->line = l;
	this->column = c;
	this->information = info;
}

Token::~Token() {
	delete information;
	delete[] signArray;
}

Information* Token::getInformation() {
	return information;
}

void Token::setInformation(Information* info) {
	this->information = info;
}

int Token::getType(){
	return tType;
}

void Token::setType(int type) {
	this->tType = type;
}

char* Token::getLexem() {
	return information->getLexem();
}

int Token::getLine() {
	return line;
}

int Token::getColumn() {
	return column;
}

long int Token::getValue() {
	return value;
}

int Token::getKey() {
	return Symboltable::hash(this->getLexem());
}

char Token::getSymbol() {
	return symbol;
}

void Token::setValue(long int value) {
	this->value = value;
}

void Token::setSymbol(char symbol) {
	this->symbol = symbol;
}

bool Token::hasSameTypeAs(Token* other) {
	return this->tType == other->tType;
}

char* Token::getErrorMessage() {
	return this->errorMessage;
}

void Token::setErrorMessage(char* errorMessage) {
	this->errorMessage = errorMessage;
}