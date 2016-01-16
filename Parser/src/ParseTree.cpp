/*
 * ParseTree.cpp
 *
 *  Created on: 29.12.2015
 *      Author: Domi
 */

#include "../includes/ParseTree.h"

void ParseTree::initStatic() { // to be called on Parser launch
	ParseTree::epsToken = EPSILON_TOKEN;
	ParseTree::bracketsToken = TYPE_REFERENCE_TOKEN_BRACKETS_START;
	ParseTree::minusToken = TYPE_REFERENCE_TOKEN_MINUS;
	Prog::initStatic();
}

bool ParseTree::isMatching(TokenSequence* sequence) {
	return false; // no rule corresponding to abstract ParseTree
}

TokenTypeRegistry* ParseTree::first() {
	return nullptr; // no actual first() of abstract ParseTree
}

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
	TokenSequence* sub1 = nullptr;
	TokenSequence* sub2 = nullptr;
	for (int i = -1; i <= sequence->getSize(); i++) {
		sub1 = sequence->splitOn(i, &sub2);
		if (Decls::isMatching(sub1) && Statements::isMatching(sub2)) {
			delete sub1;
			delete sub2;
			return true;
		} else {
			delete sub1;
			delete sub2;
		}
	}
	return false;
}

ProgOnly::ProgOnly() {
	this->declarationSegment = nullptr;
	this->statementSegment = nullptr;
}

TokenTypeRegistry* ProgOnly::first() {
	TokenTypeRegistry* registry = Decls::first();
	registry->uniteWith(Statements::first()); // Decls::first() contains Epsilon, Statements::first() too so no need to remove it before merging
	return registry;
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
	TokenSequence* sub1 = nullptr;
	TokenSequence* sub2 = nullptr;
	TokenSequence* sub3 = nullptr;
	TokenSequence* sub4 = nullptr;
	int semicolonTokenType = 0; // TODO change to actual type of Semicolon Token
	for (int i = 0; i < sequence->getSize(); i++) {
		sub1 = sequence->splitOn(i, &sub2);
		sub3 = sub2->splitOn(0, &sub4);
		if (Decl::isMatching(sub1) && sub3->tokenAt(0, false)->getType() == semicolonTokenType && Decls::isMatching(sub4)) {
			delete sub1;
			delete sub2;
			delete sub3;
			delete sub4;
			return true;
		} else {
			delete sub1;
			delete sub2;
			delete sub3;
			delete sub4;
		}
	}
	return false;
}

DeclsSeq::DeclsSeq() {
	this->firstDeclaration = nullptr;
	this->restOfDeclarations = nullptr;
}

TokenTypeRegistry* DeclsSeq::first() {
	return Decl::first(); // no Epsilon in Decl::first()
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

DeclsEps::~DeclsEps() {}

void DeclOnly::initStatic() {
	DeclOnly::firstToken  = TYPE_REFERENCE_TOKEN_INT;
	Array::initStatic();
}

bool DeclOnly::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 2) return false;
	TokenSequence* subPostInt = nullptr;
	TokenSequence* useless1 = sequence->splitOn(1, &subPostInt);
	TokenSequence* useless2 = nullptr;
	TokenSequence* array = subPostInt->splitOn(subPostInt->getSize() - 2, &useless2);
	int semicolonTokenType = 0; // TODO change to actual type of Semicolon Token
	bool result = sequence->tokenAt(0, false)->getType() == DeclOnly::firstToken->getType()
			&& sequence->tokenAt(1, false)->getType() == ParseTree::identifierToken->getType()
			&& Array::isMatching(array)
			&& sequence->tokenAt(sequence->getSize()-1,false)->getType() == semicolonTokenType;
	delete useless1;
	delete useless2;
	delete subPostInt;
	delete array;
	return result;
}

DeclOnly::DeclOnly() {
	this->identifier = nullptr; // will be set by Parser in the next isMatching() step
	this->size = nullptr; // will be set by Parser in the next isMatching() step
}

TokenTypeRegistry* DeclOnly::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry();
    sequence->set(DeclOnly::firstToken);
    return sequence;
}

DeclOnly::~DeclOnly() {
	delete this->identifier;
	delete this->size;
}

void ArrayIndex::initStatic() {
	ArrayIndex::firstToken = ParseTree::bracketsToken;
}

