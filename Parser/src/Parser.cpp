/*
 * Parser.cpp
 *
 *  Created on: 16.01.2016
 *      Author: work
 */

#include "../includes/Parser.h"

Parser::Parser(char* filename) {
	this->currentCodeSnippet = this->composeTable(filename);
	ParseTree::initStatic();
}

ParseTree* Parser::parse() {
	if (!ProgOnly::isMatching(this->currentCodeSnippet)) {
		throwError(INVALID_SEMANTICS);
		std::cout << "Wrong" <<std::endl;
	}
	// if it does match, the entire code (in the test file) is OK and all dynamic indexes the Parser must split the sequence on are in ParseTree::splitIndexes
	ProgOnly* prog = new ProgOnly();
	TokenSequence* statementPart = nullptr;
	TokenSequence* declarationPart = this->currentCodeSnippet->splitOn(ParseTree::splitIndexes->pop(), &statementPart);
	if (Decls::first()->isSet(this->currentCodeSnippet->tokenAt(0, false))) {
		prog->declarationSegment = new DeclsSeq();
		TokenSequence* singleDeclaration = nullptr;
		TokenSequence* rest0 = nullptr;
		TokenSequence* semicolon = nullptr;
		TokenSequence* otherDeclarations = nullptr;
		Decls* currentDecls = prog->declarationSegment;
		do {
			singleDeclaration = declarationPart->splitOn(ParseTree::splitIndexes->pop(), &rest0);
			semicolon = rest0->splitOn(0, &otherDeclarations);
			((DeclsSeq*) currentDecls)->firstDeclaration = new DeclOnly();
			this->buildDecl(&(((DeclsSeq*)currentDecls)->firstDeclaration), singleDeclaration);
			((DeclsSeq*) currentDecls)->restOfDeclarations = (otherDeclarations->getSize() == 0 ? ((Decls*)new DeclsSeq()) : ((Decls*)new DeclsEps()));
			delete singleDeclaration;
			delete rest0;
			delete semicolon;
			delete declarationPart;
			declarationPart = otherDeclarations;
			currentDecls = ((DeclsSeq*) currentDecls)->restOfDeclarations;
		} while(!currentDecls->isEps());
	} else {
		prog->declarationSegment = new DeclsEps();
	}
	if (statementPart->getSize() != 0) {
		prog->statementSegment = new StatementsSeq();
		TokenSequence* singleStatement = nullptr;
		TokenSequence* rest0 = nullptr;
		TokenSequence* semicolon = nullptr;
		TokenSequence* otherStatements = nullptr;
		Statements* currentStatements = prog->statementSegment;
		do {
			singleStatement = statementPart->splitOn(ParseTree::splitIndexes->pop(), &rest0);
			semicolon = rest0->splitOn(0, &otherStatements);
			this->buildStatement(&(((StatementsSeq*)currentStatements)->firstStatement), singleStatement);
			((StatementsSeq*) currentStatements)->restOfStatements = (otherStatements->getSize() == 0 ? ((Statements*)new StatementsSeq()) : ((Statements*)new StatementsEps()));
			delete singleStatement;
			delete rest0;
			delete semicolon;
			delete statementPart;
			statementPart = otherStatements;
			currentStatements = ((StatementsSeq*) currentStatements)->restOfStatements;
		} while(!currentStatements->isEps());
	} else {
		prog->statementSegment = new StatementsEps();
	}
	delete declarationPart;
	delete statementPart;
	return prog;
}

TokenSequence* Parser::composeTable(char* filename) {
	TokenSequence* sequence = new TokenSequence(10, 10);
	Token* singulum = nullptr;
	Symboltable* table = new Symboltable();
	Scanner* scanner = new Scanner(filename, table);
	bool sequel = true;
	do {
		singulum = scanner->nextToken();
		if (singulum != nullptr) {
			sequence->add(singulum, false);
		} else if (singulum->getType() == Syntax::PROH_Z){
			throwError(PROHIBITED_TOKEN);
		}
		sequel = (singulum != nullptr);
		delete singulum;
	} while(sequel);
	return sequence;
}

