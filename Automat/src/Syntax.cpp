/*
 * Syntax.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#include "../includes/Syntax.h"

Syntax::Syntax() {
	keywordNumber = KEYWORD_NUMBER;
	tokenIf       = (char *) "if";
	tokenIfCap    = (char *) "IF";
	tokenWhile    = (char *) "while";
	tokenWhileCap = (char *) "WHILE";
	tokenInt      = (char *) "int";
	tokenIntCap   = (char *) "INT";
	tokenWrite	   = (char *) "write";
	tokenWriteCap = (char *) "WRITE";
	tokenElse     = (char *) "else";
	tokenElseCap  = (char *) "ELSE";
	tokenRead     = (char *) "read";
	tokenReadCap  = (char *) "READ";


	lexemDispStart = (char *) "Start";
	lexemDispIdent = (char *) "Identifier";
	lexemDispInteg = (char *) "Integer";
	lexemDispColon = (char *) "Colon";
	lexemDispEquals = (char *) "Equals";
	lexemDispNotEqSign = (char *) "=:=-sign";
	lexemDispNotEqLeft = (char *) "--=:--";
	lexemDispNotEqFull = (char *) "=:=";
	lexemDispAssign = (char *) "Assignment";
	lexemDispEof = (char *) "eof";
	lexemDispWhitespace = (char *) "Whitespace";
	lexemDispMultipl = (char *) "Multiplication";

	lexemDispCommentLeft = (char *) "Comment Start";
	lexemDispCommentContent = (char *) "Comment Content";
	lexemDispCommentRight = (char *) "Comment End";
	lexemDispProhibited = (char *) "Prohibited";
	
	lexemDispNull = (char *) "Null";
	lexemDispPlus = (char *) "Plus";
	lexemDispMinus = (char *) "Minus";
	lexemDispNot = (char *) "Not";
	lexemDispSingleAnd = (char *) "Single AND";
	lexemDispDoubleAnd = (char *) "Double AND";	
	lexemDispSemicol = (char *) "Semicolon";	
	lexemDispParantLeft = (char *) "Paranthesis Left";	
	lexemDispParantRight = (char *) "Parenthesis Right";	
	lexemDispBracesLeft = (char *) "Braces Left";	
	lexemDispBracesRight = (char *) "Braces Right";	
	lexemDispBracketsLeft = (char *) "Brackets Left";	
	lexemDispBracketsRight = (char *) "Bracket Right";	

	lexemDispTknIf = (char *) "Token If";	
	lexemDispTknWhile = (char *) "Token While";	
	lexemDispTknInt = (char *) "Token Int";	
	lexemDispTknWrite = (char *) "Token Write";	
	lexemDispTknElse = (char *) "Token Else";
	lexemDispTknRead = (char *) "Token Read";	


	char* ttypeString[STATES_NUMBER + KEYWORD_NUMBER] = {
							 lexemDispStart, lexemDispIdent, lexemDispInteg, lexemDispColon, //  0- 3
							 lexemDispEquals, lexemDispNotEqSign, lexemDispNotEqLeft, lexemDispNotEqFull, //  4- 7
							 lexemDispAssign, lexemDispEof, lexemDispWhitespace, lexemDispMultipl, //  8-11
							 lexemDispCommentLeft, lexemDispCommentContent, lexemDispCommentRight, lexemDispProhibited, // 12-15
							 lexemDispNull, lexemDispPlus, lexemDispMinus, lexemDispNot, // 16-19
							 lexemDispSingleAnd, lexemDispDoubleAnd,lexemDispSemicol, lexemDispParantLeft, // 20-23  replace '&' with SglAndTok and replace '&&' with DblAndTok
							 lexemDispParantRight, lexemDispBracesLeft, lexemDispBracesRight, lexemDispBracketsLeft, // 24-27 all tokens starting from this line have incremented index from now on
							 lexemDispBracketsRight ,lexemDispTknIf, lexemDispTknWhile, lexemDispTknInt, // 28-31
							 lexemDispTknWrite, lexemDispTknElse, lexemDispTknRead                // 32-35
	};
	(void) ttypeString; // suppress 'unused variable' warning
	char signArray[SIGN_ARRAY_SZ] = {'+', '-', '!', ';', '<', '>', '(', ')','{', '}', '[', ']'}; 
	(void) signArray; // suppress 'unused variable' warning
	int stateTable[STATETABLE_HEIGHT][STATETABLE_WIDTH] =  {
				/*            STRT    ID       INT	      :	     =	   <ANY>	  =:	 =:=	 :=      &      &&      Eof     WSP     *       :*   <comment>  *:    PROH_Z */
				/* a-Z */	{IDEN_Z, IDEN_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
				/* 0-9 */	{INTG_Z, IDEN_Z, INTG_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
				/*  *  */	{MULT_Z, STRT_Z, STRT_Z,   OPNC_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, COMM_Z, COMM_Z, STRT_Z, STRT_Z},
				/*  :  */ 	{COLN_Z, STRT_Z, STRT_Z,   STRT_Z, LCLN_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, CLSC_Z, STRT_Z, STRT_Z},
				/*  =  */ 	{EQLS_Z, STRT_Z, STRT_Z,   ASSG_Z, STRT_Z, STRT_Z, LCLL_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
	/*  added new	&  */   {AND1_Z, STRT_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, AND2_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
				/* RST */	{ASGN_Z, STRT_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
				/* EOF */	{EOF_Z,  STRT_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
				/* WSP */	{WSP_Z,  STRT_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  STRT_Z, STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
				/* PRH */	{PROH_Z, STRT_Z, STRT_Z,   STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z}
	};
	(void) stateTable;  // suppress 'unused variable' warning
	char* keywordsArray[KEYWORD_NUMBER * 2] = {tokenIf, tokenIfCap, tokenWhile, tokenWhileCap, tokenInt, tokenIntCap, tokenWrite, tokenWriteCap, tokenElse, tokenElseCap, tokenRead, tokenReadCap};
	(void) keywordsArray;  // suppress 'unused variable' warning
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
	//int tType = 0;  // suppress 'unused variable' warning
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


