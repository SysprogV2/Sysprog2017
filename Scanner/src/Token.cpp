/*
 * Token.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#include "../includes/Token.h"

#include <iostream>
#include <errno.h>
#include <cstdarg>
#include <cstdio>

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
	char buf[1000];
	va_start(args, fmt);
	vsnprintf(buf, sizeof(buf), fmt, args );
	va_end(args);
	return buf;
}

char* Token::nameOf(int tokenType) {
	switch (tokenType) {
	case 1:
		return "identifier";
	case 2:
		return "integer";
	case 3:
	case 4:
	case 6:
	case 7:
	case 9:
		return "comparision";
	case 5:
		return "division";
	case 10:
		return "assignment";
	case 13:
		return "multiplication";
	case 19:
		return "addition";
	case 20:
		return "negative signum or substraction";
	case 21:
		return "boolean negator";
	case 22:
		return "\"and\" mask";
	case 23:
		return "semicolon";
	case 24:
		return "opening paranthesis (\"(\")";
	case 25:
		return "closing paranthesis (\")\")";
	case 26:
		return "opening brace (\"{\")";
	case 27:
		return "closing brace (\"}\")";
	case 28:
		return "opening bracket (\"[\")";
	case 29:
		return "closing bracket (\"]\")";
	case 30:
		return "keyword \"if\"";
	case 31:
		return "keyword \"while\"";
	case 32:
		return "keyword \"int\"";
	case 33:
		return "keyword \"write\"";
	case 34:
		return "keyword \"else\"";
	case 35:
		return "keyword \"read\"";
	default:
		return StringUtil::format("unidentifiable token (%d)", tokenType);
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