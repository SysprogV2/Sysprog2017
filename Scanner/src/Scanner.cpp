/*
 * Scanner.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include "../includes/Scanner.h"

#define CONV_ERR "error: cannot convert given CHAR* to LONG INT"
#define CONV_ERR_OVERFLOW "error: given integer is too big to be converted to LONG INT"
// TODO: use somewhere

Scanner::Scanner(const char *filename): Scanner(filename, new Symboltable()) {
}

Scanner::Scanner(const char *filename, Symboltable *st) {
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
	if (!this->idenInt->isSet(this->cToken)) {
        delete this->cToken;
    }
	delete this->idenInt;
}

/*
 * feeds characters to the automat, until the new lexem is found.
 * Then tries to attribute it to some token.
 * @return current token
 */
Token *Scanner::nextToken() {
	//std::cout << "debuging *** Scanner::nextToken STRT" << std::endl;

	char currentChar;
	int finalState = 0;

	/* run automat and feed it char by char, till any lexem is found */
	if (buffer->isEnd()) {
		this->cToken = new Token(11, automat->getLine(), automat->getColumn());
		return this->cToken;
	}

	do {
		currentChar = buffer->getChar();
		int back_steps = automat->read(currentChar);
		finalState = automat->getFinalState();
		buffer->ungetChar(back_steps);
		if (automat->isLexemReady() && (finalState == Syntax::WSP_Z || finalState == Syntax::CLSC_Z)) {
			automat->reset();
		}
	} while (!buffer->isEnd() && currentChar != '\0' &&  !automat->isLexemReady());

	/* save all information about the lexem */
	const char* lexem = automat->getLexem();
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
	} else if (tokenType == Syntax::AND1_Z || tokenType == Syntax::PROH_Z) {
		t->setType(Syntax::PROH_Z);
		t->setErrorMessage((char *) "unknown token");
		t->setSymbol(lexem[0]);
	} else if (tokenType == Syntax::INTG_Z) {
		getNumberToken(lexem, t);
	}

	/* now we can reset automat */
	automat->reset();

	/* if we need to finish already*/
	if (currentChar == '\0') {
		return new Token(11, line, col);
	} else {
        // free cached Token (if existant) unless it's stored in the tree
		if (this->cToken != nullptr && !this->idenInt->isSet(this->cToken)) {
            delete this->cToken;
        }
        // cache generated Token
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
int Scanner::mapStateToType(int state, const char *lexem) {
    char symbol = lexem[0];
    int tType = state;
    if (state == Syntax::ASGN_Z) {
        tType = syntax->isPacked(symbol);
    } else if (state == Syntax::IDEN_Z) {
        int tmp = syntax->ifKeyword(lexem);
        if (tmp > 0) tType = tmp;  // 30..35
    }
    return tType;
}

/*
 * assigns a decimal value of given char pointer to given token
 * @return void
 */
void Scanner::getNumberToken(const char* lexem, Token* t) {
	errno = 0;
	long int value = strtol(lexem, 0, 10);
	if (errno == ERANGE) {
		t->setType(Syntax::PROH_Z);
		t->setErrorMessage((char *) "error: given integer is too big to be converted to LONG INT");
		t->setSymbol(nullptr);
		errno = 0;
	} else {
		t->setValue(value);
	}
	
}