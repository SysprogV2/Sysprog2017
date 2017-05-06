/*
 * ParseTree.cpp
 *
 *  Created on: 29.12.2015
 *      Author: Domi
 */

#include "../includes/ParseTree.h"

Token* ParseTree::epsToken = nullptr;
Token* ParseTree::bracketsToken = nullptr;
Token* ParseTree::minusToken = nullptr;
Token* ParseTree::integerToken = nullptr;
Token* ParseTree::identifierToken = nullptr;
Token* ParseTree::greaterToken = nullptr;
Token* ParseTree::notEqualsToken = nullptr;
Token* ParseTree::failureToken = nullptr;
Symboltable* ParseTree::typeTable = nullptr;
std::ofstream ParseTree::codeOutput;
LabelFactory* ParseTree::labelFactory = nullptr;
Token* DeclOnly::firstToken = nullptr;
Token* ArrayIndex::firstToken = nullptr;
Token* StatementSetValue::defaultIdentifier = nullptr;
Token* StatementWrite::firstToken = nullptr;
Token* StatementRead::firstToken = nullptr;
Token* StatementBlock::firstToken = nullptr;
Token* StatementIfElse::firstToken = nullptr;
Token* StatementWhile::firstToken = nullptr;
Token* Exp2Nested::firstToken = nullptr;
Token* Exp2Variable::defaultIdentifier = nullptr;
Token* Exp2Constant::defaultInteger = nullptr;
Token* Exp2NumericNegation::firstToken = nullptr;
Token* Exp2LogicalNegation::firstToken = nullptr;
Token* IndexPosition::firstToken = nullptr;
Token* OpPlus::firstToken = nullptr;
Token* OpMinus::firstToken = nullptr;
Token* OpMult::firstToken = nullptr;
Token* OpDiv::firstToken = nullptr;
Token* OpLess::firstToken = nullptr;
Token* OpGreater::firstToken = nullptr;
Token* OpEquals::firstToken = nullptr;
Token* OpNotEquals::firstToken = nullptr;
Token* OpAnd::firstToken = nullptr;

void ParseTree::initStatic() { // to be called on Parser launch
	epsToken = EPSILON_TOKEN;
	ParseTree::bracketsToken = TYPE_REFERENCE_TOKEN_BRACKETS_START;
	ParseTree::minusToken = TYPE_REFERENCE_TOKEN_MINUS;
	ParseTree::identifierToken = IDENTIFIER_DEFAULT_TOKEN;
	ParseTree::integerToken = INTEGER_DEFAULT_TOKEN;
	ParseTree::greaterToken = TYPE_REFERENCE_TOKEN_GREATER;
	ParseTree::notEqualsToken = TYPE_REFERENCE_TOKEN_NOT_EQUALS;
	Prog::initStatic();
	std::cout << "Static ParseTree initialization works\n";
}

TokenTypeRegistry* ParseTree::first() {
	return nullptr; // no actual first() of abstract ParseTree
}

