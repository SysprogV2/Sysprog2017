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
	if (this->currentCodeSnippet == nullptr) {
		throw "Undefined file for parser\n";
	}
	if (!ProgOnly::isMatching(this->currentCodeSnippet)) {
		std::cerr << "error some spot: syntax error type 2 (invalid token composition)\n";
		exit(1);
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
			if (singleDeclaration != nullptr) {
				singleDeclaration->prepareDelete(true);
				delete singleDeclaration;
			}
			if (rest0 != nullptr) {
				rest0->prepareDelete(true);
				delete rest0;
			}
			if (semicolon != nullptr) {
				semicolon->prepareDelete(true);
				delete semicolon;
			}
			if (declarationPart != nullptr) {
				declarationPart->prepareDelete(true);
				delete declarationPart;
			}
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
			if (singleStatement != nullptr) {
				singleStatement->prepareDelete(true);
				delete singleStatement;
			}
			if (rest0 != nullptr) {
				rest0->prepareDelete(true);
				delete rest0;
			}
			if (semicolon != nullptr) {
				semicolon->prepareDelete(true);
				delete semicolon;
			}
			if (statementPart != nullptr) {
				statementPart->prepareDelete(true);
				delete statementPart;
			}
			statementPart = otherStatements;
			currentStatements = ((StatementsSeq*) currentStatements)->restOfStatements;
		} while(!currentStatements->isEps());
	} else {
		prog->statementSegment = new StatementsEps();
	}
	if (declarationPart != nullptr) {
		declarationPart->prepareDelete(true);
		delete declarationPart;
	}
	if (statementPart != nullptr) {
		statementPart->prepareDelete(true);
		delete statementPart;
	}
	std::cout << "Parsing works\n";
	return prog;
}

TokenSequence* Parser::composeTable(char* filename) {
	TokenSequence* sequence = new TokenSequence(10, 10);
	Token* singulum = nullptr;
	Symboltable* table = new Symboltable();
	Scanner* scanner = new Scanner(filename, table);
	std::cout << "Initialization works\n";
	do {
		std::cout << "debuging *** Parser::composeTable DO-STRT" << std::endl;
		singulum = scanner->nextToken();
		if (singulum != nullptr) {
			if (singulum->getType() == Syntax::PROH_Z) {
				std::cerr << "error line " << singulum->getLine() << " column " << singulum->getColumn() << ": syntax error type 1 (unsupported token)\n";
				exit(1);
			}
			std::cout << "crashing?\n";
			sequence->add(singulum, false);
		}
		std::cout << "debuging *** Parser::composeTable DO-END" << std::endl;
	} while(singulum != nullptr);
	std::cout << "Scanning works\n";
	return sequence;
}

void Parser::buildDecl(Decl** toBuild, TokenSequence* relatedSequence) {
	TokenSequence* fullSuffix = nullptr;
	TokenSequence* prefixIntIdentifier = relatedSequence->splitOn(1, &fullSuffix);
	((DeclOnly*)(*toBuild))->identifier = prefixIntIdentifier->tokenAt(1, false);
	if (prefixIntIdentifier != nullptr) {
		prefixIntIdentifier->prepareDelete(true);
		delete prefixIntIdentifier;
	}
	if (fullSuffix->getSize() != 0) {
		((DeclOnly*)(*toBuild))->size = new ArrayIndex();
		((ArrayIndex*)((DeclOnly*)(*toBuild))->size)->integer = fullSuffix->tokenAt(1, false);
	} else {
		((DeclOnly*)(*toBuild))->size = new ArrayEps();
	}
	if (fullSuffix != nullptr) {
		fullSuffix->prepareDelete(true);
		delete fullSuffix;
	}
}

