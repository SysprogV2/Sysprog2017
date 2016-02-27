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
IntQueue* ParseTree::splitIndexes = nullptr;
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
	ParseTree::splitIndexes = new IntQueue();
	Prog::initStatic();
	std::cout << "Static ParseTree initialization works\n";
}

bool ParseTree::isMatching(TokenSequence* sequence) {
	return false; // no rule corresponding to abstract ParseTree
}

TokenTypeRegistry* ParseTree::first() {
	return nullptr; // no actual first() of abstract ParseTree
}

void ParseTree::prepareTreeOperations() { // to be called before running typeCheck()
	ParseTree::typeTable = new Symboltable();
	ParseTree::codeOutput.open("../../debug/test.code");
	ParseTree::labelFactory = new LabelFactory(1);
	std::cout << "Operative initialization works\n";
}

void ParseTree::terminateTreeOperations() { // to be called at the end of main()
	delete ParseTree::splitIndexes;
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

bool Prog::isMatching(TokenSequence* sequence) {
	return ProgOnly::isMatching(sequence);
}

TokenTypeRegistry* Prog::first() {
	return ProgOnly::first();
}

void Decls::initStatic() {
	DeclsSeq::initStatic();
	DeclsEps::initStatic();
}

bool Decls::isMatching(TokenSequence* sequence) {
	return DeclsSeq::isMatching(sequence)
	    || DeclsEps::isMatching(sequence);
}

TokenTypeRegistry* Decls::first() {
	TokenTypeRegistry* registry = DeclsSeq::first();
	registry->uniteWith(DeclsEps::first());
	return registry;
}

void Decl::initStatic() {
	DeclOnly::initStatic();
}

bool Decl::isMatching(TokenSequence* sequence) {
	return DeclOnly::isMatching(sequence);
}

TokenTypeRegistry* Decl::first() {
	return DeclOnly::first();
}

void Array::initStatic() {
	ArrayIndex::initStatic();
	ArrayEps::initStatic();
}

bool Array::isMatching(TokenSequence* sequence) {
	return ArrayIndex::isMatching(sequence)
		|| ArrayEps::isMatching(sequence);
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

bool Statements::isMatching(TokenSequence* sequence) {
	return StatementsSeq::isMatching(sequence)
		|| StatementsEps::isMatching(sequence);
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

bool Statement::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 2) return false;
	return StatementSetValue::isMatching(sequence)
		|| StatementWrite::isMatching(sequence)
		|| StatementRead::isMatching(sequence)
		|| StatementBlock::isMatching(sequence)
		|| StatementIfElse::isMatching(sequence)
		|| StatementWhile::isMatching(sequence);
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

bool Exp::isMatching(TokenSequence* sequence) {
	return ExpOnly::isMatching(sequence);
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

bool Exp2::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 1) return false;
	return Exp2Nested::isMatching(sequence)
		|| Exp2Variable::isMatching(sequence)
		|| Exp2Constant::isMatching(sequence)
		|| Exp2NumericNegation::isMatching(sequence)
		|| Exp2LogicalNegation::isMatching(sequence);
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

bool Index::isMatching(TokenSequence* sequence) {
	return IndexPosition::isMatching(sequence)
		|| IndexEps::isMatching(sequence);
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

bool OpExp::isMatching(TokenSequence* sequence) {
	return OpExpNext::isMatching(sequence)
		|| OpExpEps::isMatching(sequence);
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

bool Op::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 1) return false;
	return OpPlus::isMatching(sequence)
		|| OpMinus::isMatching(sequence)
		|| OpMult::isMatching(sequence)
		|| OpDiv::isMatching(sequence)
		|| OpLess::isMatching(sequence)
		|| OpGreater::isMatching(sequence)
		|| OpEquals::isMatching(sequence)
		|| OpNotEquals::isMatching(sequence)
		|| OpAnd::isMatching(sequence);
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


bool ProgOnly::isMatching(TokenSequence* sequence) {
	std::cout << "Starting isMatching() from ProgOnly\n";
	TokenSequence* sub1 = nullptr;
	TokenSequence* sub2 = nullptr;
	for (int i = -1; i <= sequence->getSize(); i++) {
		sub1 = sequence->splitOn(i, &sub2);
		ParseTree::splitIndexes->push(i);
		if (Decls::isMatching(sub1) && Statements::isMatching(sub2)) {
			sub1->prepareDelete(true);
			delete sub1;
			sub2->prepareDelete(true);
			delete sub2;
			std::cout << "Finishing isMatching() from ProgOnly\n" << "Matching works\n";
			return true;
		} else {
			sub1->prepareDelete(true);
			delete sub1;
			sub2->prepareDelete(true);
			delete sub2;
			ParseTree::splitIndexes->undoPushing();
		}
	}
	std::cout << "Finishing isMatching() from ProgOnly\n" << "Matching works\n";
	return false;
}

ProgOnly::ProgOnly() {
	this->declarationSegment = nullptr;
	this->statementSegment = nullptr;
	this->checkingType = uncheckedType;
}

TokenTypeRegistry* ProgOnly::first() {
	TokenTypeRegistry* registry = Decls::first();
	registry->uniteWith(Statements::first()); // Decls::first() contains Epsilon, Statements::first() too so no need to remove it before merging
	return registry;
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

bool DeclsSeq::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 3) return false;
	std::cout << "Starting isMatching() from DeclsSeq\n";
	TokenSequence* sub1 = nullptr;
	TokenSequence* sub2 = nullptr;
	TokenSequence* sub3 = nullptr;
	TokenSequence* sub4 = nullptr;
	const int semicolonTokenType = 23;
	for (int i = 0; i < sequence->getSize(); i++) {
		sub1 = sequence->splitOn(i, &sub2);
		sub3 = sub2->splitOn(0, &sub4);
		ParseTree::splitIndexes->push(i);
		if (Decl::isMatching(sub1) && sub3->tokenAt(0, false)->getType() == semicolonTokenType && Decls::isMatching(sub4)) {
			sub1->prepareDelete(true);
			sub2->prepareDelete(true);
			sub3->prepareDelete(true);
			sub4->prepareDelete(true);
			delete sub1;
			delete sub2;
			delete sub3;
			delete sub4;
			std:: cout << "Finishing isMatching() from DeclsSeq\n";
			return true;
		} else {
			sub1->prepareDelete(true);
			sub2->prepareDelete(true);
			sub3->prepareDelete(true);
			sub4->prepareDelete(true);
			delete sub1;
			delete sub2;
			delete sub3;
			delete sub4;
			ParseTree::splitIndexes->undoPushing();
		}
	}
	std:: cout << "Finishing isMatching() from DeclsSeq\n";
	return false;
}

DeclsSeq::DeclsSeq() {
	this->firstDeclaration = nullptr;
	this->restOfDeclarations = nullptr;
	this->checkingType = uncheckedType;
}

TokenTypeRegistry* DeclsSeq::first() {
	return Decl::first(); // no Epsilon in Decl::first() so no merging with Decls::first()
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

bool DeclsEps::isMatching(TokenSequence* sequence) {
	for (int i = 0; i < sequence->getSize(); i++) { // empty sequence: loop completely skips -> true (as should be)
		if (sequence->tokenAt(i, false)->getType() != ParseTree::epsToken->getType()) return false;
	}
	return true; // pseudo code: return sequence->allTokens()->areEpsTokens();
}

DeclsEps::DeclsEps() {}

TokenTypeRegistry* DeclsEps::first() {
	TokenTypeRegistry* registry = new TokenTypeRegistry();
	registry->set(DeclsEps::epsToken);
	return registry;
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

bool DeclOnly::isMatching(TokenSequence* sequence) {
	std:: cout << "Starting isMatching() from DeclOnly\n";
	if (sequence->getSize() < 2) return false;
	TokenSequence* array = nullptr;
	TokenSequence* useless1 = sequence->splitOn(1, &array);
	bool result = sequence->tokenAt(0, false)->getType() == DeclOnly::firstToken->getType()
			&& sequence->tokenAt(1, false)->getType() == ParseTree::identifierToken->getType()
			&& Array::isMatching(array);
	useless1->prepareDelete(true);
	array->prepareDelete(true);
	delete useless1;
	delete array;
	std:: cout << "Finishing isMatching() from DeclOnly\n";
	return result;
}

DeclOnly::DeclOnly() {
	this->identifier = nullptr; // will be set by Parser in the next first() step
	this->size = nullptr; // will be set by Parser in the next first() step
}

TokenTypeRegistry* DeclOnly::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry();
    sequence->set(DeclOnly::firstToken);
    return sequence;
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

bool ArrayIndex::isMatching(TokenSequence* sequence) {
	const int bracketsEndTokenType = 29;
	return sequence->getSize() == 3
			&& sequence->tokenAt(0, false)->getType() == ArrayIndex::firstToken->getType()
			&& sequence->tokenAt(1, false)->getType() == ParseTree::integerToken->getType()
			&& sequence->tokenAt(2, false)->getType() == bracketsEndTokenType;
}

ArrayIndex::ArrayIndex() {
	this->integer = nullptr;
}

bool ArrayIndex::isEps() {
	return false;
}

TokenTypeRegistry* ArrayIndex::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(ArrayIndex::firstToken);
	return sequence;
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

bool ArrayEps::isMatching(TokenSequence* sequence) {
	for (int i = 0; i < sequence->getSize(); i++) { // empty sequence: loop completely skips -> true (as should be)
		if (sequence->tokenAt(i, false)->getType() != ParseTree::epsToken->getType()) return false;
	}
	return true; // pseudo code: return sequence->allTokens()->areEpsTokens();
}

ArrayEps::ArrayEps() {}

TokenTypeRegistry* ArrayEps::first() {
	TokenTypeRegistry *sequence = new TokenTypeRegistry ();
	sequence->set (ParseTree::epsToken);
	return sequence;
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

bool StatementsSeq::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 3) return false;
	std:: cout << "Starting isMatching() from StatementsSeq\n";
	TokenSequence* sub1 = nullptr;
	TokenSequence* sub2 = nullptr;
	TokenSequence* sub3 = nullptr;
	TokenSequence* sub4 = nullptr;
	int semicolonTokenType = 23;
	for (int i = 0; i < sequence->getSize(); i++) {
		sub1 = sequence->splitOn(i, &sub2);
		sub3 = sub2->splitOn(0, &sub4);
		ParseTree::splitIndexes->push(i);
		if (Statement::isMatching(sub1) && sub3->tokenAt(0, false)->getType() == semicolonTokenType && Statements::isMatching(sub4)) {
			sub1->prepareDelete(true);
			sub2->prepareDelete(true);
			sub3->prepareDelete(true);
			sub4->prepareDelete(true);
			delete sub1;
			delete sub2;
			delete sub3;
			delete sub4;
			std:: cout << "Finishing isMatching() from StatementsSeq\n";
			return true;
		} else {
			sub1->prepareDelete(true);
		    sub2->prepareDelete(true);
		    sub3->prepareDelete(true);
		    sub4->prepareDelete(true);
			delete sub1;
			delete sub2;
			delete sub3;
			delete sub4;
			ParseTree::splitIndexes->undoPushing();
		}
	}
	std:: cout << "Finishing isMatching() from StatementsSeq\n";
	return false;
}

StatementsSeq::StatementsSeq() {
	this->firstStatement = nullptr;
	this->restOfStatements = nullptr;
}

TokenTypeRegistry* StatementsSeq::first() {
	return Statement::first();
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

bool StatementsEps::isMatching(TokenSequence* sequence) {
	for (int i = 0; i < sequence->getSize(); i++) { // empty sequence: loop completely skips -> true (as should be)
		if (sequence->tokenAt(i, false)->getType() != ParseTree::epsToken->getType()) return false;
	}
	return true; // pseudo code: return sequence->allTokens()->areEpsTokens();
}

StatementsEps::StatementsEps() {}

TokenTypeRegistry* StatementsEps::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set (ParseTree::epsToken);
	return sequence;
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

bool StatementSetValue::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 3) return false;
	std:: cout << "Starting isMatching() from StatementSetValue\n";
	TokenSequence* sub1 = nullptr;
	TokenSequence* sub2 = nullptr;
	TokenSequence* sub3 = nullptr;
	TokenSequence* sub4 = nullptr;
	TokenSequence* sub5 = nullptr;
	TokenSequence* sub6 = nullptr;
	const int assignType = 10;
	sub1 = sequence->splitOn(0, &sub2);
	if (sub1->tokenAt(0, false)->getType() != StatementSetValue::defaultIdentifier->getType()) return false;
	for (int i = 0; i < sub2->getSize(); i++) {
		sub3 = sub2->splitOn(i, &sub4);
		sub5 = sub4->splitOn(0, &sub6);
		ParseTree::splitIndexes->push(i);
		if (Index::isMatching(sub3) && sub5->tokenAt(0, false)->getType() == assignType && Exp::isMatching(sub6)) {
			sub1->prepareDelete(true);
			sub2->prepareDelete(true);
			sub3->prepareDelete(true);
			sub4->prepareDelete(true);
			sub5->prepareDelete(true);
			sub6->prepareDelete(true);
			delete sub1;
			delete sub2;
			delete sub3;
			delete sub4;
			delete sub5;
			delete sub6;
			std:: cout << "Finishing isMatching() from StatementSetValue\n";
			return true;
		}
		else {
			sub3->prepareDelete(true);
			sub4->prepareDelete(true);
			sub5->prepareDelete(true);
			sub6->prepareDelete(true);
			delete sub3;
			delete sub4;
			delete sub5;
			delete sub6;
			ParseTree::splitIndexes->undoPushing();
		}
	}
	sub1->prepareDelete(true);
	sub2->prepareDelete(true);
	delete sub1;
	delete sub2;
	std:: cout << "Finishing isMatching() from StatementSetValue\n";
	return false;
}

StatementSetValue::StatementSetValue() {
	this->identifier = nullptr;
	this->index = nullptr;
	this->aimValue = nullptr;
}

TokenTypeRegistry* StatementSetValue::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set (StatementSetValue::defaultIdentifier);
	return sequence;
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

bool StatementWrite::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 4) return false;
	std:: cout << "Starting isMatching() from StatementWrite\n";
	TokenSequence* exp = nullptr;
	TokenSequence* preExp = sequence->splitOn(1, &exp);
	TokenSequence* postExp = nullptr;
	TokenSequence* actualExp = exp->splitOn(exp->getSize() - 2, &postExp);
	const int paranthType1 = 24;
	const int paranthType2 = 25;
	bool result = sequence->tokenAt(0, false)->getType() == StatementWrite::firstToken->getType()
			&& sequence->tokenAt(1, false)->getType() == paranthType1
			&& Exp::isMatching(actualExp)
			&& sequence->tokenAt(sequence->getSize()-1, false)->getType() == paranthType2;
	exp->prepareDelete(true);
	actualExp->prepareDelete(true);
	preExp->prepareDelete(true);
	postExp->prepareDelete(true);
	delete exp;
	delete actualExp;
	delete preExp;
	delete postExp;
	std:: cout << "Finishing isMatching() from StatementWrite\n";
	return result;
}