void Parser::buildDecl(Decl** toBuild, TokenSequence* relatedSequence) {
	TokenSequence* fullSuffix = nullptr;
	TokenSequence* prefixIntIdentifier = relatedSequence->splitOn(1, &fullSuffix);
	((DeclOnly*)(*toBuild))->identifier = prefixIntIdentifier->tokenAt(1, false);
	delete prefixIntIdentifier;
	if (fullSuffix->getSize() != 0) {
		((DeclOnly*)(*toBuild))->size = new ArrayIndex();
		((ArrayIndex*)((DeclOnly*)(*toBuild))->size)->integer = fullSuffix->tokenAt(1, false);
	} else {
		((DeclOnly*)(*toBuild))->size = new ArrayEps();
	}
	delete fullSuffix;
}

void Parser::buildStatement(Statement** toBuild, TokenSequence* relatedSequence) {
	if (StatementSetValue::first()->isSet(relatedSequence->tokenAt(0, false))) {
		*toBuild = new StatementSetValue();
		((StatementSetValue*)(*toBuild))->identifier = relatedSequence->tokenAt(0, false);
		TokenSequence* exceptIdentifier = nullptr;
		TokenSequence* isolatedIdentifier = relatedSequence->splitOn(0, &exceptIdentifier);
		delete isolatedIdentifier;
		TokenSequence* assigningCore = nullptr;
		TokenSequence* indexPart = exceptIdentifier->splitOn(ParseTree::splitIndexes->pop(), &assigningCore);
		delete exceptIdentifier;
		((StatementSetValue*)(*toBuild))->index = this->buildIndex(indexPart);
		delete indexPart;
		TokenSequence* expression = nullptr;
		TokenSequence* assignment = assigningCore->splitOn(0, &expression);
		delete assigningCore;
		delete assignment;
		((StatementSetValue*)(*toBuild))->aimValue = this->buildExp(expression);
		delete expression;
	} else if (StatementWrite::first()->isSet(relatedSequence->tokenAt(0, false))) {
		*toBuild = new StatementWrite();
		TokenSequence* exp = nullptr;
		TokenSequence* preExp = relatedSequence->splitOn(1, &exp);
		TokenSequence* postExp = nullptr;
		TokenSequence* actualExp = exp->splitOn(exp->getSize() - 2, &postExp);
		((StatementWrite*)(*toBuild))->toPrint = this->buildExp(actualExp);
		delete exp;
		delete actualExp;
		delete preExp;
		delete postExp;
	} else if (StatementRead::first()->isSet(relatedSequence->tokenAt(0, false))) {
		*toBuild = new StatementRead();
		TokenSequence* sub = nullptr;
		TokenSequence* post = nullptr;
		TokenSequence* pre = relatedSequence->splitOn(2, &sub);
		TokenSequence* core = sub->splitOn(sub->getSize()-2, &post);
		((StatementRead*)(*toBuild))->identifier = pre->tokenAt(2, false);
		((StatementRead*)(*toBuild))->index = this->buildIndex(core);
		delete sub;
		delete pre;
		delete core;
		delete post;
	} else if (StatementBlock::first()->isSet(relatedSequence->tokenAt(0, false))) {
		*toBuild = new StatementBlock();
		TokenSequence* subcore0 = nullptr;
		TokenSequence* preBrace = relatedSequence->splitOn(0, &subcore0);
		delete preBrace;
		TokenSequence* postBrace = nullptr;
		TokenSequence* statementCore = subcore0->splitOn(subcore0->getSize() - 2, &postBrace);
		Statements* currentStatements = ((StatementBlock*)(*toBuild))->blockContent;
		if (statementCore->getSize() != 0) {
			currentStatements = new StatementsSeq();
			TokenSequence* singleStatement = nullptr;
			TokenSequence* rest0 = nullptr;
			TokenSequence* semicolon = nullptr;
			TokenSequence* otherStatements = nullptr;
			do {
				singleStatement = statementCore->splitOn(ParseTree::splitIndexes->pop(), &rest0);
				semicolon = rest0->splitOn(0, &otherStatements);
				this->buildStatement(&(((StatementsSeq*)currentStatements)->firstStatement), singleStatement);
				((StatementsSeq*) currentStatements)->restOfStatements = (otherStatements->getSize() == 0 ? ((Statements*)new StatementsSeq()) : ((Statements*)new StatementsEps()));
				delete singleStatement;
				delete rest0;
				delete semicolon;
				delete statementCore;
				statementCore = otherStatements;
				currentStatements = ((StatementsSeq*) currentStatements)->restOfStatements;
			} while(!currentStatements->isEps());
		} else {
			currentStatements = new StatementsEps();
		}
	} else if (StatementIfElse::first()->isSet(relatedSequence->tokenAt(0, false))) {
		*toBuild = new StatementIfElse();
		TokenSequence* majorPrefix = nullptr;
		TokenSequence* elseStatement = nullptr;
		TokenSequence* elsePart = nullptr;
		TokenSequence* ifAndItsStatement = nullptr;
		TokenSequence* ifPart = nullptr;
		TokenSequence* semiCore = nullptr;
		TokenSequence* ifExpression = nullptr;
		TokenSequence* endOfIf = nullptr;
		TokenSequence* core = nullptr;
		TokenSequence* ifStatement = nullptr;
		majorPrefix = relatedSequence->splitOn(ParseTree::splitIndexes->pop(), &elseStatement);
		this->buildStatement(&(((StatementIfElse*)(*toBuild))->elseCase), elseStatement);
		delete elseStatement;
		ifAndItsStatement = majorPrefix->splitOn(majorPrefix->getSize() - 3, &elsePart);
		delete majorPrefix;
		delete elsePart;
		ifPart = ifAndItsStatement->splitOn(1, &semiCore);
		delete ifAndItsStatement;
		delete ifPart;
		ifExpression = semiCore->splitOn(ParseTree::splitIndexes->pop(), &endOfIf);
		((StatementIfElse*)(*toBuild))->condition = this->buildExp(ifExpression);
		delete ifExpression;
		delete semiCore;
		core = endOfIf->splitOn(0, &ifStatement);
		delete core;
		delete endOfIf;
		this->buildStatement(&(((StatementIfElse*)(*toBuild))->thenCase), ifStatement);
		delete ifStatement;
	} else if (StatementWhile::first()->isSet(relatedSequence->tokenAt(0, false))) {
		*toBuild = new StatementWhile();
		TokenSequence* remainings = nullptr;
		TokenSequence* whileBeginning = relatedSequence->splitOn(1, &remainings);
		delete whileBeginning;
		TokenSequence* parStat = nullptr;
		TokenSequence* exp = remainings->splitOn(ParseTree::splitIndexes->pop(), &parStat);
		TokenSequence* statement = nullptr;
		TokenSequence* paranth = parStat->splitOn(0, &statement);
		((StatementWhile*)(*toBuild))->condition = this->buildExp(exp);
		this->buildStatement(&(((StatementWhile*)(*toBuild))->loop), statement);
	}
}