void Parser::buildStatement(Statement** toBuild, TokenSequence* relatedSequence) {
	if (StatementSetValue::first()->isSet(relatedSequence->tokenAt(0, false))) {
		*toBuild = new StatementSetValue();
		((StatementSetValue*)(*toBuild))->identifier = relatedSequence->tokenAt(0, false);
		TokenSequence* exceptIdentifier = nullptr;
		TokenSequence* isolatedIdentifier = relatedSequence->splitOn(0, &exceptIdentifier);
		if (isolatedIdentifier != nullptr) {
			isolatedIdentifier->prepareDelete(true);
			delete isolatedIdentifier;
		}
		TokenSequence* assigningCore = nullptr;
		TokenSequence* indexPart = exceptIdentifier->splitOn(ParseTree::splitIndexes->pop(), &assigningCore);
		if (exceptIdentifier != nullptr) {
			exceptIdentifier->prepareDelete(true);
			delete exceptIdentifier;
		}
		((StatementSetValue*)(*toBuild))->index = this->buildIndex(indexPart);
		if (indexPart != nullptr) {
			indexPart->prepareDelete(true);
			delete indexPart;
		}
		TokenSequence* expression = nullptr;
		TokenSequence* assignment = assigningCore->splitOn(0, &expression);
		if (assigningCore != nullptr) {
			assigningCore->prepareDelete(true);
			delete assigningCore;
		}
		if (assignment != nullptr) {
			assignment->prepareDelete(true);
			delete assignment;
		}
		((StatementSetValue*)(*toBuild))->aimValue = this->buildExp(expression);
		if (expression != nullptr) {
			expression->prepareDelete(true);
			delete expression;
		}
	} else if (StatementWrite::first()->isSet(relatedSequence->tokenAt(0, false))) {
		*toBuild = new StatementWrite();
		TokenSequence* exp = nullptr;
		TokenSequence* preExp = relatedSequence->splitOn(1, &exp);
		TokenSequence* postExp = nullptr;
		TokenSequence* actualExp = exp->splitOn(exp->getSize() - 2, &postExp);
		((StatementWrite*)(*toBuild))->toPrint = this->buildExp(actualExp);
		if (exp != nullptr) {
			exp->prepareDelete(true);
			delete exp;
		}
		if (actualExp != nullptr) {
			actualExp->prepareDelete(true);
			delete actualExp;
		}
		if (preExp != nullptr) {
			preExp->prepareDelete(true);
			delete preExp;
		}
		if (postExp != nullptr) {
			postExp->prepareDelete(true);
			delete postExp;
		}
	} else if (StatementRead::first()->isSet(relatedSequence->tokenAt(0, false))) {
		*toBuild = new StatementRead();
		TokenSequence* sub = nullptr;
		TokenSequence* post = nullptr;
		TokenSequence* pre = relatedSequence->splitOn(2, &sub);
		TokenSequence* core = sub->splitOn(sub->getSize()-2, &post);
		((StatementRead*)(*toBuild))->identifier = pre->tokenAt(2, false);
		((StatementRead*)(*toBuild))->index = this->buildIndex(core);
		if (sub != nullptr) {
			sub->prepareDelete(true);
			delete sub;
		}
		if (pre != nullptr) {
			pre->prepareDelete(true);
			delete pre;
		}
		if (core != nullptr) {
			core->prepareDelete(true);
			delete core;
		}
		if (post != nullptr) {
			post->prepareDelete(true);
			delete post;
		}
	} else if (StatementBlock::first()->isSet(relatedSequence->tokenAt(0, false))) {
		*toBuild = new StatementBlock();
		TokenSequence* subcore0 = nullptr;
		TokenSequence* preBrace = relatedSequence->splitOn(0, &subcore0);
		if (preBrace != nullptr) {
			preBrace->prepareDelete(true);
			delete preBrace;
		}
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
				if (singleStatement != nullptr) {
					singleStatement->prepareDelete(true);
					delete singleStatement;
				}
				if (rest0 != nullptr) {
					rest0->prepareDelete(true);
					delete rest0;
				}
				if (semicolon != nullptr) {
					semicolon->prepareDelete(true);
					delete semicolon;
				}
				if (statementCore != nullptr) {
					statementCore->prepareDelete(true);
					delete statementCore;
				}
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
		if (elseStatement != nullptr) {
			elseStatement->prepareDelete(true);
			delete elseStatement;
		}
		ifAndItsStatement = majorPrefix->splitOn(majorPrefix->getSize() - 3, &elsePart);
		if (majorPrefix != nullptr) {
			majorPrefix->prepareDelete(true);
			delete majorPrefix;
		}
		if (elsePart != nullptr) {
			elsePart->prepareDelete(true);
			delete elsePart;
		}
		ifPart = ifAndItsStatement->splitOn(1, &semiCore);
		if (ifAndItsStatement != nullptr) {
			ifAndItsStatement->prepareDelete(true);
			delete ifAndItsStatement;
		}
		if (ifPart != nullptr) {
			ifPart->prepareDelete(true);
			delete ifPart;
		}
		ifExpression = semiCore->splitOn(ParseTree::splitIndexes->pop(), &endOfIf);
		((StatementIfElse*)(*toBuild))->condition = this->buildExp(ifExpression);
		if (ifExpression != nullptr) {
			ifExpression->prepareDelete(true);
			delete ifExpression;
		}
		if (semiCore != nullptr) {
			semiCore->prepareDelete(true);
			delete semiCore;
		}
		core = endOfIf->splitOn(0, &ifStatement);
		if (core != nullptr) {
			core->prepareDelete(true);
			delete core;
		}
		if (endOfIf != nullptr) {
			endOfIf->prepareDelete(true);
			delete endOfIf;
		}
		this->buildStatement(&(((StatementIfElse*)(*toBuild))->thenCase), ifStatement);
		if (ifStatement != nullptr) {
			ifStatement->prepareDelete(true);
			delete ifStatement;
		}
	} else if (StatementWhile::first()->isSet(relatedSequence->tokenAt(0, false))) {
		*toBuild = new StatementWhile();
		TokenSequence* remainings = nullptr;
		TokenSequence* whileBeginning = relatedSequence->splitOn(1, &remainings);
		if (whileBeginning != nullptr) {
			whileBeginning->prepareDelete(true);
			delete whileBeginning;
		}
		TokenSequence* parStat = nullptr;
		TokenSequence* exp = remainings->splitOn(ParseTree::splitIndexes->pop(), &parStat);
		TokenSequence* statement = nullptr;
		TokenSequence* paranth = parStat->splitOn(0, &statement);
		if (paranth != nullptr) {
			paranth->prepareDelete(true);
			delete paranth;
		}
		((StatementWhile*)(*toBuild))->condition = this->buildExp(exp);
		this->buildStatement(&(((StatementWhile*)(*toBuild))->loop), statement);
		if (exp != nullptr) {
			exp->prepareDelete(true);
			delete exp;
		}
		if (statement != nullptr) {
			statement->prepareDelete(true);
			delete statement;
		}
	}
}