StatementWrite::StatementWrite() {
	this->toPrint = nullptr;
}

TokenTypeRegistry* StatementWrite::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(StatementWrite::firstToken);
	return sequence;
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

bool StatementRead::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 4) return false;
	std:: cout << "Starting isMatching() from StatementRead\n";
	TokenSequence* sub = nullptr;
	TokenSequence* post = nullptr;
	TokenSequence* pre = sequence->splitOn(2, &sub);
	TokenSequence* core = sub->splitOn(sub->getSize()-2, &post);
	const int paranthType1 = 24;
	const int paranthType2 = 25;
	bool result = sequence->tokenAt(0, false)->getType() == StatementRead::firstToken->getType()
				&& sequence->tokenAt(1, false)->getType() == paranthType1
				&& sequence->tokenAt(2, false)->hasSameTypeAs(ParseTree::identifierToken)
				&& Index::isMatching(core)
				&& sequence->tokenAt(sequence->getSize()-1, false)->getType() == paranthType2;
	sub->prepareDelete(true);
	pre->prepareDelete(true);
	core->prepareDelete(true);
	post->prepareDelete(true);
	delete sub;
	delete pre;
	delete core;
	delete post;
	std:: cout << "Finishing isMatching() from StatementRead\n";
	return result;
}

StatementRead::StatementRead() {
	this->identifier = nullptr;
	this->index = nullptr;
}