Index* Parser::buildIndex(TokenSequence* related) {
	Index* toBuild = nullptr;
	if (related->getSize() != 0) {
		toBuild = new IndexPosition();
		TokenSequence* end = nullptr;
		TokenSequence* beginBracket = related->splitOn(0, &end);
		delete beginBracket;
		TokenSequence* endBracket = nullptr;
		TokenSequence* subexp = end->splitOn(end->getSize() - 2, &endBracket);
		delete end;
		delete endBracket;
		((IndexPosition*) toBuild)->index = this->buildExp(subexp);
		delete subexp;
	} else {
		toBuild = new IndexEps();
	}
	return toBuild;
}

Exp* Parser::buildExp(TokenSequence* related) {
	ExpOnly* toBuild = new ExpOnly();
	TokenSequence* operatingUnit = nullptr;
	TokenSequence* firstExp = related->splitOn(ParseTree::splitIndexes->pop(), &operatingUnit);
	toBuild->rawExpression = this->buildExp2(firstExp);
	if (operatingUnit->getSize() != 0) {
		toBuild->calculateWith = new OpExpNext();
		const int optypePlus = 19;
		const int optypeMinus = 20;
		const int optypeMult = 13;
		const int optypeDiv = 5;
		const int optypeLess = 3;
		const int optypeGreater = 4;
		const int optypeEquals = 6;
		const int optypeNotEquals = 7;
		const int optypeAnd = 22;
		switch (operatingUnit->tokenAt(0, false)->getType()) {
		case optypePlus:
			((OpExpNext*)(toBuild->calculateWith))->Operator = new OpPlus();
			break;
		case optypeMinus:
			((OpExpNext*)(toBuild->calculateWith))->Operator = new OpMinus();
			break;
		case optypeMult:
			((OpExpNext*)(toBuild->calculateWith))->Operator = new OpMult();
			break;
		case optypeDiv:
			((OpExpNext*)(toBuild->calculateWith))->Operator = new OpDiv();
			break;
		case optypeLess:
			((OpExpNext*)(toBuild->calculateWith))->Operator = new OpLess();
			break;
		case optypeGreater:
			((OpExpNext*)(toBuild->calculateWith))->Operator = new OpGreater();
			break;
		case optypeEquals:
			((OpExpNext*)(toBuild->calculateWith))->Operator = new OpEquals();
			break;
		case optypeNotEquals:
			((OpExpNext*)(toBuild->calculateWith))->Operator = new OpNotEquals();
			break;
		case optypeAnd:
			((OpExpNext*)(toBuild->calculateWith))->Operator = new OpAnd();
			break;
		}
		TokenSequence* nextExp = nullptr;
		TokenSequence* builtOperator = related->splitOn(0, &nextExp);
		delete builtOperator;
		((OpExpNext*)(toBuild->calculateWith))->operand = this->buildExp(nextExp);
	} else {
		toBuild->calculateWith = new OpExpEps();
	}
	return toBuild;
}