bool ArrayIndex::isMatching(TokenSequence* sequence) {
	int bracketsEndTokenType = 0; // TODO change to actual type of Brackets] Token
	return sequence->getSize() == 3
			&& sequence->tokenAt(0, false)->getType() == ArrayIndex::firstToken->getType()
			&& sequence->tokenAt(1, false)->getType() == ParseTree::integerToken->getType()
			&& sequence->tokenAt(2, false)->getType() == bracketsEndTokenType;
}

ArrayIndex::ArrayIndex() {
	this->integer = nullptr;
}

TokenTypeRegistry* ArrayIndex::first() {
	TokenTypeRegistry* sequence = new TokenTypeRegistry ();
	sequence->set(ArrayIndex::firstToken);
	return sequence;
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
	TokenTypeRegistry sequence = new TokenTypeRegistry ();
	sequence.set (ParseTree::epsToken);
	return sequence;
}

ArrayEps::~ArrayEps() {}

void StatementsSeq::initStatic() {
	Statement::initStatic();
}

bool StatementsSeq::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 3) return false;
	TokenSequence* sub1 = nullptr;
	TokenSequence* sub2 = nullptr;
	TokenSequence* sub3 = nullptr;
	TokenSequence* sub4 = nullptr;
	int semicolonTokenType = 0; // TODO change to actual type of Semicolon Token
	for (int i = 0; i < sequence->getSize(); i++) {
		sub1 = sequence->splitOn(i, &sub2);
		sub3 = sub2->splitOn(0, &sub4);
		if (Statement::isMatching(sub1) && sub3->tokenAt(0, false)->getType() == semicolonTokenType && Statements::isMatching(sub4)) {
			delete sub1;
			delete sub2;
			delete sub3;
			delete sub4;
			return true;
		} else {
			delete sub1;
			delete sub2;
			delete sub3;
			delete sub4;
		}
	}
	return false;
}

StatementsSeq::StatementsSeq() {
	this->firstStatement = nullptr;
	this->restOfStatements = nullptr;
}

TokenTypeRegistry* StatementsSeq::first() {
	return Statement::first();
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

StatementsEps::~StatementsEps() {}

void StatementSetValue::initStatic() {
	// TODO initialize defaultIdentifier
	Index::initStatic();
	Exp::initStatic();
}

bool StatementSetValue::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 3) return false;
	TokenSequence* sub1 = nullptr;
	TokenSequence* sub2 = nullptr;
	TokenSequence* sub3 = nullptr;
	TokenSequence* sub4 = nullptr;
	TokenSequence* sub5 = nullptr;
	TokenSequence* sub6 = nullptr;
	int paranthType = 0; // TODO set to actual Token type of "("
	int assignType = 0; // TODO set to actual Token type of ":="
	sub1 = sequence->splitOn(1, &sub2);
	if (sub1->tokenAt(0, false)->getType() != StatementSetValue::defaultIdentifier->getType()) return false;
	if (sub1->tokenAt(1, false)->getType() !=paranthType) return false;
	for (int i = 0; i < sub2->getSize(); i++) {
		sub3 = sub2->splitOn(i, &sub4);
		sub5 = sub4->splitOn(0, &sub6);
		if (Index::isMatching(sub3) && sub5->tokenAt(0, false)->getType() == assignType && Exp::isMatching(sub6)) return true;
	}
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
	TokenSequence* exp = nullptr;
	TokenSequence* preExp = sequence->splitOn(1, &exp);
	TokenSequence* postExp = nullptr;
	TokenSequence* actualExp = exp->splitOn(exp->getSize() - 2, &postExp);
	int paranthType1 = 0; // TODO change to actual type of "("
	int paranthType2 = 0; // TODO change to actual type of ")"
	bool result = sequence->tokenAt(0, false)->getType() == StatementWrite::firstToken->getType()
			&& sequence->tokenAt(1, false)->getType() == paranthType1
			&& Exp::isMatching(actualExp)
			&& sequence->tokenAt(sequence->getSize()-1, false)->getType() == paranthType2;
	delete exp;
	delete actualExp;
	delete preExp;
	delete postExp;
	return result;
}

StatementWrite::StatementWrite() {
	this->toPrint = nullptr;
}

TokenTypeRegistry* StatementWrite::first() {
	TokenTypeRegistry sequence = new TokenTypeRegistry ();
	sequence.set(StatementWrite::firstToken);
	return sequence;
}

StatementWrite::~StatementWrite() {
	delete this->toPrint;
}