TokenTypeRegistry* StatementRead::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(StatementRead::firstToken);
	return sequence;
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

bool StatementBlock::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 2) return false;
	std:: cout << "Starting isMatching() from StatementBlock\n";
	TokenSequence* suffix = nullptr;
	TokenSequence* brace1 = sequence->splitOn(0, &suffix);
	TokenSequence* brace2 = nullptr;
	TokenSequence* core = suffix->splitOn(suffix->getSize() - 2, &brace2);
	bool isCoreStatements = Statements::isMatching(core);
	const int braceCloseType = 27;
	suffix->prepareDelete(true);
	brace1->prepareDelete(true);
	core->prepareDelete(true);
	brace2->prepareDelete(true);
	delete suffix;
	delete brace1;
	delete core;
	delete brace2;
	std:: cout << "Finishing isMatching() from StatementBlock\n";
	return sequence->tokenAt(0, false)->hasSameTypeAs(StatementBlock::firstToken)
			&& sequence->tokenAt(sequence->getSize()-1, false)->getType() == braceCloseType
			&& isCoreStatements;
}

StatementBlock::StatementBlock() {
	this->blockContent = nullptr;
}

TokenTypeRegistry* StatementBlock::first() {
	TokenTypeRegistry *sequence = new TokenTypeRegistry();
	sequence->set(StatementBlock::firstToken);
	return sequence;
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

bool StatementIfElse::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 9) return false;
	std:: cout << "Starting isMatching() from StatementIfElse\n";
	// all necessary variables
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
	const int elseType = 34;
	const int paranthStartType = 24;
	const int paranthEndType = 25;
	bool currentOperationSucceeded = false;
	// try to locate the Else block
	for (int i = 1; i <= sequence->getSize(); i++) {
		majorPrefix = sequence->splitOn(sequence->getSize()-i, &elseStatement);
		ParseTree::splitIndexes->push(i);
		currentOperationSucceeded = (majorPrefix->tokenAt(majorPrefix->getSize()-1, false)->getType() == elseType
									&& Statement::isMatching(elseStatement));
		elseStatement->prepareDelete(true);
		delete elseStatement;
		if (currentOperationSucceeded) break;
		else {
			majorPrefix->prepareDelete(true);
			delete majorPrefix;
			ParseTree::splitIndexes->undoPushing();
		}
	}
	if (!currentOperationSucceeded) return false;
	// try to locate If block
	ifAndItsStatement = majorPrefix->splitOn(majorPrefix->getSize() - 3, &elsePart);
	majorPrefix->prepareDelete(true);
	delete majorPrefix;
	elsePart->prepareDelete(true);
	delete elsePart;
	if (!ifAndItsStatement->tokenAt(0, false)->hasSameTypeAs(StatementIfElse::firstToken) || ifAndItsStatement->tokenAt(1, false)->getType() != paranthStartType) {
		ifAndItsStatement->prepareDelete(true);
		delete ifAndItsStatement;
		std:: cout << "Finishing isMatching() from StatementIfElse\n";
		return false;
	}
	// final check: Can a constellation matching the "EXP)STATEMENT" pattern be found?
	ifPart = ifAndItsStatement->splitOn(1, &semiCore);
	ifAndItsStatement->prepareDelete(true);
	delete ifAndItsStatement;
	ifPart->prepareDelete(true);
	delete ifPart;
	for (int i = 0; i < semiCore->getSize() - 2; i++) {
		currentOperationSucceeded = true;
		ifExpression = semiCore->splitOn(i, &endOfIf);
		ParseTree::splitIndexes->push(i);
		if (!Exp::isMatching(ifExpression)) {
			ifExpression->prepareDelete(true);
			delete ifExpression;
			endOfIf->prepareDelete(true);
			delete endOfIf;
			currentOperationSucceeded = false;
			ParseTree::splitIndexes->undoPushing();
			continue;
		}
		ifExpression->prepareDelete(true);
		delete ifExpression;
		core = endOfIf->splitOn(0, &ifStatement);
		if (core->tokenAt(0, false)->getType() != paranthEndType || !Statement::isMatching(ifStatement)) currentOperationSucceeded = false;
		endOfIf->prepareDelete(true);
		delete endOfIf;
		core->prepareDelete(true);
		delete core;
		ifStatement->prepareDelete(true);
		delete ifStatement;
		if (currentOperationSucceeded) break;
		else ParseTree::splitIndexes->undoPushing();
	}
	semiCore->prepareDelete(true);
	delete semiCore;
	std:: cout << "Finishing isMatching() from StatementIfElse\n";
	return currentOperationSucceeded;
}

