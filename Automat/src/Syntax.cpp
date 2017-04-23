/*
 * Syntax.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#include "../includes/Syntax.h"

Syntax::Syntax() {
	keywordNumber = KEYWORD_NUMBER;

	this->stateTable = new int*[STATETABLE_HEIGHT]{
					/*            STRT    ID       INT	      :	     =	   <ANY>	  =:	 =:=	 :=      &      &&      Eof     WSP     *       :*   <comment>  *:    PROH_Z */
					/* a-Z */	new int[STATETABLE_WIDTH]{IDEN_Z, IDEN_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
					/* 0-9 */	new int[STATETABLE_WIDTH]{INTG_Z, IDEN_Z, INTG_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
					/*  *  */	new int[STATETABLE_WIDTH]{MULT_Z, STRT_Z, STRT_Z,   OPNC_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, COMM_Z, COMM_Z, STRT_Z, STRT_Z},
					/*  :  */ 	new int[STATETABLE_WIDTH]{COLN_Z, STRT_Z, STRT_Z,   STRT_Z, LCLN_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, CLSC_Z, STRT_Z, STRT_Z},
					/*  =  */ 	new int[STATETABLE_WIDTH]{EQLS_Z, STRT_Z, STRT_Z,   ASSG_Z, STRT_Z, STRT_Z, LCLL_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
		/*  added new	&  */   new int[STATETABLE_WIDTH]{AND1_Z, STRT_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, AND2_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
					/* RST */	new int[STATETABLE_WIDTH]{ASGN_Z, STRT_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
					/* EOF */	new int[STATETABLE_WIDTH]{EOF_Z,  STRT_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
					/* WSP */	new int[STATETABLE_WIDTH]{WSP_Z,  STRT_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  STRT_Z, STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
					/* PRH */	new int[STATETABLE_WIDTH]{PROH_Z, STRT_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z}
		};

	ttypeString = new const char*[STATES_NUMBER + KEYWORD_NUMBER] {
								 "Start     ", "Identifier", "Integer   ", "Colon     ", //  0- 3
								 "Equals    ", "=:=-sign  ", "  --=:--  ", "=:=       ", //  4- 7
								 "Assignment", " --eof--  ", "Whitespace", "Multipl   ", //  8-11
								 "  --:*--  ", " --comm-- ", "  --*:--  ", "Prohibited", // 12-15
								 " --null-- ", "PlusToken ", "MinusToken", "NotToken  ", // 16-19
								 "SglAndTok ", "DblAndTok ","SemicolTok ", "Paranth ( ", // 20-23  replace '&' with SglAndTok and replace '&&' with DblAndTok
								 "Paranth ) ", "Braces {  ", "Braces }  ", "Brackets [", // 24-27 all tokens starting from this line have incremented index from now on
								 "Brackets ]" ,"IfToken   ", "WhileToken", "INT-Token ", // 28-31
								 "WRITE-Toke", "ELSE-Token", "READ-Token"                // 32-35
	};

	signArray = new const char[SIGN_ARRAY_SZ] {'+', '-', '!', ';', '<', '>', '(', ')','{', '}', '[', ']'}; // remove '&' since its got replaced by '&&' , add '<' and '>'

	keywordsArray = new const char*[KEYWORD_NUMBER * 2] {"if", "IF", "while", "WHILE", "int", "INT", "write", "WRITE", "else", "ELSE", "read", "READ"};
}

Syntax::~Syntax() {
	delete[] stateTable;
	delete[] ttypeString;
	delete[] signArray;
	delete[] keywordsArray;
}

const char* Syntax::getTokenTypeAsChar(int num) {
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
int Syntax::ifKeyword(const char* lexem) {
	//int tType = 0;
	for (int i = 0; i < KEYWORD_NUMBER * 2; i++) {
		if (matches(lexem, keywordsArray[i]))
			return (STATES_NUMBER + i / 2);
	}
	return -1;
}

bool Syntax::matches(const char* one, const char* another) {
	const char* tmp1 = one;
	const char* tmp2 = another;
	while (tmp1[0] != '\0' || tmp2[0] != '\0') {
		if (tmp1++[0] != tmp2++[0]) {
			return false;
		}
	}
	return true;
}


