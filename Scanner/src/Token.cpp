/*
 * Token.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#include "../includes/Token.h"

#include <iostream>
#include <errno.h>

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
		return "unidentifiable token";
	}
}

Token::Token(int type, int line, int column) {
	this->tType = type;
	this->line = line;
	this->column = column;
	this->value = 0;
	this->symbol = 'a';
	this->information = nullptr;
}

Token::Token(int state, int l, int c, Information* info) {
	this->tType = state;
	this->value = 0;
	this->symbol = 'a';
	this->line = l;
	this->column = c;
	this->information = info;
}

Token::~Token() {
	delete information;
}

Information* Token::getInformation() {
	return information;
}

void Token::setInformation(Information* info) {
	this->information = info;
}

int Token::getType(){

	std::cout << "debuging *** Token::getType STRT" << std::endl;
	std::cout << tType << std::endl;
	int toReturn = tType;
	std::cout << "debuging *** Token::getType END" << std::endl;
	return toReturn;
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

int Token::getValue() {
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
