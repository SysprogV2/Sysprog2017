/*
 * Syntax.h
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#ifndef AUTOMAT_INCLUDES_SYNTAX_H_
#define AUTOMAT_INCLUDES_SYNTAX_H_
#define SIGN_ARRAY_SZ 11
#define STATETABLE_WIDTH 18
#define STATETABLE_HEIGHT 11
#define KEYWORD_NUMBER 6
#define STATES_NUMBER STATETABLE_WIDTH + STATETABLE_HEIGHT + 1
class Syntax {

	int stateTable[STATETABLE_HEIGHT][STATETABLE_WIDTH] = {
				/*            STRT    ID       INT	  < 		>      :	   =	 <ANY>	   <:	  <:>	   :=      Eof     WSP     *       :*   <comment>  *:    PROH_Z */
				/* a-Z */	{IDEN_Z, IDEN_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
				/* 0-9 */	{INTG_Z, IDEN_Z, INTG_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
				/*  *  */	{MULT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, OPNC_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, COMM_Z, COMM_Z, STRT_Z, STRT_Z},
				/*  <  */ 	{LESS_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
				/*  >  */	{GREA_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, LCLL_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
				/*  :  */ 	{COLN_Z, STRT_Z, STRT_Z, LCLN_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, CLSC_Z, STRT_Z, STRT_Z},
				/*  =  */ 	{EQLS_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, ASSG_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
				/* RST */	{ASGN_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
				/* EOF */	{EOF_Z,  STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
				/* WSP */	{WSP_Z,  STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
				/* PRH */	{PROH_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z}
	};
	char* ttypeString[STATES_NUMBER + KEYWORD_NUMBER] = {
			(char *) "Start     ", (char *) "Identifier", (char *) "Integer   ", (char *) "Less      ", //  0- 3
			(char *) "Greater   ", (char *) "Colon     ", (char *) "Equals    ", (char *) "<:>-sign  ", //  4- 7
			(char *) "  --<:--  ", (char *) "<:>       ", (char *) "Assignment", (char *) " --eof--  ", //  8-11
			(char *) "Whitespace", (char *) "Multipl   ", (char *) "  --:*--  ", (char *) " --comm-- ", // 12-15
			(char *) "  --*:--  ", (char *) "Prohibited", (char *) " --null-- ", (char *) "PlusToken ", // 16-19
			(char *) "MinusToken", (char *) "NotToken  ", (char *) "AndToken  ", (char *) "SemicolTok", // 20-23
			(char *) "Paranth ( ", (char *) "Paranth ) ", (char *) "Braces {  ", (char *) "Braces }  ", // 24-27
			(char *) "Brackets [", (char *) "Brackets ]", (char *) "IfToken   ", (char *) "WhileToken", // 28-31
			(char *) "INT-Token ", (char *) "WRITE-Toke", (char *) "ELSE-Token", (char *) "READ-Token"  // 32-35
	};
	const char signArray[SIGN_ARRAY_SZ] = {'+', '-', '!', '&', ';', '(', ')','{', '}', '[', ']'};

	char* keywordsArray[KEYWORD_NUMBER * 2] = {(char *) "if", (char *) "IF", (char *) "while", (char *) "WHILE", (char *) "int", (char *) "INT", (char *) "write", (char *) "WRITE",
											   (char *) "else",
											   (char *) "ELSE",
											   (char *) "read",
											   (char *) "READ"};

public:
	int keywordNumber;
	enum States {STRT_Z, IDEN_Z, INTG_Z, LESS_Z,
				 GREA_Z, COLN_Z, EQLS_Z, ASGN_Z,
				 LCLN_Z, LCLL_Z, ASSG_Z, EOF_Z,
				 WSP_Z,  MULT_Z, OPNC_Z, COMM_Z,
				 CLSC_Z, PROH_Z, NULL_STATE, PLUS_Z,
				 MIN_Z,  NOT_Z,  AND_Z,  SEMI_Z,
				 PARO_Z, PARC_Z, BRACO_Z, BRACC_Z,
				 BRACKO_Z, BRACKC_Z, IF_Z, WHILE_Z,
				 INTKEY_Z, WRITE_Z, ELSE_Z, READ_Z
	};
	enum Symbols {ANY_LETTER, ANY_DIGIT, MULT_SYMB, LESS_SYMB,
	    		  GREATER_SYMB, COLON_SYMB, EQUALS_SYMB, REST_SYMB,
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
