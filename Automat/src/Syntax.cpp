/*
 * Syntax.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#include "../includes/Syntax.h"

Syntax::Syntax() {

}

Syntax::~Syntax() {

}

char* Syntax::getTokenTypeAsChar(int num) {
	return ttypeString[num];
}

 int Syntax::getState(int i, int j) {
	 return stateTable[i][j];
 }

 bool Syntax::isRest(char c) {
	for (int i = 0; i < SIGN_ARRAY_SZ; i++) {
 		if (c == signArray[i]) return true;
 	}
 }

int Syntax::unpackSignToState(char sign) {
	for (int i=0; i < SIGN_ARRAY_SZ; i++) {
		if (sign == signArray[i])
			return i + 19;
	}
	return -1;
}

int Syntax::ifKeyword(char* lexem) {
	char* another;
	int tType = 0;
	for (int i = 0; i < 12; i++) {
		another = keywordsArray[i];
		if (matches(lexem, another))
			return (30 + i / 2);
	}
	return -1;
}

bool Syntax::matches(char* one, char* another) {
	char* tmp1 = one;
	char* tmp2 = another;
	while (tmp1[0] != '\0' || tmp2[0] != '\0') {
		if (tmp1++[0] != tmp2++[0]) {
			return false;
		}
	}
	return true;
}


