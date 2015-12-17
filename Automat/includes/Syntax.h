/*
 * Syntax.h
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#ifndef AUTOMAT_INCLUDES_SYNTAX_H_
#define AUTOMAT_INCLUDES_SYNTAX_H_
#define SIGN_ARRAY_SZ 11
class Syntax {


	int stateTable[11][18] = {
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
					/* WSP */	{WSP_Z,  STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z,  STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z},
				    /* PRH */	{PROH_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, STRT_Z, EOF_Z,  STRT_Z, STRT_Z, OPNC_Z, OPNC_Z, STRT_Z, STRT_Z}
				    };
	const char signArray[SIGN_ARRAY_SZ] = {'+', '-', '!', '&', ';', '(', ')','{', '}', '[', ']'};
public:

	const char* ttypeStrinaSSga[30] =  {"Start     ", "Identifier", "Integer   ", "Less      ",
				"Greater   ", "Colon     ", "Equals    ", "<:>-sign  ",
				 "  --<:--  ", "<:>       ", "Assignment", " --eof--  ",
				 "Whitespace", "Multipl   ", "  --:*--  ", " --comm-- ",
				 "  --*:--  ", "Prohibited", " --null-- ", "Plus      ",
				 "Minus     ", "Not       ", "And       ", "Semicol   ",
				 "Paranth ( ", "Paranth ) ", "Braces {  ", "Braces }  ",
				 "Brackets [", "Brackets ]"
	};

	enum States {STRT_Z, IDEN_Z, INTG_Z, LESS_Z, GREA_Z, COLN_Z,
				 EQLS_Z, ASGN_Z, LCLN_Z, LCLL_Z, ASSG_Z, EOF_Z,
				 WSP_Z, MULT_Z, OPNC_Z, COMM_Z, CLSC_Z, PROH_Z,
				 NULL_STATE};
	enum Symbols {ANY_LETTER, ANY_DIGIT, MULT_SYMB, LESS_SYMB,
	    		  GREATER_SYMB, COLON_SYMB, EQUALS_SYMB, REST_SYMB,
				  EOF_SYMB, WHITESPACE_SYMB, PROH_SYMB};


	//const char* getTokenTypeAsChar(int num);
	int getState(int i, int j);
	bool isRest(char c);

	Syntax();
	virtual ~Syntax();
};





#endif /* AUTOMAT_INCLUDES_SYNTAX_H_ */