void StatementRead::initStatic() {
	StatementRead::firstToken = TYPE_REFERENCE_TOKEN_READ;
}

bool StatementRead::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 4) return false;
	TokenSequence* sub = nullptr;
	TokenSequence* post = nullptr;
	TokenSequence* pre = sequence->splitOn(1, &sub);
	TokenSequence* core = sub->splitOn(sub->getSize()-2, &post);
	int paranthType1 = 0; // TODO change to actual type of "("
	int paranthType2 = 0; // TODO change to actual type of ")"
	bool result = sequence->tokenAt(0, false)->getType() == StatementRead::firstToken->getType()
				&& sequence->tokenAt(1, false)->getType() == paranthType1
				&& Exp::isMatching(core)
				&& sequence->tokenAt(sequence->getSize()-1, false)->getType() == paranthType2;
	delete sub;
	delete pre;
	delete core;
	delete post;
	return result;
}

StatementRead::StatementRead() {
	this->identifier = nullptr;
	this->index = nullptr;
}

TokenTypeRegistry* StatementRead::first() {
	TokenTypeRegistry sequence = new TokenTypeRegistry ();
	sequence.set(StatementRead::firstToken);
	return sequence;
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
	TokenSequence* suffix = nullptr;
	TokenSequence* brace1 = sequence->splitOn(0, &suffix);
	TokenSequence* brace2 = nullptr;
	TokenSequence* core = suffix->splitOn(suffix->getSize() - 2, &brace2);
	bool isCoreExp = Exp::isMatching(core);
	int braceCloseType = 0; // TODO set to
	delete suffix;
	delete brace1;
	delete core;
	delete brace2;
	return sequence->tokenAt(0, false)->hasSameTypeAs(StatementBlock::firstToken)
			&& sequence->tokenAt(sequence->getSize()-1, false)->getType() == braceCloseType
			&& isCoreExp;
}

StatementBlock::StatementBlock() {
	this->blockContent = nullptr;
}

TokenTypeRegistry* StatementBlock::first() {
	TokenTypeRegistry sequence = new TokenTypeRegistry();
	sequence.set(StatementBlock::firstToken);
	return sequence;
}

StatementBlock::~StatementBlock() {
	delete this->blockContent;
}

void StatementIfElse::initStatic() {
	StatementIfElse::firstToken = TYPE_REFERENCE_TOKEN_IF;
}

bool StatementIfElse::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 9) return false;
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
	int elseType = 0; // TODO type of "else"
	int paranthStartType = 0; // TODO type of "}"
	int paranthEndType = 0; // TODO type of ")"
	bool currentOperationSucceeded = false;
	// try to locate the Else block
	for (int i = 1; i <= sequence->getSize(); i++) {
		majorPrefix = sequence->splitOn(sequence->getSize()-i, &elseStatement);
		currentOperationSucceeded = (majorPrefix->tokenAt(majorPrefix->getSize()-1, false)->getType() == elseType
									&& Statement::isMatching(elseStatement));
		delete elseStatement;
		if (currentOperationSucceeded) break;
		else delete majorPrefix;
	}
	if (!currentOperationSucceeded) return false;
	// try to locate If block
	ifAndItsStatement = majorPrefix->splitOn(majorPrefix->getSize() - 3, &elsePart);
	delete majorPrefix;
	delete elsePart;
	if (!ifAndItsStatement->tokenAt(0, false)->hasSameTypeAs(StatementIfElse::firstToken) || ifAndItsStatement->tokenAt(1, false)->getType() != paranthStartType) {
		delete ifAndItsStatement;
		return false;
	}
	// final check: Can a constellation matching the "EXP)STATEMENT" pattern be found?
	ifPart = ifAndItsStatement->splitOn(1, &semiCore);
	delete ifAndItsStatement;
	delete ifPart;
	for (int i = 0; i < semiCore->getSize() - 2; i++) {
		currentOperationSucceeded = true;
		ifExpression = semiCore->splitOn(i, &endOfIf);
		if (!Exp::isMatching(ifExpression)) {
			delete ifExpression;
			delete semiCore;
			delete endOfIf;
			currentOperationSucceeded = false;
			continue;
		}
		delete ifExpression;
		delete semiCore;
		core = endOfIf->splitOn(0, &ifStatement);
		if (core->tokenAt(0, false)->getType() != paranthEndType || !Statement::isMatching(ifStatement)) currentOperationSucceeded = false;
		delete endOfIf;
		delete core;
		delete ifStatement;
		if (currentOperationSucceeded) break;
	}
	return currentOperationSucceeded;
}