StatementIfElse::StatementIfElse() {
	this->condition = nullptr;
	this->thenCase = nullptr;
	this->elseCase = nullptr;
}

TokenTypeRegistry* StatementIfElse::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(StatementIfElse::firstToken);
	return sequence;
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

bool StatementWhile::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 6) return false;
	std::cout << "Starting isMatching() from StatementWhile\n";
	const int paranthStartType = 24;
	const int paranthEndType = 25;
	if (!sequence->tokenAt(0, false)->hasSameTypeAs(StatementWhile::firstToken)) return false;
	if (sequence->tokenAt(1, false)->getType() != paranthStartType) return false;
	TokenSequence* remainings = nullptr;
	TokenSequence* whileBeginning = sequence->splitOn(1, &remainings);
	TokenSequence* exp = nullptr;
	TokenSequence* parStat = nullptr;
	TokenSequence* paranth = nullptr;
	TokenSequence* statement = nullptr;
	whileBeginning->prepareDelete(true);
	delete whileBeginning;
	for (int i = 0; i < remainings->getSize()-1; i++) {
		exp = remainings->splitOn(i, &parStat);
		paranth = parStat->splitOn(0, &statement);
		parStat->prepareDelete(true);
		delete parStat;
		ParseTree::splitIndexes->push(i);
		if (Exp::isMatching(exp)
		    && paranth->tokenAt(0, false)->getType() == paranthEndType
			&& Statement::isMatching(statement)) {
			exp->prepareDelete(true);
			delete exp;
			paranth->prepareDelete(true);
			delete paranth;
			statement->prepareDelete(true);
			delete statement;
			std::cout << "Finishing isMatching() from StatementWhile\n";
			return true;
		}
		exp->prepareDelete(true);
		delete exp;
		paranth->prepareDelete(true);
		delete paranth;
		statement->prepareDelete(true);
		delete statement;
		ParseTree::splitIndexes->undoPushing();
	}
	remainings->prepareDelete(true);
	delete remainings;
	std::cout << "Finishing isMatching() from StatementWhile\n";
	return false;
}

