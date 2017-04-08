/*
 * Syntax.h
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#ifndef AUTOMAT_INCLUDES_SYNTAX_H_
#define AUTOMAT_INCLUDES_SYNTAX_H_
#define SIGN_ARRAY_SZ 14     // we removed one char from @signArray (see below), we added 2 chars '<' and '>'
#define STATETABLE_WIDTH 18  // we added 2 new states for compounded token &&: '&' and '&&'
#define STATETABLE_HEIGHT 10 // we added one char '&' to table to look for compounded t0ken '&&', we removed '<' and '>'
#define KEYWORD_NUMBER 6
#define STATES_NUMBER STATETABLE_WIDTH + STATETABLE_HEIGHT + 1
class Syntax {
						 //  STRT_Z, IDEN_Z, INTG_Z,   COLN_Z, EQLS_Z, ASGN_Z, LCLN_Z, LCLL_Z, ASSG_Z, AND1_Z, AND2_Z,	
	int stateTable[STATETABLE_HEIGHT][STATETABLE_WIDTH] = {									// two new states  ->   /--------------\	
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
	};//+sdf&eileen
	char* ttypeString[STATES_NUMBER + KEYWORD_NUMBER] = {
							 "Start     ", "Identifier", "Integer   ", //  0- 3
							 "Colon     ", "Equals    ", "=:=-sign  ", //  4- 7
							 "  --=:--  ", "=:=       ", "Assignment", " --eof--  ", //  8-11
							 "Whitespace", "Multipl   ", "  --:*--  ", " --comm-- ", // 12-15
							 "  --*:--  ", "Prohibited", " --null-- ", "PlusToken ", // 16-19
							 "MinusToken", "NotToken  ", "SglAndTok ", "DblAndTok ", // 20-23  replace '&' with SglAndTok and replace '&&' with DblAndTok
							 "SemicolTok", "Paranth ( ", "Paranth ) ", "Braces {  ", // 24-27 all tokens starting from this line have incremented index from now on
							 "Braces }  ", "Brackets [", "Brackets ]" ,"IfToken   ", // 28-31
							 "WhileToken", "INT-Token ", "WRITE-Toke", "ELSE-Token", // 32-35
							 "READ-Token" 
	};
	const char signArray[SIGN_ARRAY_SZ] = {'+', '-', '!', ';', '<', '>', '(', ')','{', '}', '[', ']'}; // remove '&' since its got replaced by '&&' , add '<' and '>'
		// and doesnt belogn to the set of _single chars_

	char* keywordsArray[KEYWORD_NUMBER * 2] = {"if", "IF", "while", "WHILE", "int", "INT", "write", "WRITE", "else", "ELSE", "read", "READ"};

public:
	int keywordNumber;
	enum States {STRT_Z, IDEN_Z, INTG_Z, COLN_Z, EQLS_Z, ASGN_Z,
				 LCLN_Z, LCLL_Z, ASSG_Z, 
				 AND1_Z, AND2_Z,				       // add two states for '&' and '&&'
				 EOF_Z,
				 WSP_Z,  MULT_Z, OPNC_Z, COMM_Z,
				 CLSC_Z, PROH_Z, NULL_STATE, PLUS_Z,
				 MIN_Z,  NOT_Z,  AND_Z,  SEMI_Z,
				 PARO_Z, PARC_Z, BRACO_Z, BRACC_Z,
				 BRACKO_Z, BRACKC_Z, IF_Z, WHILE_Z,
				 INTKEY_Z, WRITE_Z, ELSE_Z, READ_Z
	};
	enum Symbols {ANY_LETTER, ANY_DIGIT, MULT_SYMB, COLON_SYMB, EQUALS_SYMB, AND_SYMB, REST_SYMB,  // add AND_SYMB ('&') since it's part of a compound '&&' token, remove '<' and '>' symbols
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
