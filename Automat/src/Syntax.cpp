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

/*
 const static char* Syntax::getTokenTypeAsChar(int num) {

	return ttypeString[num];
}*/

 int Syntax::getState(int i, int j) {
	 return stateTable[i][j];
 }

 bool Syntax::isRest(char c) {
	for (int i = 0; i < SIGN_ARRAY_SZ; i++) {
 		if (c == signArray[i]) return true;
 	}
 }