StatementWhile::StatementWhile() {
	this->condition = nullptr;
	this->loop = nullptr;
}

TokenTypeRegistry* StatementWhile::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(StatementWhile::firstToken);
	return sequence;
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

bool ExpOnly::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 1) return false;
	std::cout << "Starting isMatching() from ExpOnly\n";
	TokenSequence* firstExp = nullptr;
	TokenSequence* operatingUnit = nullptr;
	bool combinationFound = false;
	for (int i = 0; i < sequence->getSize(); i++) {
		firstExp = sequence->splitOn(i, &operatingUnit);
		ParseTree::splitIndexes->push(i);
		combinationFound = (Exp2::isMatching(firstExp) && OpExp::isMatching(operatingUnit));
		firstExp->prepareDelete(true);
		delete firstExp;
		operatingUnit->prepareDelete(true);
		delete operatingUnit;
		if (combinationFound)break;
		ParseTree::splitIndexes->undoPushing();
	}
	std::cout << "Finishing isMatching() from ExpOnly\n";
	return combinationFound;
}

ExpOnly::ExpOnly() {
	this->rawExpression = nullptr;
	this->calculateWith = nullptr;
}

TokenTypeRegistry* ExpOnly::first() {
	return Exp2::first();
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

bool Exp2Nested::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 3) return false;
	std::cout << "Starting isMatching() from Exp2Nested\n";
	const int paranthEndType = 25;
	TokenSequence* end = nullptr;
	TokenSequence* beginParanth = sequence->splitOn(0, &end);
	TokenSequence* endParanth = nullptr;
	TokenSequence* subexp = end->splitOn(end->getSize() - 2, &endParanth);
	end->prepareDelete(true);
	delete end;
	if (beginParanth->tokenAt(0, false)->hasSameTypeAs(Exp2Nested::firstToken) && Exp::isMatching(subexp) && endParanth->tokenAt(0, false)->getType() == paranthEndType) {
		beginParanth->prepareDelete(true);
		delete beginParanth;
		subexp->prepareDelete(true);
		delete subexp;
		endParanth->prepareDelete(true);
		delete endParanth;
		std::cout << "Finishing isMatching() from Exp2Nested\n";
		return true;
	}
	beginParanth->prepareDelete(true);
	delete beginParanth;
	subexp->prepareDelete(true);
	delete subexp;
	endParanth->prepareDelete(true);
	delete endParanth;
	std::cout << "Finishing isMatching() from Exp2Nested\n";
	return false;
}

