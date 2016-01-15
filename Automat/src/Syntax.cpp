/*
 * Syntax.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#include "../includes/Syntax.h"

Syntax::Syntax() {
	keywordNumber = KEYWORD_NUMBER;
}

Syntax::~Syntax() {

}

char* Syntax::getTokenTypeAsChar(int num) {
	return ttypeString[num];
}

int Syntax::getState(int i, int j) {
	return stateTable[i][j];
}

/*
 * finds a state for a given "packed" character
 * returns -1 if the char does NOT belong to a group
 *     of "packed" chars
 * @return corresponding state for a char
 */
int Syntax::isPacked(char sign) {
	for (int i = 0; i < SIGN_ARRAY_SZ; i++) {
		if (sign == signArray[i]) return i + STATETABLE_WIDTH + 1;
	}
	return -1;
}

/*
 * checks whether the given lexem is a keyword
 * returns -1 if not
 * @return corresponding token type for keyword
 */
int Syntax::ifKeyword(char* lexem) {
	int tType = 0;
	for (int i = 0; i < KEYWORD_NUMBER * 2; i++) {
		if (matches(lexem, keywordsArray[i]))
			return (STATES_NUMBER + i / 2);
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


