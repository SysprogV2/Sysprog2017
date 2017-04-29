/*
 * Syntax.h
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */

#ifndef AUTOMAT_INCLUDES_SYNTAX_H_
#define AUTOMAT_INCLUDES_SYNTAX_H_
#ifndef SIGN_ARRAY_SZ
#define SIGN_ARRAY_SZ 14
#endif
#define STATETABLE_WIDTH 18
#define STATETABLE_HEIGHT 10
#define KEYWORD_NUMBER 6
#define STATES_NUMBER STATETABLE_WIDTH +1 + STATETABLE_HEIGHT + 1 + 1

class Syntax {
	//  STRT_Z, IDEN_Z, INTG_Z,   COLN_Z, EQLS_Z, ASGN_Z, LCLN_Z, LCLL_Z, ASSG_Z, AND1_Z, AND2_Z,
	int **stateTable;
	const char **ttypeString;
	const char *signArray;

	const char **keywordsArray;

public:
	int keywordNumber;
	enum States {
		STRT_Z, IDEN_Z, INTG_Z, COLN_Z,
		EQLS_Z, ASGN_Z, LCLN_Z, LCLL_Z,
		ASSG_Z, AND1_Z, AND2_Z, EOF_Z,
		WSP_Z, MULT_Z, OPNC_Z, COMM_Z,
		CLSC_Z, PROH_Z, NULL_STATE, PLUS_Z,
		MIN_Z, NOT_Z, AND_Z, SEMI_Z,
		PARO_Z, PARC_Z, BRACO_Z, BRACC_Z,
		BRACKO_Z, BRACKC_Z, IF_Z, WHILE_Z,
		INTKEY_Z, WRITE_Z, ELSE_Z, READ_Z
	};
	enum Symbols {
		ANY_LETTER, ANY_DIGIT, MULT_SYMB, COLON_SYMB, EQUALS_SYMB, AND_SYMB, REST_SYMB,
		EOF_SYMB, WHITESPACE_SYMB, PROH_SYMB
	};

	Syntax();

	virtual ~Syntax();

	const char *getTokenTypeAsChar(int num);

	int getState(int i, int j);

	int isPacked(char sign);

	int ifKeyword(const char *lexem);

	bool matches(const char *one, const char *another);
};

#endif /* AUTOMAT_INCLUDES_SYNTAX_H_ */