Exp2Nested::Exp2Nested() {
	this->nestedExpression = nullptr;
}

TokenTypeRegistry* Exp2Nested::first() {
	TokenTypeRegistry *sequence = new TokenTypeRegistry ();
	sequence->set(Exp2Nested::firstToken);
	return sequence;
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

bool Exp2Variable::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 1) return false;
	if (!sequence->tokenAt(0, false)->hasSameTypeAs(Exp2Variable::defaultIdentifier)) return false;
	std::cout << "Starting isMatching() from Exp2Variable\n";
	TokenSequence* notCheckedYet = nullptr;
	TokenSequence* precedingIdentifier = sequence->splitOn(0, &notCheckedYet);
	precedingIdentifier->prepareDelete(true);
	delete precedingIdentifier;
	if (Index::isMatching(notCheckedYet)) {
		notCheckedYet->prepareDelete(true);
		delete notCheckedYet;
		std::cout << "Finishing isMatching() from Exp2Variable\n";
		return true;
	}
	notCheckedYet->prepareDelete(true);
	delete notCheckedYet;
	std::cout << "Finishing isMatching() from Exp2Variable\n";
	return false;
}

Exp2Variable::Exp2Variable() {
	this->identifier = nullptr;
	this->index = nullptr;
}

TokenTypeRegistry* Exp2Variable::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(Exp2Variable::defaultIdentifier);
	return sequence;
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

