/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include "../includes/Scanner.h"

#define CONV_ERR "error: cannot convert given CHAR* to LONG INT"
#define CONV_ERR_OVERFLOW "error: given integer is too big to be converted to LONG INT"

Scanner::Scanner(char *filename) {
	buffer = new Buffer(filename);
	automat = new Automat();
	syntax = new Syntax();
	stab = nullptr;
	cToken = nullptr;
	idenInt =  new TokenTypeRegistry();
	Token* idenToken = new Token(1, 0, 0);
	Token* intToken = new Token (2, 0, 0);
	idenInt->set(idenToken);
	idenInt->set(intToken);
	delete idenToken;
	delete intToken;
}

Scanner::Scanner(char *filename, Symboltable* st) {
	stab = st;
	buffer = new Buffer(filename);
	automat = new Automat();
	syntax = new Syntax();
	cToken = nullptr;
	idenInt =  new TokenTypeRegistry();
	Token* idenToken = new Token(1, 0, 0);
	Token* intToken = new Token (2, 0, 0);
	idenInt->set(idenToken);
	idenInt->set(intToken);
	delete idenToken;
	delete intToken;
}

Scanner::~Scanner() {
	delete buffer;
	delete automat;
	delete syntax;
	if (!this->idenInt->isSet(this->cToken)) delete this->cToken;
	delete this->idenInt;
}

/*
 * feeds characters to the automat, untill the new lexem is found.
 * Then tries to attribute it to some token.
 * @return current token
 */
Token *Scanner::nextToken() {
	std::cout << "debuging *** Scanner::nextToken STRT" << std::endl;

	char currentChar;
	int finalState = 0;

	std::cout << "debuging *** Scanner::nextToken DO-STRT" << std::endl;
	/* run automat and feed it char by char, till any lexem is found */
	do {
		currentChar = buffer->getChar();
		int back_steps = automat->read(currentChar);
		finalState = automat->getFinalState();
		buffer->ungetChar(back_steps);
		if (automat->isLexemReady() && (finalState == Syntax::WSP_Z || finalState == Syntax::CLSC_Z)) {
			automat->reset();
		}
	}while ( currentChar != '\0' &&  !automat->isLexemReady());
	std::cout << "debuging *** Scanner::nextToken DO-NED" << std::endl;

	/* save all information about the lexem */
	char* lexem = automat->getLexem();
	int lexemLength = automat->getLexemLength();
	int line = automat->getLine();
	int col = automat->getColumn();
	int tokenType = mapStateToType(finalState, lexem);

	/* create Token */
	Token* t = new Token(tokenType, line, col);

	/* add additional information to the token */
	Information* info;
	if (tokenType == Syntax::IDEN_Z) {
		info = stab->lookup(lexem);
		if (info == nullptr) {
			SymtabEntry* entry = stab->insert(lexem, lexemLength);
			info = entry->getInfo();
		}
		t->setInformation(info);
	} else {
		if (tokenType == Syntax::INTG_Z) {
			long int value = lexemToValue(lexem);
			t->setValue(value);
		} else if (tokenType == Syntax::PROH_Z) {
			t->setSymbol(lexem[0]);
		}
	}

	/* now we can reset automat */
	automat->reset();
	std::cout << "debuging *** Scanner::nextToken END" << std::endl;

	/* if we need to finish already*/
	if (currentChar == '\0') {
		return nullptr;
	} else {
		if (!this->idenInt->isSet(this->cToken)) delete this->cToken;
		this->cToken = t;
		return t;
	}
}

Token* Scanner::currentToken() {
	return this->cToken;
}

/*
 * determine the current token type relying on STATE and LEXEM
 * @return token's type
 */
int Scanner::mapStateToType(int state, char* lexem) {
	char symbol = lexem[0];
	int tType = state;
	if (state == Syntax::ASGN_Z) {
		tType = syntax->isPacked(symbol);
	} else if (state == Syntax::IDEN_Z) {
		int tmp = syntax->ifKeyword(lexem);
		if (tmp > 0) tType = tmp; // 30..35
	}
	return tType;
}

/*
 * converts a lexem to a its decimal value if it's possible
 * @return the value of a lexem if any
 */
long int Scanner::lexemToValue(char* lexem) {
	long int value = 0;
	char *pEnd;
	value = strtol(lexem, &pEnd, 10);
	if (errno == EINVAL) {
		std::cout << CONV_ERR << std::endl; // TODO actually throw the error
	} else if (errno == ERANGE) {
		std::cout << CONV_ERR_OVERFLOW << std::endl; // TODO actually throw the error
		errno = 0;
	}
	return value;
}