Exp2* Parser::buildExp2(TokenSequence* related) {
	Exp2* toBuild = nullptr;
	if (Exp2Nested::first()->isSet(related->tokenAt(0, false))) {
		toBuild = new Exp2Nested();
		TokenSequence* end = nullptr;
		TokenSequence* beginParanth = related->splitOn(0, &end);
		TokenSequence* endParanth = nullptr;
		TokenSequence* subexp = end->splitOn(end->getSize() - 2, &endParanth);
		delete end;
		delete beginParanth;
		delete endParanth;
		((Exp2Nested*)(toBuild))->nestedExpression = this->buildExp(subexp);
		delete subexp;
	} else if (Exp2Variable::first()->isSet(related->tokenAt(0, false))) {
		toBuild = new Exp2Variable();
		((Exp2Variable*)(toBuild))->identifier = related->tokenAt(0, false);
		TokenSequence* readingPos = nullptr;
		TokenSequence* precedingIdentifier = related->splitOn(0, &readingPos);
		delete precedingIdentifier;
		((Exp2Variable*)(toBuild))->index = this->buildIndex(readingPos);
		delete readingPos;
	} else if (Exp2Constant::first()->isSet(related->tokenAt(0, false))) {
		toBuild = new Exp2Constant();
		((Exp2Constant*)(toBuild))->integer = related->tokenAt(0, false);
	} else if (Exp2NumericNegation::first()->isSet(related->tokenAt(0, false))) {
		toBuild = new Exp2NumericNegation();
		TokenSequence* negated = nullptr;
		TokenSequence* negMinus = related->splitOn(0, &negated);
		delete negMinus;
		((Exp2NumericNegation*) toBuild)->toNegate = this->buildExp2(negated);
	} else if (Exp2LogicalNegation::first()->isSet(related->tokenAt(0, false))){
		toBuild = new Exp2LogicalNegation();
		TokenSequence* negated = nullptr;
		TokenSequence* negExcl = related->splitOn(0, &negated);
		delete negExcl;
		((Exp2NumericNegation*) toBuild)->toNegate = this->buildExp2(negated);
	}
	return toBuild;
}

Parser::~Parser() {
	delete this->currentCodeSnippet;
	// clean up all static ParseTree members (only the Parser ever calls first() and isMatching())
	delete ParseTree::bracketsToken;
	delete ParseTree::epsToken;
	delete ParseTree::identifierToken;
	delete ParseTree::integerToken;
	delete ParseTree::minusToken;
	delete ParseTree::splitIndexes;
	delete DeclOnly::firstToken;
	delete StatementWrite::firstToken;
	delete StatementRead::firstToken;
	delete StatementBlock::firstToken;
	delete StatementIfElse::firstToken;
	delete StatementWhile::firstToken;
	delete Exp2Nested::firstToken;
	delete Exp2LogicalNegation::firstToken;
	delete OpPlus::firstToken;
	delete OpMult::firstToken;
	delete OpDiv::firstToken;
	delete OpLess::firstToken;
	delete OpGreater::firstToken;
	delete OpEquals::firstToken;
	delete OpNotEquals::firstToken;
	delete OpAnd::firstToken;
}
