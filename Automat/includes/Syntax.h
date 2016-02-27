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
							 "Start     ", "Identifier", "Integer   ", "Less      ", //  0- 3
							 "Greater   ", "Colon     ", "Equals    ", "<:>-sign  ", //  4- 7
							 "  --<:--  ", "<:>       ", "Assignment", " --eof--  ", //  8-11
							 "Whitespace", "Multipl   ", "  --:*--  ", " --comm-- ", // 12-15
							 "  --*:--  ", "Prohibited", " --null-- ", "PlusToken ", // 16-19
							 "MinusToken", "NotToken  ", "AndToken  ", "SemicolTok", // 20-23
							 "Paranth ( ", "Paranth ) ", "Braces {  ", "Braces }  ", // 24-27
							 "Brackets [", "Brackets ]" ,"IfToken   ", "WhileToken", // 28-31
							 "INT-Token ", "WRITE-Toke", "ELSE-Token", "READ-Token"  // 32-35
	};
	const char signArray[SIGN_ARRAY_SZ] = {'+', '-', '!', '&', ';', '(', ')','{', '}', '[', ']'};

	char* keywordsArray[KEYWORD_NUMBER * 2] = {"if", "IF", "while", "WHILE", "int", "INT", "write", "WRITE", "else", "ELSE", "read", "READ"};

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