Index* Parser::buildIndex(TokenSequence* related) {
	Index* toBuild = nullptr;
	if (related->getSize() != 0) {
		toBuild = new IndexPosition();
		TokenSequence* end = nullptr;
		TokenSequence* beginBracket = related->splitOn(0, &end);
		if (beginBracket != nullptr) {
			beginBracket->prepareDelete(true);
			delete beginBracket;
		}
		TokenSequence* endBracket = nullptr;
		TokenSequence* subexp = end->splitOn(end->getSize() - 2, &endBracket);
		if (end != nullptr) {
			end->prepareDelete(true);
			delete end;
		}
		if (endBracket != nullptr) {
			endBracket->prepareDelete(true);
			delete endBracket;
		}
		((IndexPosition*) toBuild)->index = this->buildExp(subexp);
		if (subexp != nullptr) {
			subexp->prepareDelete(true);
			delete subexp;
		}
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
		if (builtOperator != nullptr) {
			builtOperator->prepareDelete(true);
			delete builtOperator;
		}
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
		if (end != nullptr) {
			end->prepareDelete(true);
			delete end;
		}
		if (beginParanth != nullptr) {
			beginParanth->prepareDelete(true);
			delete beginParanth;
		}
		if (endParanth != nullptr) {
			endParanth->prepareDelete(true);
			delete endParanth;
		}
		((Exp2Nested*)(toBuild))->nestedExpression = this->buildExp(subexp);
		if (subexp != nullptr) {
			subexp->prepareDelete(true);
			delete subexp;
		}
	} else if (Exp2Variable::first()->isSet(related->tokenAt(0, false))) {
		toBuild = new Exp2Variable();
		((Exp2Variable*)(toBuild))->identifier = related->tokenAt(0, false);
		TokenSequence* readingPos = nullptr;
		TokenSequence* precedingIdentifier = related->splitOn(0, &readingPos);
		if (precedingIdentifier != nullptr) {
			precedingIdentifier->prepareDelete(true);
			delete precedingIdentifier;
		}
		((Exp2Variable*)(toBuild))->index = this->buildIndex(readingPos);
		if (readingPos != nullptr) {
			readingPos->prepareDelete(true);
			delete readingPos;
		}
	} else if (Exp2Constant::first()->isSet(related->tokenAt(0, false))) {
		toBuild = new Exp2Constant();
		((Exp2Constant*)(toBuild))->integer = related->tokenAt(0, false);
	} else if (Exp2NumericNegation::first()->isSet(related->tokenAt(0, false))) {
		toBuild = new Exp2NumericNegation();
		TokenSequence* negated = nullptr;
		TokenSequence* negMinus = related->splitOn(0, &negated);
		if (negMinus != nullptr) {
			negMinus->prepareDelete(true);
			delete negMinus;
		}
		((Exp2NumericNegation*) toBuild)->toNegate = this->buildExp2(negated);
	} else if (Exp2LogicalNegation::first()->isSet(related->tokenAt(0, false))){
		toBuild = new Exp2LogicalNegation();
		TokenSequence* negated = nullptr;
		TokenSequence* negExcl = related->splitOn(0, &negated);
		if (negExcl != nullptr) {
			negExcl->prepareDelete(true);
			delete negExcl;
		}
		((Exp2NumericNegation*) toBuild)->toNegate = this->buildExp2(negated);
	}
	return toBuild;
}

Parser::~Parser() {
	this->currentCodeSnippet->prepareDelete(false);
	delete this->currentCodeSnippet;
	// clean up all static ParseTree members (only the Parser ever calls first() and isMatching(), and there is only one)
	delete ParseTree::bracketsToken;
	delete ParseTree::epsToken;
	delete ParseTree::identifierToken;
	delete ParseTree::integerToken;
	delete ParseTree::minusToken;
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
	delete OpEquals::firstToken;
	delete OpAnd::firstToken;
}