void Exp2Constant::initStatic() {
	Exp2Constant::defaultInteger = ParseTree::integerToken;
}

bool Exp2Constant::isMatching(TokenSequence* sequence) {
	return sequence->getSize() == 1
			&& sequence->tokenAt(0, false)->hasSameTypeAs(Exp2Constant::defaultInteger);
}

Exp2Constant::Exp2Constant() {
	this->integer = nullptr;
}

TokenTypeRegistry* Exp2Constant::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(Exp2Constant::defaultInteger);
	return sequence;
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

bool Exp2NumericNegation::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 2) return false;
	if (!sequence->tokenAt(0, false)->hasSameTypeAs(Exp2NumericNegation::firstToken)) return false;
	std::cout << "Starting isMatching() from Exp2NumericNegation\n";
	TokenSequence* notCheckedYet = nullptr;
	TokenSequence* precedingNegator = sequence->splitOn(0, &notCheckedYet);
	precedingNegator->prepareDelete(true);
	delete precedingNegator;
	if (Exp2::isMatching(notCheckedYet)) {
		notCheckedYet->prepareDelete(true);
		delete notCheckedYet;
		std::cout << "Finishing isMatching() from Exp2NumericNegation\n";
		return true;
	}
	notCheckedYet->prepareDelete(true);
	delete notCheckedYet;
	std::cout << "Finishing isMatching() from Exp2NumericNegation\n";
	return false;
}

Exp2NumericNegation::Exp2NumericNegation() {
	this->toNegate = nullptr;
}

TokenTypeRegistry* Exp2NumericNegation::first() {
	TokenTypeRegistry *sequence = new TokenTypeRegistry ();
	sequence->set(Exp2NumericNegation::firstToken);
	return sequence;
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

bool Exp2LogicalNegation::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 2) return false;
	if (!sequence->tokenAt(0, false)->hasSameTypeAs(Exp2LogicalNegation::firstToken)) return false;
	std::cout << "Starting isMatching() from Exp2LogicalNegation\n";
	TokenSequence* notCheckedYet = nullptr;
	TokenSequence* precedingNegator = sequence->splitOn(0, &notCheckedYet);
	precedingNegator->prepareDelete(true);
	delete precedingNegator;
	if (Exp2::isMatching(notCheckedYet)) {
		notCheckedYet->prepareDelete(true);
		delete notCheckedYet;
		std::cout << "Finishing isMatching() from Exp2LogicalNegation\n";
		return true;
	}
	notCheckedYet->prepareDelete(true);
	delete notCheckedYet;
	std::cout << "Finishing isMatching() from Exp2LogicalNegation\n";
	return false;
}

Exp2LogicalNegation::Exp2LogicalNegation() {
	this->toNegate = nullptr;
}

TokenTypeRegistry* Exp2LogicalNegation::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(Exp2LogicalNegation::firstToken);
	return sequence;
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

bool IndexPosition::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 3) return false;
	std::cout << "Starting isMatching() from IndexPosition\n";
	const int bracketEndType = 29;
	TokenSequence* end = nullptr;
	TokenSequence* beginBracket = sequence->splitOn(0, &end);
	TokenSequence* endBracket = nullptr;
	TokenSequence* subexp = end->splitOn(end->getSize() - 2, &endBracket);
	delete end;
	if (beginBracket->tokenAt(0, false)->hasSameTypeAs(IndexPosition::firstToken) && Exp::isMatching(subexp) && endBracket->tokenAt(0, false)->getType() == bracketEndType) {
		beginBracket->prepareDelete(true);
		subexp->prepareDelete(true);
		endBracket->prepareDelete(true);
		delete beginBracket;
		delete subexp;
		delete endBracket;
		std::cout << "Finishing isMatching() from IndexPosition\n";
		return true;
	}
	beginBracket->prepareDelete(true);
	subexp->prepareDelete(true);
	endBracket->prepareDelete(true);
	delete beginBracket;
	delete subexp;
	delete endBracket;
	std::cout << "Finishing isMatching() from IndexPosition\n";
	return false;
}

IndexPosition::IndexPosition() {
	this->index = nullptr;
}

bool IndexPosition::isEps() {
	return false;
}

TokenTypeRegistry* IndexPosition::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(IndexPosition::firstToken);
	return sequence;
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

bool IndexEps::isMatching(TokenSequence* sequence) {
	for (int i = 0; i < sequence->getSize(); i++) { // empty sequence: loop completely skips -> true (as should be)
		if (sequence->tokenAt(i, false)->getType() != ParseTree::epsToken->getType()) return false;
	}
	return true; // pseudo code: return sequence->allTokens()->areEpsTokens();
}

