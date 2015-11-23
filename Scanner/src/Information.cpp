/*
 * Information.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#include "../includes/Information.h"


Information::Information() {
	setLexem("df");
}

Information::Information(char* lexem) {
	setLexem(lexem);
}

Information::~Information() {

}

void Information::setLexem(char* lexem) {
	this->lexem = lexem;
}

char* Information::getLexem() {
	return lexem;
}

bool Information::matches(char* other) {
	char* tmp1 = this->lexem;
	char* tmp2 = other;
	while (tmp1[0] != '\0' && tmp2[0] != '\0') {
		if (tmp1++[0] != tmp2++[0]) {
			return false;
		}
	}
	return true;
}