void ParseTree::cleanupStatic() {
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

void ParseTree::prepareTreeOperations() { // to be called before running typeCheck()
	ParseTree::typeTable = new Symboltable();
	ParseTree::codeOutput.open("../../debug/test.code");
	ParseTree::labelFactory = new LabelFactory(1);
	std::cout << "Operative initialization works\n";
}

void ParseTree::terminateTreeOperations() { // to be called at the end of main()
	delete ParseTree::typeTable;
	ParseTree::codeOutput.close();
	delete ParseTree::labelFactory;
}

void ParseTree::setChecktype(CheckableType type) {
	this->checkingType = type;
}

CheckableType ParseTree::getChecktype() {
	return this->checkingType;
}

ParseTree::~ParseTree() {}

void Prog::initStatic() {
	ProgOnly::initStatic();
}

TokenTypeRegistry* Prog::first() {
	return ProgOnly::first();
}

void Decls::initStatic() {
	DeclsSeq::initStatic();
	DeclsEps::initStatic();
}

TokenTypeRegistry* Decls::first() {
	TokenTypeRegistry* registry = DeclsSeq::first();
	registry->uniteWith(DeclsEps::first());
	return registry;
}

void Decl::initStatic() {
	DeclOnly::initStatic();
}

TokenTypeRegistry* Decl::first() {
	return DeclOnly::first();
}

void Array::initStatic() {
	ArrayIndex::initStatic();
	ArrayEps::initStatic();
}

TokenTypeRegistry* Array::first() {
	TokenTypeRegistry* registry = ArrayIndex::first();
	registry->uniteWith(ArrayEps::first());
	return registry;
}

void Statements::initStatic() {
	StatementsSeq::initStatic();
	StatementsEps::initStatic();
}

TokenTypeRegistry* Statements::first() {
	TokenTypeRegistry* registry = StatementsSeq::first();
    registry->uniteWith(StatementsEps::first());
    return registry;
}

void Statement::initStatic() {
	StatementSetValue::initStatic();
	StatementWrite::initStatic();
	StatementRead::initStatic();
	StatementBlock::initStatic();
	StatementIfElse::initStatic();
	StatementWhile::initStatic();
}

TokenTypeRegistry* Statement::first() {
	TokenTypeRegistry* registry = StatementSetValue::first();
	registry->uniteWith(StatementWrite::first());
	registry->uniteWith(StatementRead::first());
	registry->uniteWith(StatementBlock::first());
	registry->uniteWith(StatementIfElse::first());
	registry->uniteWith(StatementWhile::first());
	return registry;
}

void Exp::initStatic() {
	ExpOnly::initStatic();
}

TokenTypeRegistry* Exp::first() {
	return ExpOnly::first();
}

void Exp2::initStatic() {
	Exp2Nested::initStatic();
	Exp2Variable::initStatic();
	Exp2Constant::initStatic();
	Exp2NumericNegation::initStatic();
	Exp2LogicalNegation::initStatic();
}

TokenTypeRegistry* Exp2::first() {
	TokenTypeRegistry* registry = Exp2Nested::first();
	registry->uniteWith(Exp2Variable::first());
	registry->uniteWith(Exp2Constant::first());
	registry->uniteWith(Exp2NumericNegation::first());
	registry->uniteWith(Exp2LogicalNegation::first());
	return registry;
}

void Index::initStatic() {
	IndexPosition::initStatic();
	IndexEps::initStatic();
}

TokenTypeRegistry* Index::first() {
	TokenTypeRegistry* sequence = IndexPosition::first();
	sequence->uniteWith(IndexEps::first());
	return sequence;
}

void OpExp::initStatic() {
	OpExpNext::initStatic();
	OpExpEps::initStatic();
}

TokenTypeRegistry* OpExp::first() {
	TokenTypeRegistry* sequence = OpExpNext::first();
	sequence->uniteWith(OpExpEps::first());
	return sequence;
}

void Op::initStatic() {
	OpPlus::initStatic();
	OpMinus::initStatic();
	OpMult::initStatic();
	OpDiv::initStatic();
	OpLess::initStatic();
	OpGreater::initStatic();
	OpEquals::initStatic();
	OpNotEquals::initStatic();
	OpAnd::initStatic();
}

TokenTypeRegistry* Op::first() {
	TokenTypeRegistry* registry = OpPlus::first();
	registry->uniteWith(OpMinus::first());
	registry->uniteWith(OpMult::first());
	registry->uniteWith(OpDiv::first());
	registry->uniteWith(OpLess::first());
	registry->uniteWith(OpGreater::first());
	registry->uniteWith(OpEquals::first());
	registry->uniteWith(OpNotEquals::first());
	registry->uniteWith(OpAnd::first());
	return registry;
}

void ProgOnly::initStatic() {
	Decls::initStatic();
	Statements::initStatic();
}

TokenTypeRegistry* ProgOnly::first() {
	TokenTypeRegistry* registry = Decls::first();
	registry->uniteWith(Statements::first()); // Decls::first() contains Epsilon, Statements::first() too so no need to remove it before merging
	return registry;
}

ProgOnly::ProgOnly(Scanner* scanner) {
	if (DeclsSeq::first()->isSet(scanner->nextToken())) {
		this->declarationSegment = new DeclsSeq(scanner);
	} else if (DeclsEps::first()->isSet(scanner->currentToken())) {
		this->declarationSegment = new DeclsEps(scanner);
	} else {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << Decls::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	if (StatementsSeq::first()->isSet(scanner->nextToken())) {
		this->statementSegment = new StatementsSeq(scanner);
	} else if (StatementsEps::first()->isSet(scanner->currentToken())) {
		this->statementSegment = new StatementsEps(scanner);
	} else {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << Statements::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool ProgOnly::typeCheck() {
	if (!this->declarationSegment->typeCheck()) {
		std::cout << "Type checking works\n";
		ERROR_EXIT
	}
	if (!this->statementSegment->typeCheck()) {
		std::cout << "Type checking works\n";
		ERROR_EXIT
	}
	this->checkingType = noType;
	std::cout << "Type checking works\n";
	return true;
}

void ProgOnly::makeCode() {
	this->declarationSegment->makeCode();
	this->statementSegment->makeCode();
	ParseTree::codeOutput << "STP\n";
	std::cout << "Code creation works\n";
}

ProgOnly::~ProgOnly() {
	delete this->declarationSegment;
	delete this->statementSegment;
}

void DeclsSeq::initStatic() {
	Decl::initStatic();
}

TokenTypeRegistry* DeclsSeq::first() {
	return Decl::first(); // no Epsilon in Decl::first() so no merging with Decls::first()
}

DeclsSeq::DeclsSeq(Scanner* scanner) {
	this->firstDeclaration = new DeclOnly(scanner);
	if (scanner->nextToken()->getType() != 23) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, semicolon expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found\n";
		exit(1);
	}
	if (DeclsSeq::first()->isSet(scanner->nextToken())) {
		this->restOfDeclarations = new DeclsSeq(scanner);
	} else if (DeclsEps::first()->isSet(scanner->currentToken())) {
		this->restOfDeclarations = new DeclsEps(scanner);
	} else {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << Decls::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		// if (scanner->currentToken()->getLexem() == "class") std::cerr << "Sorry, but this programming language does not support classes. We suggest trying Java instead.\n";
		exit(1);
	}
}

bool DeclsSeq::typeCheck() {
	if (!this->firstDeclaration->typeCheck()) {
		ERROR_EXIT
	}
	if (!this->restOfDeclarations->typeCheck()) {
		ERROR_EXIT
	}
	this->checkingType = noType;
	return true;
}

void DeclsSeq::makeCode() {
	this->firstDeclaration->makeCode();
	this->restOfDeclarations->makeCode();
}

bool DeclsSeq::isEps() {
	return false;
}

DeclsSeq::~DeclsSeq() {
	delete this->firstDeclaration;
	delete this->restOfDeclarations;
}

void DeclsEps::initStatic() {}

TokenTypeRegistry* DeclsEps::first() {
	TokenTypeRegistry* registry = new TokenTypeRegistry();
	registry->set(DeclsEps::epsToken);
	return registry;
}

DeclsEps::DeclsEps(Scanner* scanner) {
	 // empty string representative, doesn't make much sense to check anything here
}

bool DeclsEps::typeCheck() {
	this->checkingType = noType;
	return true;
}

void DeclsEps::makeCode() {}

bool DeclsEps::isEps() {
	return true;
}

DeclsEps::~DeclsEps() {}

void DeclOnly::initStatic() {
	DeclOnly::firstToken  = TYPE_REFERENCE_TOKEN_INT;
	Array::initStatic();
}

TokenTypeRegistry* DeclOnly::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry();
    sequence->set(DeclOnly::firstToken);
    return sequence;
}

DeclOnly::DeclOnly(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 32) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, keyword \"int\" expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		// if (scanner->currentToken()->getLexem() == "class") std::cerr << "Sorry, but this programming language does not support classes. We suggest trying Java instead.\n";
		exit(1);
	}
	if (ArrayIndex::first()->isSet(scanner->nextToken())) {
		this->size = new ArrayIndex(scanner);
	} else if (ArrayEps::first()->isSet(scanner->currentToken())) {
		this->size = new ArrayEps(scanner);
	} else {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << Array::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	this->identifier = scanner->nextToken();
	if (this->identifier->getType() != 1) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, identifier expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool DeclOnly::typeCheck() {
	if (!this->size->typeCheck()) {
		ERROR_EXIT
	}
	if (ParseTree::typeTable->lookup(this->identifier->getLexem())->getType() != noType) {
		std::cerr << "error line " << this->identifier->getLine() << " column " << this->identifier->getColumn() << ": identifier already defined\n";
		ERROR_EXIT
	}
	if (this->size->getChecktype() == errorType) {
		ERROR_EXIT
	}
	this->checkingType = noType;
	if (this->size->getChecktype() == arrayType) {
		ParseTree::typeTable->attachType(this->identifier->getLexem(), intArrayType);
	} else {
		ParseTree::typeTable->attachType(this->identifier->getLexem(), intType);
	}
	return true;
}

void DeclOnly::makeCode() {
	ParseTree::codeOutput << "DS $" << this->identifier->getLexem() << ' ';
	this->size->makeCode();
}

DeclOnly::~DeclOnly() {
	delete this->identifier;
	delete this->size;
}

void ArrayIndex::initStatic() {
	ArrayIndex::firstToken = ParseTree::bracketsToken;
}

bool ArrayIndex::isEps() {
	return false;
}

TokenTypeRegistry* ArrayIndex::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(ArrayIndex::firstToken);
	return sequence;
}

ArrayIndex::ArrayIndex(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 28) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, opening bracket (\"[\") expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	this->integer = scanner->nextToken();
	if (this->integer->getType() != 2) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, integer expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	if (scanner->nextToken()->getType() != 29) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, closing bracket (\"]\") expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool ArrayIndex::typeCheck() {
	if (this->integer->getValue() < 0) {
		std::cerr << "error line " << this->integer->getLine() << " column " << this->integer->getColumn() << ": no valid dimension\n";
		ERROR_EXIT
	}
	this->checkingType = noType;
	return true;
}

void ArrayIndex::makeCode() {
	ParseTree::codeOutput << this->integer->getValue() << '\n';
}

ArrayIndex::~ArrayIndex() {
	delete this->integer;
}

void ArrayEps::initStatic() {}

TokenTypeRegistry* ArrayEps::first() {
	TokenTypeRegistry *sequence = new TokenTypeRegistry ();
	sequence->set (ParseTree::epsToken);
	return sequence;
}

ArrayEps::ArrayEps(Scanner* scanner) {
	// empty string representative, doesn't make much sense to check anything here
}

bool ArrayEps::isEps() {
	return true;
}

bool ArrayEps::typeCheck() {
	this->checkingType = noType;
	return true;
}

void ArrayEps::makeCode() {
	ParseTree::codeOutput << "1\n";
}

ArrayEps::~ArrayEps() {}

void StatementsSeq::initStatic() {
	Statement::initStatic();
}

TokenTypeRegistry* StatementsSeq::first() {
	return Statement::first();
}

StatementsSeq::StatementsSeq(Scanner* scanner) {
	switch (scanner->currentToken()->getType()) {
	case 1:
		this->firstStatement = new StatementSetValue(scanner);
		break;
	case 33:
		this->firstStatement = new StatementWrite(scanner);
		break;
	case 35:
		this->firstStatement = new StatementRead(scanner);
		break;
	case 26:
		this->firstStatement = new StatementBlock(scanner);
		break;
	case 30:
		this->firstStatement = new StatementIfElse(scanner);
		break;
	case 31:
		this->firstStatement = new StatementWhile(scanner);
		break;
	default:
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << Statement::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	if (scanner->nextToken()->getType() != 23) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, semicolon expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	if (StatementsSeq::first()->isSet(scanner->nextToken())) {
		this->restOfStatements = new StatementsSeq(scanner);
	} else if (StatementsEps::first()->isSet(scanner->currentToken())) {
		this->restOfStatements = new StatementsEps(scanner);
	} else {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << Statements::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool StatementsSeq::typeCheck() {
	if (!this->firstStatement->typeCheck()) {
		ERROR_EXIT
	}
	if (!this->restOfStatements->typeCheck()) {
		ERROR_EXIT
	}
	this->checkingType = noType;
	return true;
}

void StatementsSeq::makeCode() {
	this->firstStatement->makeCode();
	this->restOfStatements->makeCode();
}

bool StatementsSeq::isEps() {
	return false;
}

StatementsSeq::~StatementsSeq() {
	delete this->firstStatement;
	delete this->restOfStatements;
}

void StatementsEps::initStatic() {}

TokenTypeRegistry* StatementsEps::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set (ParseTree::epsToken);
	return sequence;
}

StatementsEps::StatementsEps(Scanner* scanner) {
	// empty string representative, doesn't make much sense to check anything here
}

bool StatementsEps::isEps() {
	return true;
}

bool StatementsEps::typeCheck() {
	this->checkingType = noType;
	return true;
}

void StatementsEps::makeCode() {
	ParseTree::codeOutput << "NOP\n";
}

StatementsEps::~StatementsEps() {}

void StatementSetValue::initStatic() {
	StatementSetValue::defaultIdentifier = ParseTree::identifierToken;
	Index::initStatic();
	Exp::initStatic();
}

TokenTypeRegistry* StatementSetValue::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set (StatementSetValue::defaultIdentifier);
	return sequence;
}

StatementSetValue::StatementSetValue(Scanner* scanner) {
	this->identifier = scanner->currentToken();
	if (this->identifier->getType() != 1) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, identifier expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	if (IndexPosition::first()->isSet(scanner->nextToken())) {
		this->index = new IndexPosition(scanner);
	} else if (IndexEps::first()->isSet(scanner->currentToken())) {
		this->index = new IndexEps(scanner);
	} else {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << Index::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	if (scanner->nextToken()->getType() != 10) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, assignment expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	this->aimValue = new ExpOnly(scanner);
}

bool StatementSetValue::typeCheck() {
	if (!this->aimValue->typeCheck()) {
		ERROR_EXIT
	}
	if (!this->index->typeCheck()) {
		ERROR_EXIT
	}
	if (ParseTree::typeTable->lookup(this->identifier->getLexem())->getType() == noType) {
	    std::cerr << "error line " << this->identifier->getLine() << " column " << this->identifier->getColumn() << ": identifier not defined\n";
	    ERROR_EXIT
	}
	if (this->aimValue->getChecktype() != intType) {
		std::cerr << "error line " << this->identifier->getLine() << " column " << this->identifier->getColumn() << ": cannot assign arrays\n";
		ERROR_EXIT
	}
	if (   (ParseTree::typeTable->lookup(this->identifier->getLexem())->getType() != intType
	        || this->index->getChecktype() != noType)
	    && (ParseTree::typeTable->lookup(this->identifier->getLexem())->getType() != intArrayType
	        || this->index->getChecktype() != arrayType)) {
	    std::cerr << "error line " << this->identifier->getLine() << " column " << this->identifier->getColumn() << ": incompatible types\n";
		ERROR_EXIT
	}
	this->checkingType = noType;
	return true;
}

void StatementSetValue::makeCode() {
	this->aimValue->makeCode();
	ParseTree::codeOutput << "LA $" << this->identifier->getLexem() << '\n';
	this->index->makeCode();
	ParseTree::codeOutput << "STR\n";
}

StatementSetValue::~StatementSetValue() {
	delete this->identifier;
	delete this->index;
	delete this->aimValue;
}

void StatementWrite::initStatic() {
	StatementWrite::firstToken = TYPE_REFERENCE_TOKEN_WRITE;
}

TokenTypeRegistry* StatementWrite::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(StatementWrite::firstToken);
	return sequence;
}

StatementWrite::StatementWrite(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 33) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, keyword \"write\" expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	if (scanner->nextToken()->getType() != 24) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, opening paranthesis (\"(\") expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	this->toPrint = new ExpOnly(scanner);
	if (scanner->nextToken()->getType() != 25) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, closing paranthesis (\")\") expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool StatementWrite::typeCheck() {
	if (!this->toPrint->typeCheck()) {
		ERROR_EXIT
	}
	this->checkingType = noType;
	return true;
}

void StatementWrite::makeCode() {
	this->toPrint->makeCode();
	ParseTree::codeOutput << "PRI\n";
}

StatementWrite::~StatementWrite() {
	delete this->toPrint;
}

void StatementRead::initStatic() {
	StatementRead::firstToken = TYPE_REFERENCE_TOKEN_READ;
}

TokenTypeRegistry* StatementRead::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(StatementRead::firstToken);
	return sequence;
}

StatementRead::StatementRead(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 35) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, keyword \"read\" expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	if (scanner->nextToken()->getType() != 24) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, opening paranthesis (\"(\") expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	this->identifier = scanner->nextToken();
	if (this->identifier->getType() != 1) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, identifier expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	if (IndexPosition::first()->isSet(scanner->nextToken())) {
		this->index = new IndexPosition(scanner);
	} else if (IndexEps::first()->isSet(scanner->currentToken())) {
		this->index = new IndexEps(scanner);
	} else {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << Index::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	if (scanner->nextToken()->getType() != 25) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, closing paranthesis(\")\") expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool StatementRead::typeCheck() {
	if (!this->index->typeCheck()) {
		ERROR_EXIT
	}
	if (ParseTree::typeTable->lookup(this->identifier->getLexem())->getType() == noType) {
	    std::cerr << "error line " << this->identifier->getLine() << " column " << this->identifier->getColumn() << ": identifier not defined\n";
		ERROR_EXIT
	}
	if (   (ParseTree::typeTable->lookup(this->identifier->getLexem())->getType() != intType
	        || this->index->getChecktype() != noType)
	    && (ParseTree::typeTable->lookup(this->identifier->getLexem())->getType() != intArrayType
	        || this->index->getChecktype() != arrayType)) {
	    std::cerr << "error line " << this->identifier->getLine() << " column " << this->identifier->getColumn() << ": incompatible types\n";
	    ERROR_EXIT
	}
	this->checkingType = noType;
	return true;
}

void StatementRead::makeCode() {
	ParseTree::codeOutput << "REA\nLA $" << this->identifier->getLexem() << '\n';
	this->index->makeCode();
	ParseTree::codeOutput << "STR\n";
}

StatementRead::~StatementRead() {
	delete this->identifier;
	delete this->index;
}

void StatementBlock::initStatic() {
	StatementBlock::firstToken = TYPE_REFERENCE_TOKEN_BRACES_START;
}

TokenTypeRegistry* StatementBlock::first() {
	TokenTypeRegistry *sequence = new TokenTypeRegistry();
	sequence->set(StatementBlock::firstToken);
	return sequence;
}

StatementBlock::StatementBlock(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 26) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, opening brace (\"{\") expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	if (StatementsSeq::first()->isSet(scanner->nextToken())) {
		this->blockContent = new StatementsSeq(scanner);
	} else if (StatementsEps::first()->isSet(scanner->currentToken())) {
		this->blockContent = new StatementsEps(scanner);
	} else {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << Statements::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	if (scanner->nextToken()->getType() != 27) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, closing brace (\"}\") expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool StatementBlock::typeCheck() {
	if (!this->blockContent->typeCheck()) {
		ERROR_EXIT
	}
	this->checkingType = noType;
	return true;
}

void StatementBlock::makeCode() {
	this->blockContent->makeCode();
}

StatementBlock::~StatementBlock() {
	delete this->blockContent;
}

void StatementIfElse::initStatic() {
	StatementIfElse::firstToken = TYPE_REFERENCE_TOKEN_IF;
}

TokenTypeRegistry* StatementIfElse::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(StatementIfElse::firstToken);
	return sequence;
}

StatementIfElse::StatementIfElse(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 30) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, keyword \"if\" expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	if (scanner->nextToken()->getType() != 24) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, opening paranthesis (\"(\") expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	this->condition = new ExpOnly(scanner);
	if (scanner->nextToken()->getType() != 25) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, closing paranthesis (\")\") expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	switch (scanner->nextToken()->getType()) {
	case 1:
		this->thenCase = new StatementSetValue(scanner);
		break;
	case 33:
		this->thenCase = new StatementWrite(scanner);
		break;
	case 35:
		this->thenCase = new StatementRead(scanner);
		break;
	case 26:
		this->thenCase = new StatementBlock(scanner);
		break;
	case 30:
		this->thenCase = new StatementIfElse(scanner);
		break;
	case 31:
		this->thenCase = new StatementWhile(scanner);
		break;
	default:
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << Statement::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	if (scanner->nextToken()->getType() != 34) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, keyword \"else\" expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	switch (scanner->nextToken()->getType()) {
	case 1:
		this->elseCase = new StatementSetValue(scanner);
		break;
	case 33:
		this->elseCase = new StatementWrite(scanner);
		break;
	case 35:
		this->elseCase = new StatementRead(scanner);
		break;
	case 26:
		this->elseCase = new StatementBlock(scanner);
		break;
	case 30:
		this->elseCase = new StatementIfElse(scanner);
		break;
	case 31:
		this->elseCase = new StatementWhile(scanner);
		break;
	default:
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << Statement::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool StatementIfElse::typeCheck() {
	if (!this->condition->typeCheck()) {
		ERROR_EXIT
	}
	if (this->condition->getChecktype() == errorType) {
		ERROR_EXIT
	}
	if (!this->thenCase->typeCheck()) {
		ERROR_EXIT
	}
	if (!this->elseCase->typeCheck()) {
		ERROR_EXIT
	}
	this->checkingType = noType;
	return true;
}

void StatementIfElse::makeCode() {
	int label1 = ParseTree::labelFactory->newLabel();
	int label2 = ParseTree::labelFactory->newLabel();
	this->condition->makeCode();
	ParseTree::codeOutput << "JIN #" << label1 << '\n';
	this->thenCase->makeCode();
	ParseTree::codeOutput << "JMP #" << label2 << "\n#" << label1 << " NOP\n";
	this->elseCase->makeCode();
	ParseTree::codeOutput << '#' << label2 << " NOP\n";
}

StatementIfElse::~StatementIfElse() {
	delete this->condition;
	delete this->thenCase;
	delete this->elseCase;
}

void StatementWhile::initStatic() {
	StatementWhile::firstToken = TYPE_REFERENCE_TOKEN_WHILE;
}

TokenTypeRegistry* StatementWhile::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(StatementWhile::firstToken);
	return sequence;
}

StatementWhile::StatementWhile(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 31) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, keyword \"while\" expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	if (scanner->nextToken()->getType() != 24) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, opening paranthesis (\"(\") expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	this->condition = new ExpOnly(scanner);
	if (scanner->nextToken()->getType() != 25) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, closing paranthesis (\")\") expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	switch (scanner->nextToken()->getType()) {
	case 1:
		this->loop = new StatementSetValue(scanner);
		break;
	case 33:
		this->loop = new StatementWrite(scanner);
		break;
	case 35:
		this->loop = new StatementRead(scanner);
		break;
	case 26:
		this->loop = new StatementBlock(scanner);
		break;
	case 30:
		this->loop = new StatementIfElse(scanner);
		break;
	case 31:
		this->loop = new StatementWhile(scanner);
		break;
	default:
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << Statement::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool StatementWhile::typeCheck() {
	if (!this->condition->typeCheck()) {
		ERROR_EXIT
	}
	if (this->condition->getChecktype() == errorType) {
		ERROR_EXIT
	}
	if (!this->loop->typeCheck()) {
		ERROR_EXIT
	}
	this->checkingType = noType;
	return true;
}

void StatementWhile::makeCode() {
	int label1 = ParseTree::labelFactory->newLabel();
	int label2 = ParseTree::labelFactory->newLabel();
	ParseTree::codeOutput << '#' << label1 << " NOP\n";
	this->condition->makeCode();
	ParseTree::codeOutput << "JIN #" << label2 << '\n';
	this->loop->makeCode();
	ParseTree::codeOutput << "JMP #" << label1 << "\n#" << label2 << " NOP\n";
}

StatementWhile::~StatementWhile() {
	delete this->condition;
	delete this->loop;
}

void ExpOnly::initStatic() {
	Exp2::initStatic();
	OpExp::initStatic();
}

TokenTypeRegistry* ExpOnly::first() {
	return Exp2::first();
}

ExpOnly::ExpOnly(Scanner* scanner) {
	switch(scanner->nextToken()->getType()) {
	case 24:
		this->rawExpression = new Exp2Nested(scanner);
		break;
	case 1:
		this->rawExpression = new Exp2Variable(scanner);
		break;
	case 2:
		this->rawExpression = new Exp2Constant(scanner);
		break;
	case 20:
		this->rawExpression = new Exp2NumericNegation(scanner);
		break;
	case 21:
		this->rawExpression = new Exp2LogicalNegation(scanner);
		break;
	default:
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << Exp2::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	if (OpExpNext::first()->isSet(scanner->nextToken())) {
		this->calculateWith = new OpExpNext(scanner);
	} else if (OpExpEps::first()->isSet(scanner->currentToken())) {
		this->calculateWith = new OpExpEps(scanner);
	} else {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << OpExp::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool ExpOnly::typeCheck() {
	if (!this->rawExpression->typeCheck()
	 || !this->calculateWith->typeCheck()) {
		ERROR_EXIT
	}
	if (this->calculateWith->getChecktype() == noType
	 || this->calculateWith->getChecktype() == this->rawExpression->getChecktype()) {
		this->checkingType = this->rawExpression->getChecktype();
		return true;
	}
	ERROR_EXIT
}

void ExpOnly::makeCode() {
	if (this->calculateWith->getChecktype() != noType
	 && ((OpExpNext*)this->calculateWith)->isOperatorGreater()) {
		this->calculateWith->makeCode();
	}
	this->rawExpression->makeCode();
	if (this->calculateWith->getChecktype() != noType) {
		if (!((OpExpNext*)this->calculateWith)->isOperatorGreater()) {
			this->calculateWith->makeCode();
			if (((OpExpNext*)this->calculateWith)->isOperatorNotEquals()) {
				ParseTree::codeOutput << "NOT\n";
			}
		}
		else {
			ParseTree::codeOutput << "LES\n";
		}
	}
}

ExpOnly::~ExpOnly() {
	delete this->rawExpression;
	delete this->calculateWith;
}

void Exp2Nested::initStatic() {
	Exp2Nested::firstToken = TYPE_REFERENCE_TOKEN_PARANTH_START;
}

TokenTypeRegistry* Exp2Nested::first() {
	TokenTypeRegistry *sequence = new TokenTypeRegistry ();
	sequence->set(Exp2Nested::firstToken);
	return sequence;
}

Exp2Nested::Exp2Nested(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 24) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, opening paranthesis (\"(\") expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	this->nestedExpression = new ExpOnly(scanner);
	if (scanner->nextToken()->getType() != 25) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, closing paranthesis (\")\") expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool Exp2Nested::typeCheck() {
	this->checkingType = this->nestedExpression->typeCheck() ? this->nestedExpression->getChecktype() : errorType;
	return this->checkingType != errorType;
}

void Exp2Nested::makeCode() {
	this->nestedExpression->makeCode();
}

Exp2Nested::~Exp2Nested() {
	delete this->nestedExpression;
}

void Exp2Variable::initStatic() {
	Exp2Variable::defaultIdentifier = ParseTree::identifierToken;
}

TokenTypeRegistry* Exp2Variable::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(Exp2Variable::defaultIdentifier);
	return sequence;
}

Exp2Variable::Exp2Variable(Scanner* scanner) {
	this->identifier = scanner->currentToken();
	if (this->identifier->getType() != 1) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, identifier expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	if (IndexPosition::first()->isSet(scanner->nextToken())) {
		this->index = new IndexPosition(scanner);
	} else if (IndexEps::first()->isSet(scanner->currentToken())) {
		this->index = new IndexEps(scanner);
	} else {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << Index::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool Exp2Variable::typeCheck() {
	if (!this->index->typeCheck()) {
		ERROR_EXIT
	}
	if (ParseTree::typeTable->lookup(this->identifier->getLexem())->getType() == noType) {
		std::cerr << "error line " << this->identifier->getLine() << " column " << this->identifier->getColumn() << ": identifier not defined\n";
	    ERROR_EXIT
	}
	if (   (ParseTree::typeTable->lookup(this->identifier->getLexem())->getType() != intType
	        || this->index->getChecktype() != noType)
	    && (ParseTree::typeTable->lookup(this->identifier->getLexem())->getType() != intArrayType
	        || this->index->getChecktype() != arrayType)) {
	    if (ParseTree::typeTable->lookup(this->identifier->getLexem())->getType() == intArrayType
	    	|| this->index->getChecktype() == noType) {
	    	std::cerr << "error line " << this->identifier->getLine() << " column " << this->identifier->getColumn() << ": not a primitive type\n";
	    }
		ERROR_EXIT
	}
	this->checkingType = intType;
	return true;
}

void Exp2Variable::makeCode() {
	ParseTree::codeOutput << "LA $" << this->identifier->getLexem() << '\n';
	this->index->makeCode();
	ParseTree::codeOutput << "LV\n";
}

Exp2Variable::~Exp2Variable() {
	delete this->identifier;
	delete this->index;
}

TokenTypeRegistry* Exp2Constant::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(Exp2Constant::defaultInteger);
	return sequence;
}

Exp2Constant::Exp2Constant(Scanner* scanner) {
	this->integer = scanner->currentToken();
	if (this->integer->getType() != 2) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, integer expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool Exp2Constant::typeCheck() {
	this->checkingType = intType;
	return true;
}

void Exp2Constant::makeCode() {
	ParseTree::codeOutput << "LC " << this->integer->getValue();
}

Exp2Constant::~Exp2Constant() {
	delete this->integer;
}

void Exp2NumericNegation::initStatic() {
	Exp2NumericNegation::firstToken = ParseTree::minusToken;
}

TokenTypeRegistry* Exp2NumericNegation::first() {
	TokenTypeRegistry *sequence = new TokenTypeRegistry ();
	sequence->set(Exp2NumericNegation::firstToken);
	return sequence;
}

Exp2NumericNegation::Exp2NumericNegation(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 20) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, negative signum or substraction expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	switch(scanner->nextToken()->getType()) {
	case 24:
		this->toNegate = new Exp2Nested(scanner);
		break;
	case 1:
		this->toNegate = new Exp2Variable(scanner);
		break;
	case 2:
		this->toNegate = new Exp2Constant(scanner);
		break;
	case 20:
		this->toNegate = new Exp2NumericNegation(scanner);
		break;
	case 21:
		this->toNegate = new Exp2LogicalNegation(scanner);
		break;
	default:
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << Exp2::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool Exp2NumericNegation::typeCheck() {
	bool result = this->toNegate->typeCheck();
	this->checkingType = this->toNegate->getChecktype();
	return result;
}

void Exp2NumericNegation::makeCode() {
	ParseTree::codeOutput << "LC 0\n";
	this->toNegate->makeCode();
	ParseTree::codeOutput << "SUB\n";
}

Exp2NumericNegation::~Exp2NumericNegation() {
	delete this->toNegate;
}

void Exp2LogicalNegation::initStatic() {
	Exp2LogicalNegation::firstToken = TYPE_REFERENCE_TOKEN_NOT;
}

TokenTypeRegistry* Exp2LogicalNegation::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(Exp2LogicalNegation::firstToken);
	return sequence;
}

Exp2LogicalNegation::Exp2LogicalNegation(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 21) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, boolean negator expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	switch(scanner->nextToken()->getType()) {
	case 24:
		this->toNegate = new Exp2Nested(scanner);
		break;
	case 1:
		this->toNegate = new Exp2Variable(scanner);
		break;
	case 2:
		this->toNegate = new Exp2Constant(scanner);
		break;
	case 20:
		this->toNegate = new Exp2NumericNegation(scanner);
		break;
	case 21:
		this->toNegate = new Exp2LogicalNegation(scanner);
		break;
	default:
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << Exp2::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool Exp2LogicalNegation::typeCheck() {
	if (!this->toNegate->typeCheck()
	 || this->toNegate->getChecktype() != intType) {
		ERROR_EXIT
	}
	this->checkingType = intType;
	return true;
}

void Exp2LogicalNegation::makeCode() {
	this->toNegate->makeCode();
	ParseTree::codeOutput << "NOT\n";
}

Exp2LogicalNegation::~Exp2LogicalNegation() {
	delete this->toNegate;
}

void IndexPosition::initStatic() {
	IndexPosition::firstToken = ParseTree::bracketsToken;
}

bool IndexPosition::isEps() {
	return false;
}

TokenTypeRegistry* IndexPosition::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(IndexPosition::firstToken);
	return sequence;
}

IndexPosition::IndexPosition(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 28) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, opening bracket (\"[\") expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	this->index = new ExpOnly(scanner);
	if (scanner->nextToken()->getType() != 29) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, closing bracket (\"]\") expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool IndexPosition::typeCheck() {
	if (!this->index->typeCheck() || this->index->getChecktype() == errorType) {
		ERROR_EXIT
	}
	this->checkingType = arrayType;
	return true;
}

void IndexPosition::makeCode() {
	this->index->makeCode();
	ParseTree::codeOutput << "ADD\n";
}

IndexPosition::~IndexPosition() {
	delete this->index;
}

void IndexEps::initStatic() {}

TokenTypeRegistry* IndexEps::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set (ParseTree::epsToken);
	return sequence;
}

bool IndexEps::isEps() {
	return true;
}

IndexEps::IndexEps(Scanner* scanner) {
	// empty string representative, doesn't make much sense to check anything here
}

bool IndexEps::typeCheck() {
	this->checkingType = noType;
	return true;
}

void IndexEps::makeCode() {}

IndexEps::~IndexEps() {}

void OpExpNext::initStatic() {
	Op::initStatic();
}

TokenTypeRegistry* OpExpNext::first() {
	return Op::first();
}

OpExpNext::OpExpNext(Scanner* scanner) {
	switch(scanner->currentToken()->getType()) {
	case 19:
		this->Operator = new OpPlus(scanner);
		break;
	case 20:
		this->Operator = new OpMinus(scanner);
		break;
	case 13:
		this->Operator = new OpMult(scanner);
		break;
	case 5:
		this->Operator = new OpDiv(scanner);
		break;
	case 3:
		this->Operator = new OpLess(scanner);
		break;
	case 4:
		this->Operator = new OpGreater(scanner);
		break;
	case 6:
		this->Operator = new OpEquals(scanner);
		break;
	case 7:
		this->Operator = new OpNotEquals(scanner);
		break;
	case 22:
		this->Operator = new OpAnd(scanner);
		break;
	default:
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, any of " << Op::first()->allSetTokenNames() << " expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
	this->operand = new ExpOnly(scanner);
}

bool OpExpNext::isEps() {
	return false;
}

bool OpExpNext::isOperatorGreater() {
	return this->Operator->first()->isSet(ParseTree::greaterToken);
}

bool OpExpNext::isOperatorNotEquals() {
	return this->Operator->first()->isSet(ParseTree::notEqualsToken);
}

bool OpExpNext::typeCheck() {
	if (!this->Operator->typeCheck()) {
		ERROR_EXIT
	}
	if (!this->operand->typeCheck()) {
		ERROR_EXIT
	}
	this->checkingType = this->operand->getChecktype();
	return true;
}

void OpExpNext::makeCode() {
	this->operand->makeCode();
	this->Operator->makeCode();
}

OpExpNext::~OpExpNext() {
	delete this->Operator;
	delete this->operand;
}

void OpExpEps::initStatic() {}

TokenTypeRegistry* OpExpEps::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set (ParseTree::epsToken);
	return sequence;
}

OpExpEps::OpExpEps(Scanner* scanner) {
	// empty string representative, doesn't make much sense to check anything here
}

bool OpExpEps::isEps() {
	return true;
}

bool OpExpEps::typeCheck() {
	this->checkingType = noType;
	return true;
}

void OpExpEps::makeCode() {}

OpExpEps::~OpExpEps() {}

void OpPlus::initStatic() {
	OpPlus::firstToken = TYPE_REFERENCE_TOKEN_PLUS;
}

TokenTypeRegistry* OpPlus::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(OpPlus::firstToken);
	return sequence;
}

OpPlus::OpPlus(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 19) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, addition expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool OpPlus::typeCheck() {
	this->checkingType = noType;
	return true;
}

void OpPlus::makeCode() {
	ParseTree::codeOutput << "ADD\n";
}

OpPlus::~OpPlus() {}

void OpMinus::initStatic() {
	OpMinus::firstToken = ParseTree::minusToken;
}

TokenTypeRegistry* OpMinus::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(OpMinus::firstToken);
	return sequence;
}

OpMinus::OpMinus(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 20) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, negative signum or substraction expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool OpMinus::typeCheck() {
	this->checkingType = noType;
	return true;
}

void OpMinus::makeCode() {
	ParseTree::codeOutput << "SUB\n";
}

OpMinus::~OpMinus() {}

void OpMult::initStatic() {
	OpMult::firstToken = TYPE_REFERENCE_TOKEN_MULT;
}

TokenTypeRegistry* OpMult::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(OpMult::firstToken);
	return sequence;
}

OpMult::OpMult(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 13) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, multiplication expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool OpMult::typeCheck() {
	this->checkingType = noType;
	return true;
}

void OpMult::makeCode() {
	ParseTree::codeOutput << "MUL\n";
}

OpMult::~OpMult() {}

void OpDiv::initStatic() {
	OpDiv::firstToken = TYPE_REFERENCE_TOKEN_DIV;
}

TokenTypeRegistry* OpDiv::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(OpDiv::firstToken);
	return sequence;
}

OpDiv::OpDiv(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 5) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, division expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool OpDiv::typeCheck() {
	this->checkingType = noType;
	return true;
}

void OpDiv::makeCode() {
	ParseTree::codeOutput << "DIV\n";
}

OpDiv::~OpDiv() {}

void OpLess::initStatic() {
	OpLess::firstToken = TYPE_REFERENCE_TOKEN_LESS;
}

TokenTypeRegistry* OpLess::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(OpLess::firstToken);
	return sequence;
}

OpLess::OpLess(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 3) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, comparision expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool OpLess::typeCheck() {
	this->checkingType = noType;
	return true;
}

void OpLess::makeCode() {
	ParseTree::codeOutput << "LES\n";
}

OpLess::~OpLess() {}

void OpGreater::initStatic() {
	OpGreater::firstToken = ParseTree::greaterToken;
}

TokenTypeRegistry* OpGreater::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(OpGreater::firstToken);
	return sequence;
}

OpGreater::OpGreater(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 4) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, comparision expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool OpGreater::typeCheck() {
	this->checkingType = noType;
	return true;
}

void OpGreater::makeCode() {}

OpGreater::~OpGreater() {}

 void OpEquals::initStatic() {
	 firstToken = TYPE_REFERENCE_TOKEN_EQUALS;
}

TokenTypeRegistry* OpEquals::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(OpEquals::firstToken);
	return sequence;
}

OpEquals::OpEquals(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 6) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, comparision expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

bool OpEquals::typeCheck() {
	this->checkingType = noType;
	return true;
}

void OpEquals::makeCode() {
	ParseTree::codeOutput << "EQU\n";
}

OpEquals::~OpEquals() {}

void OpNotEquals::initStatic() {
	OpNotEquals::firstToken = ParseTree::notEqualsToken;
}

OpNotEquals::OpNotEquals(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 7) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, comparision expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

TokenTypeRegistry* OpNotEquals::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(OpNotEquals::firstToken);
	return sequence;
}

bool OpNotEquals::typeCheck() {
	this->checkingType = noType;
	return true;
}

void OpNotEquals::makeCode() {
	ParseTree::codeOutput << "EQU\n";
}

OpNotEquals::~OpNotEquals() {}

void OpAnd::initStatic() {
	OpAnd::firstToken = TYPE_REFERENCE_TOKEN_AND;
}

OpAnd::OpAnd(Scanner* scanner) {
	if (scanner->currentToken()->getType() != 22) {
		std::cerr << "error line " << scanner->currentToken()->getLine() << " column " << scanner->currentToken()->getColumn() << ": unexpected token, \"and\" mask expected, " << Token::nameOf(scanner->currentToken()->getType()) << " found";
		exit(1);
	}
}

TokenTypeRegistry* OpAnd::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(OpAnd::firstToken);
	return sequence;
}

bool OpAnd::typeCheck() {
	this->checkingType = noType;
	return true;
}

void OpAnd::makeCode() {
	ParseTree::codeOutput << "AND\n";
}

OpAnd::~OpAnd() {}