IndexEps::IndexEps() {}

TokenTypeRegistry* IndexEps::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set (ParseTree::epsToken);
	return sequence;
}

bool IndexEps::isEps() {
	return true;
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

bool OpExpNext::isMatching(TokenSequence* sequence) {
	std::cout << "Starting isMatching() from OpExpNext\n";
	TokenSequence* expCandidate = nullptr;
	TokenSequence* opCandidate = sequence->splitOn(0, &expCandidate); // as OP is always 1 Token
	bool result = Op::isMatching(opCandidate) && Exp::isMatching(expCandidate);
	opCandidate->prepareDelete(true);
	delete opCandidate;
	expCandidate->prepareDelete(true);
	delete expCandidate;
	std::cout << "Finishing isMatching() from OpExpNext\n";
	return result;
}

OpExpNext::OpExpNext() {
	this->Operator = nullptr;
	this->operand = nullptr;
}

TokenTypeRegistry* OpExpNext::first() {
	return Op::first();
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

bool OpExpEps::isMatching(TokenSequence* sequence) {
	for (int i = 0; i < sequence->getSize(); i++) { // empty sequence: loop completely skips -> true (as should be)
		if (sequence->tokenAt(i, false)->getType() != ParseTree::epsToken->getType()) return false;
	}
	return true; // pseudo code: return sequence->allTokens()->areEpsTokens();
}

OpExpEps::OpExpEps() {}

TokenTypeRegistry* OpExpEps::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set (ParseTree::epsToken);
	return sequence;
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

bool OpPlus::isMatching(TokenSequence* sequence) {
	return sequence->getSize() == 1 && sequence->tokenAt(0, false)->hasSameTypeAs(OpPlus::firstToken);
}

OpPlus::OpPlus() {}

TokenTypeRegistry* OpPlus::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(OpPlus::firstToken);
	return sequence;
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

bool OpMinus::isMatching(TokenSequence* sequence) {
	return sequence->getSize() == 1 && sequence->tokenAt(0, false)->hasSameTypeAs(OpMinus::firstToken);
}

OpMinus::OpMinus() {}

TokenTypeRegistry* OpMinus::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(OpMinus::firstToken);
	return sequence;
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

bool OpMult::isMatching(TokenSequence* sequence) {
	return sequence->getSize() == 1 && sequence->tokenAt(0, false)->hasSameTypeAs(OpMult::firstToken);
}

OpMult::OpMult() {}

TokenTypeRegistry* OpMult::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(OpMult::firstToken);
	return sequence;
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

bool OpDiv::isMatching(TokenSequence* sequence) {
	return sequence->getSize() == 1 && sequence->tokenAt(0, false)->hasSameTypeAs(OpDiv::firstToken);
}

OpDiv::OpDiv() {}

TokenTypeRegistry* OpDiv::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(OpDiv::firstToken);
	return sequence;
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

bool OpLess::isMatching(TokenSequence* sequence) {
	return sequence->getSize() == 1 && sequence->tokenAt(0, false)->hasSameTypeAs(OpLess::firstToken);
}

OpLess::OpLess() {}

TokenTypeRegistry* OpLess::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(OpLess::firstToken);
	return sequence;
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

bool OpGreater::isMatching(TokenSequence* sequence) {
	return sequence->getSize() == 1 && sequence->tokenAt(0, false)->hasSameTypeAs(OpGreater::firstToken);
}

OpGreater::OpGreater() {}

TokenTypeRegistry* OpGreater::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(OpGreater::firstToken);
	return sequence;
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

bool OpEquals::isMatching(TokenSequence* sequence) {
	return sequence->getSize() == 1 && sequence->tokenAt(0, false)->hasSameTypeAs(OpEquals::firstToken);
}

OpEquals::OpEquals() {}

TokenTypeRegistry* OpEquals::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(OpEquals::firstToken);
	return sequence;
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

bool OpNotEquals::isMatching(TokenSequence* sequence) {
	return sequence->getSize() == 1 && sequence->tokenAt(0, false)->hasSameTypeAs(OpNotEquals::firstToken);
}

OpNotEquals::OpNotEquals() {}

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

bool OpAnd::isMatching(TokenSequence* sequence) {
	return sequence->getSize() == 1 && sequence->tokenAt(0, false)->hasSameTypeAs(OpAnd::firstToken);
}

OpAnd::OpAnd() {}

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