StatementIfElse::StatementIfElse() {
	this->condition = nullptr;
	this->thenCase = nullptr;
	this->elseCase = nullptr;
}

TokenTypeRegistry* StatementIfElse::first() {
	TokenTypeRegistry sequence = new TokenTypeRegistry ();
	sequence.set(StatementIfElse::firstToken);
	return sequence;
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
	int paranthStartType = 0; // TODO type of "("
	int paranthEndType = 0; // TODO type of ")"
	if (!sequence->tokenAt(0, false)->hasSameTypeAs(StatementWhile::firstToken)) return false;
	if (sequence->tokenAt(1, false)->getType() != paranthStartType) return false;
	TokenSequence* remainings = nullptr;
	TokenSequence* whileBeginning = sequence->splitOn(1, &remainings);
	TokenSequence* exp = nullptr;
	TokenSequence* parStat = nullptr;
	TokenSequence* paranth = nullptr;
	TokenSequence* statement = nullptr;
	for (int i = 0; i < remainings->getSize()-1; i++) {
		exp = remainings->splitOn(i, &parStat);
		paranth = parStat->splitOn(0, &statement);
		delete parStat;
		if (Exp::isMatching(exp)
		    && paranth->tokenAt(0, false) == paranthEndType
			&& Statement::isMatching(statement)) {
			delete exp;
			delete paranth;
			delete statement;
			return true;
		}
	}
	return false;
}

StatementWhile::StatementWhile() {
	this->condition = nullptr;
	this->loop = nullptr;
}

TokenTypeRegistry* StatementWhile::first() {
	TokenTypeRegistry sequence = new TokenTypeRegistry ();
	sequence.set(StatementWhile::firstToken);
	return sequence;
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
	TokenSequence* firstExp = nullptr;
	TokenSequence* operatingUnit = nullptr;
	bool combinationFound = false;
	for (int i = 0; i < sequence->getSize(); i++) {
		firstExp = sequence->splitOn(i, &operatingUnit);
		combinationFound = (Exp2::isMatching(firstExp) && OpExp::isMatching(operatingUnit));
		delete firstExp;
		delete operatingUnit;
		if (combinationFound) break;
	}
	return combinationFound;
}

ExpOnly::ExpOnly() {
	this->rawExpression = nullptr;
	this->calculateWith = nullptr;
}

TokenTypeRegistry* ExpOnly::first() {
	return Exp2::first();
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
	int paranthEndType = 0; // TODO type of ")"
	TokenSequence* end = nullptr;
	TokenSequence* beginParanth = sequence->splitOn(0, &end);
	TokenSequence* endParanth = nullptr;
	TokenSequence* subexp = end->splitOn(end->getSize() - 2, &endParanth);
	delete end;
	if (beginParanth->tokenAt(0, false)->hasSameTypeAs(Exp2Nested::firstToken) && Exp::isMatching(subexp) && endParanth->tokenAt(0, false)->getType() == paranthEndType) {
		delete beginParanth;
		delete subexp;
		delete endParanth;
		return true;
	}
	delete beginParanth;
	delete subexp;
	delete endParanth;
	return false;
}

Exp2Nested::Exp2Nested() {
	this->nestedExpression = nullptr;
}

TokenTypeRegistry* Exp2Nested::first() {
	TokenTypeRegistry sequence = new TokenTypeRegistry ();
	sequence.set(Exp2Nested::firstToken);
	return sequence;
}

Exp2Nested::~Exp2Nested() {
	delete this->nestedExpression;
}

void Exp2Variable::initStatic() {
	// TODO initialize defaultIdentifier
}

bool Exp2Variable::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 1) return false;
	if (!sequence->tokenAt(0, false)->hasSameTypeAs(Exp2Variable::defaultIdentifier)) return false;
	TokenSequence* notCheckedYet = nullptr;
	TokenSequence* precedingIdentifier = sequence->splitOn(0, &notCheckedYet);
	delete precedingIdentifier;
	if (Index::isMatching(notCheckedYet)) {
		delete notCheckedYet;
		return true;
	}
	delete notCheckedYet;
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

Exp2Variable::~Exp2Variable() {
	delete this->identifier;
	delete this->index;
}

