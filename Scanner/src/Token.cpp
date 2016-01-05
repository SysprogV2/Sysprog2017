/*
 * Token.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#include "../includes/Token.h"
//#include "../../Automat/includes/Syntax.h"
#include <iostream>
#include <errno.h>
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
	return tType;
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
