/*
 * Syntax.h
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#ifndef AUTOMAT_INCLUDES_SYNTAX_H_
#define AUTOMAT_INCLUDES_SYNTAX_H_
#define SIGN_ARRAY_SZ 14     
#define STATETABLE_WIDTH 18 
#define STATETABLE_HEIGHT 10
#define KEYWORD_NUMBER 6
#define STATES_NUMBER STATETABLE_WIDTH + STATETABLE_HEIGHT + 1
class Syntax {

	char *lexemDispStart;
	char *lexemDispIdent;
	char *lexemDispInteg;
	char *lexemDispColon;
	char *lexemDispEquals;
	char *lexemDispNotEqSign;
	char *lexemDispNotEqLeft;
	char *lexemDispNotEqFull;
	char *lexemDispAssign;
	char *lexemDispEof;
	char *lexemDispWhitespace;
	char *lexemDispMultipl;

	char *lexemDispCommentLeft;
	char *lexemDispCommentContent;
	char *lexemDispCommentRight;
	char *lexemDispProhibited;
	
	char *lexemDispNull;
	char *lexemDispPlus;
	char *lexemDispMinus;
	char *lexemDispNot;
	char *lexemDispSingleAnd;
	char *lexemDispDoubleAnd;	
	char *lexemDispSemicol;	
	char *lexemDispParantLeft;	
	char *lexemDispParantRight;	
	
	char *lexemDispBracesLeft;	
	char *lexemDispBracesRight;	
	char *lexemDispBracketsLeft;	
	char *lexemDispBracketsRight;	

	char *lexemDispTknIf;	
	char *lexemDispTknWhile;	
	char *lexemDispTknInt;	
	char *lexemDispTknWrite;	
	char *lexemDispTknElse;
	char *lexemDispTknRead;	
	

	char* ttypeString[STATES_NUMBER + KEYWORD_NUMBER];
	


	
	
	char *tokenIf      ;
	char *tokenIfCap   ;
	char *tokenWhile   ;
	char *tokenWhileCap;
	char *tokenInt     ;
	char *tokenIntCap  ;
	char *tokenWrite;
	char *tokenWriteCap;
	char *tokenElse    ;
	char *tokenElseCap ;
	char *tokenRead    ;
	char *tokenReadCap ;
	char signArray[SIGN_ARRAY_SZ]; // remove '&' since its got replaced by '&&' , add '<' and '>'
	int stateTable[STATETABLE_HEIGHT][STATETABLE_WIDTH];
	char* keywordsArray[KEYWORD_NUMBER * 2];
public:
	int keywordNumber;
	enum States {STRT_Z, IDEN_Z, INTG_Z, COLN_Z, EQLS_Z, ASGN_Z,
				 LCLN_Z, LCLL_Z, ASSG_Z, AND1_Z, AND2_Z, EOF_Z,
				 WSP_Z,  MULT_Z, OPNC_Z, COMM_Z,
				 CLSC_Z, PROH_Z, NULL_STATE, PLUS_Z,
				 MIN_Z,  NOT_Z,  AND_Z,  SEMI_Z,
				 PARO_Z, PARC_Z, BRACO_Z, BRACC_Z,
				 BRACKO_Z, BRACKC_Z, IF_Z, WHILE_Z,
				 INTKEY_Z, WRITE_Z, ELSE_Z, READ_Z
	};
	enum Symbols {ANY_LETTER, ANY_DIGIT, MULT_SYMB, COLON_SYMB, EQUALS_SYMB, AND_SYMB, REST_SYMB,
				  EOF_SYMB, WHITESPACE_SYMB, PROH_SYMB};
	Syntax();
	virtual ~Syntax();
	char* getTokenTypeAsChar(int num);
	int getState(int i, int j);

	int isPacked(char sign);
	int ifKeyword(char* lexem);
	bool matches(char* one, char* another);
};

#endif /* AUTOMAT_INCLUDES_SYNTAX_H_ */