void Exp2Constant::initStatic() {
	// TODO initialize defaultInteger
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

Exp2Constant::~Exp2Constant() {
	delete this->integer;
}

void Exp2NumericNegation::initStatic() {
	Exp2NumericNegation::firstToken = ParseTree::minusToken;
}

bool Exp2NumericNegation::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 2) return false;
	if (!sequence->tokenAt(0, false)->hasSameTypeAs(Exp2NumericNegation::firstToken)) return false;
	TokenSequence* notCheckedYet = nullptr;
	TokenSequence* precedingNegator = sequence->splitOn(0, &notCheckedYet);
	delete precedingNegator;
	if (Exp2::isMatching(notCheckedYet)) {
		delete notCheckedYet;
		return true;
	}
	delete notCheckedYet;
	return false;
}

Exp2NumericNegation::Exp2NumericNegation() {
	this->toNegate = nullptr;
}

TokenTypeRegistry* Exp2NumericNegation::first() {
	TokenTypeRegistry sequence = new TokenTypeRegistry ();
	sequence.set(Exp2NumericNegation::firstToken);
	return sequence;
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
	TokenSequence* notCheckedYet = nullptr;
	TokenSequence* precedingNegator = sequence->splitOn(0, &notCheckedYet);
	delete precedingNegator;
	if (Exp2::isMatching(notCheckedYet)) {
		delete notCheckedYet;
		return true;
	}
	delete notCheckedYet;
	return false;
}

Exp2LogicalNegation::Exp2LogicalNegation() {
	this->toNegate = nullptr;
}

TokenTypeRegistry* Exp2LogicalNegation::first() {
	TokenTypeRegistry sequence = new TokenTypeRegistry ();
	sequence.set(Exp2LogicalNegation::firstToken);
	return sequence;
}

Exp2LogicalNegation::~Exp2LogicalNegation() {
	delete this->toNegate;
}

void IndexPosition::initStatic() {
	IndexPosition::firstToken = ParseTree::bracketsToken;
}

bool IndexPosition::isMatching(TokenSequence* sequence) {
	if (sequence->getSize() < 3) return false;
	int bracketEndType = 0; // TODO type of ")"
	TokenSequence* end = nullptr;
	TokenSequence* beginBracket = sequence->splitOn(0, &end);
	TokenSequence* endBracket = nullptr;
	TokenSequence* subexp = end->splitOn(end->getSize() - 2, &endBracket);
	delete end;
	if (beginBracket->tokenAt(0, false)->hasSameTypeAs(IndexPosition::firstToken) && Exp::isMatching(subexp) && endBracket->tokenAt(0, false)->getType() == bracketEndType) {
		delete beginBracket;
		delete subexp;
		delete endBracket;
		return true;
	}
	delete beginBracket;
	delete subexp;
	delete endBracket;
	return false;
}

IndexPosition::IndexPosition() {
	this->index = nullptr;
}

TokenTypeRegistry* IndexPosition::first() {
	TokenTypeRegistry sequence = new TokenTypeRegistry ();
	sequence.set(IndexPosition::firstToken);
	return sequence;
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

IndexEps::~IndexEps() {}

void OpExpNext::initStatic() {
	Op::initStatic();
}

bool OpExpNext::isMatching(TokenSequence* sequence) {
	TokenSequence* expCandidate = nullptr;
	TokenSequence* opCandidate = sequence->splitOn(0, &expCandidate); // as OP is always 1 Token
	bool result = Op::isMatching(opCandidate) && Exp::isMatching(expCandidate);
	delete opCandidate;
	delete expCandidate;
	return result;
}

OpExpNext::OpExpNext() {
	this->Operator = nullptr;
	this->operand = nullptr;
}

TokenTypeRegistry* OpExpNext::first() {
	return Op::first();
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

OpLess::~OpLess() {}

void OpGreater::initStatic() {
	OpGreater::firstToken = TYPE_REFERENCE_TOKEN_GREATER;
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

OpGreater::~OpGreater() {}

void OpEquals::initStatic() {
	OpEquals::firstToken = TYPE_REFERENCE_TOKEN_EQUALS;
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

OpEquals::~OpEquals() {}

void OpNotEquals::initStatic() {
	OpNotEquals::firstToken = TYPE_REFERENCE_TOKEN_NOT_EQUALS;
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

OpAnd::~OpAnd() {}
