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

bool ParseTree::isMatching() {
	return false; // no rule corresponding to default ParseTree
}

TokenSequence* ParseTree::first() {
	return nullptr;
}

void Prog::initStatic() {
	ProgOnly::initStatic();
}

TokenSequence* Prog::first() {
	return ProgOnly::first();
}

void Decls::initStatic() {
	DeclsSeq::initStatic();
	DeclsEps::initStatic();
}

TokenSequence* Decls::first() {
	TokenSequence* sequence = DeclsSeq::first();
	sequence->add(ParseTree::epsToken, false);
	return sequence;
}

void Decl::initStatic() {
	DeclOnly::initStatic();
}

TokenSequence* Decl::first() {
	return DeclOnly::first();
}

void Array::initStatic() {
	ArrayIndex::initStatic();
	ArrayEps::initStatic();
}

TokenSequence* Array::first() {
	TokenSequence* sequence = ArrayIndex::first();
	sequence->add(ParseTree::epsToken, false);
	return sequence;
}

void Statements::initStatic() {
	StatementsSeq::initStatic();
	StatementsEps::initStatic();
}

TokenSequence* Statements::first() {
    TokenSequence* sequence = StatementsSeq::first();
    sequence->add(ParseTree::epsToken, false);
    return sequence;
}

void Statement::initStatic() {
	StatementSetValue::initStatic();
	StatementWrite::initStatic();
	StatementRead::initStatic();
	StatementBlock::initStatic();
	StatementIfElse::initStatic();
	StatementWhile::initStatic();
}

TokenSequence* Statement::first() {
	TokenSequence* sequence = StatementSetValue::first();
	// TODO add all of all Statement types' first() methods OR create newly and insert each Token
	// (perhaps version 2 is better because most types have a first() result of size 1)
	return sequence;
}

void Exp::initStatic() {
	ExpOnly::initStatic();
}

TokenSequence* Exp::first() {
	return ExpOnly::first();
}

void Exp2::initStatic() {
	Exp2Nested::initStatic();
	Exp2Variable::initStatic();
	Exp2Constant::initStatic();
	Exp2NumericNegation::initStatic();
	Exp2LogicalNegation::initStatic();
}

TokenSequence* Exp2::first() {
	TokenSequence* sequence = Exp2Nested::first();
	// TODO add each of the other case tokens
	return sequence;
}

void Index::initStatic() {
	IndexPosition::initStatic();
	IndexEps::initStatic();
}

TokenSequence* Index::first() {
	TokenSequence* sequence = IndexPosition::first();
	sequence->add(ParseTree::epsToken, false);
	return sequence;
}

void OpExp::initStatic() {
	OpExpNext::initStatic();
	OpExpEps::initStatic();
}

TokenSequence* OpExp::first() {
	TokenSequence* sequence = OpExpNext::first();
	sequence->add(ParseTree::epsToken, false);
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

TokenSequence* Op::first() {
	TokenSequence* sequence = OpPlus::first();
	// TODO add missing Tokens
	return sequence;
}

void ProgOnly::initStatic() {
	Decls::initStatic();
	Statements::initStatic();
}

ProgOnly::ProgOnly() {
	this->declarationSegment = nullptr;
	this->statementSegment = nullptr;
}

TokenSequence* ProgOnly::first() {
	TokenSequence* sequence = Decls::first();
	// TODO add all of Statements::first() to sequence (a declaration segment can be empty)
	return sequence;
}

ProgOnly::~ProgOnly() {
	delete this->declarationSegment;
	delete this->statementSegment;
}

void DeclsSeq::initStatic() {
	Decl::initStatic();
}

DeclsSeq::DeclsSeq() {
	this->firstDeclaration = nullptr;
	this->restOfDeclarations = nullptr;
}

TokenSequence* DeclsSeq::first() {
	return Decl::first();
}

DeclsSeq::~DeclsSeq() {
	delete this->firstDeclaration;
	delete this->restOfDeclarations;
}

void DeclsEps::initStatic() {}

DeclsEps::DeclsEps() {}

TokenSequence* DeclsEps::first() {
	TokenSequence* sequence = new TokenSequence (10, 10);
	sequence->add(DeclsEps::epsToken, false);
	return sequence;
}

DeclsEps::~DeclsEps() {}

void DeclOnly::initStatic() {
	DeclOnly::firstToken  = TYPE_REFERENCE_TOKEN_INT;
	Array::initStatic();
}

DeclOnly::DeclOnly() {
	this->identifier = nullptr; // will be set by Parser in the next isMatching() step
	this->size = nullptr; // will be set by Parser in the next isMatching() step
}

TokenSequence* DeclOnly::first() {
	TokenSequence* sequence = new TokenSequence (10, 10);
    sequence->add(DeclOnly::firstToken, false);
    return sequence;
}

DeclOnly::~DeclOnly() {
	delete this->identifier;
	delete this->size;
}

void ArrayIndex::initStatic() {
	ArrayIndex::firstToken = ParseTree::bracketsToken;
}

ArrayIndex::ArrayIndex() {
	this->integer = nullptr;
}

TokenSequence* ArrayIndex::first() {
	TokenSequence* sequence = new TokenSequence (10, 10);
	sequence->add(ArrayIndex::firstToken, false);
	return sequence;
}

ArrayIndex::~ArrayIndex() {
	delete this->integer;
}

void ArrayEps::initStatic() {}

ArrayEps::ArrayEps() {}

TokenSequence* ArrayEps::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add (ParseTree::epsToken, false);
	return sequence;
}

ArrayEps::~ArrayEps() {}

void StatementsSeq::initStatic() {
	Statement::initStatic();
}

StatementsSeq::StatementsSeq() {
	this->firstStatement = nullptr;
	this->restOfStatements = nullptr;
}

TokenSequence* StatementsSeq::first() {
	return Statement::first();
}

StatementsSeq::~StatementsSeq() {
	delete this->firstStatement;
	delete this->restOfStatements;
}

void StatementsEps::initStatic() {}

StatementsEps::StatementsEps() {}

TokenSequence* StatementsEps::first() {
	TokenSequence* sequence = new TokenSequence (10, 10);
	sequence->add (ParseTree::epsToken, false);
	return sequence;
}

StatementsEps::~StatementsEps() {}

void StatementSetValue::initStatic() {
	// TODO initialize defaultIdentifier
	Index::initStatic();
	Exp::initStatic();
}

StatementSetValue::StatementSetValue() {
	this->identifier = nullptr;
	this->index = nullptr;
	this->aimValue = nullptr;
}

TokenSequence* StatementSetValue::first() {
	TokenSequence* sequence = new TokenSequence (10, 10);
	sequence->add (StatementSetValue::defaultIdentifier, false);
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

StatementWrite::StatementWrite() {
	this->toPrint = nullptr;
}

TokenSequence* StatementWrite::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(StatementWrite::firstToken, false);
	return sequence;
}

StatementWrite::~StatementWrite() {
	delete this->toPrint;
}

void StatementRead::initStatic() {
	StatementRead::firstToken = TYPE_REFERENCE_TOKEN_READ;
}

StatementRead::StatementRead() {
	this->identifier = nullptr;
	this->index = nullptr;
}

TokenSequence* StatementRead::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(StatementRead::firstToken, false);
	return sequence;
}

StatementRead::~StatementRead() {
	delete this->identifier;
	delete this->index;
}

void StatementBlock::initStatic() {
	StatementBlock::firstToken = TYPE_REFERENCE_TOKEN_BRACES_START;
}

StatementBlock::StatementBlock() {
	this->blockContent = nullptr;
}

TokenSequence* StatementBlock::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(StatementBlock::firstToken, false);
	return sequence;
}

StatementBlock::~StatementBlock() {
	delete this->blockContent;
}

void StatementIfElse::initStatic() {
	StatementIfElse::firstToken = TYPE_REFERENCE_TOKEN_IF;
}

StatementIfElse::StatementIfElse() {
	this->condition = nullptr;
	this->thenCase = nullptr;
	this->elseCase = nullptr;
}

TokenSequence* StatementIfElse::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(StatementIfElse::firstToken, false);
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

StatementWhile::StatementWhile() {
	this->condition = nullptr;
	this->loop = nullptr;
}

TokenSequence* StatementWhile::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(StatementWhile::firstToken, false);
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

ExpOnly::ExpOnly() {
	this->rawExpression = nullptr;
	this->calculateWith = nullptr;
}

TokenSequence* ExpOnly::first() {
	return Exp2::first();
}

ExpOnly::~ExpOnly() {
	delete this->rawExpression;
	delete this->calculateWith;
}

void Exp2Nested::initStatic() {
	Exp2Nested::firstToken = TYPE_REFERENCE_TOKEN_PARANTH_START;
}

Exp2Nested::Exp2Nested() {
	this->nestedExpression = nullptr;
}

TokenSequence* Exp2Nested::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(Exp2Nested::firstToken, false);
	return sequence;
}

Exp2Nested::~Exp2Nested() {
	delete this->nestedExpression;
}

void Exp2Variable::initStatic() {
	// TODO initialize defaultIdentifier
}

Exp2Variable::Exp2Variable() {
	this->identifier = nullptr;
	this->index = nullptr;
}

TokenSequence* Exp2Variable::first() {
	TokenSequence* sequence = new TokenSequence (10, 10);
	sequence->add(Exp2Variable::defaultIdentifier, false);
	return sequence;
}

Exp2Variable::~Exp2Variable() {
	delete this->identifier;
	delete this->index;
}

void Exp2Constant::initStatic() {
	// TODO initialize defaultInteger
}

Exp2Constant::Exp2Constant() {
	this->integer = nullptr;
}

TokenSequence* Exp2Constant::first() {
	TokenSequence* sequence = new TokenSequence (10, 10);
	sequence->add(Exp2Constant::defaultInteger, false);
	return sequence;
}

Exp2Constant::~Exp2Constant() {
	delete this->integer;
}

void Exp2NumericNegation::initStatic() {
	Exp2NumericNegation::firstToken = ParseTree::minusToken;
}

Exp2NumericNegation::Exp2NumericNegation() {
	this->toNegate = nullptr;
}

TokenSequence* Exp2NumericNegation::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(Exp2NumericNegation::firstToken, false);
	return sequence;
}

Exp2NumericNegation::~Exp2NumericNegation() {
	delete this->toNegate;
}

void Exp2LogicalNegation::initStatic() {
	Exp2LogicalNegation::firstToken = TYPE_REFERENCE_TOKEN_NOT;
}

Exp2LogicalNegation::Exp2LogicalNegation() {
	this->toNegate = nullptr;
}

TokenSequence* Exp2LogicalNegation::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(Exp2LogicalNegation::firstToken, false);
	return sequence;
}

Exp2LogicalNegation::~Exp2LogicalNegation() {
	delete this->toNegate;
}

void IndexPosition::initStatic() {
	IndexPosition::firstToken = ParseTree::bracketsToken;
}

IndexPosition::IndexPosition() {
	this->index = nullptr;
}

TokenSequence* IndexPosition::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(IndexPosition::firstToken, false);
	return sequence;
}

IndexPosition::~IndexPosition() {
	delete this->index;
}

void IndexEps::initStatic() {}

IndexEps::IndexEps() {}

TokenSequence* IndexEps::first() {
	TokenSequence* sequence = new TokenSequence (10, 10);
	sequence->add (ParseTree::epsToken, false);
	return sequence;
}

IndexEps::~IndexEps() {}

void OpExpNext::initStatic() {
	Op::initStatic();
}

OpExpNext::OpExpNext() {
	this->Operator = nullptr;
	this->operand = nullptr;
}

TokenSequence* OpExpNext::first() {
	return Op::first();
}

OpExpNext::~OpExpNext() {
	delete this->Operator;
	delete this->operand;
}

void OpExpEps::initStatic() {}

OpExpEps::OpExpEps() {}

TokenSequence* OpExpEps::first() {
	TokenSequence* sequence = new TokenSequence (10, 10);
	sequence->add (ParseTree::epsToken, false);
	return sequence;
}

OpExpEps::~OpExpEps() {}

void OpPlus::initStatic() {
	OpPlus::firstToken = TYPE_REFERENCE_TOKEN_PLUS;
}

OpPlus::OpPlus() {}

TokenSequence* OpPlus::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(OpPlus::firstToken, false);
	return sequence;
}

OpPlus::~OpPlus() {}

void OpMinus::initStatic() {
	OpMinus::firstToken = ParseTree::minusToken;
}

OpMinus::OpMinus() {}

TokenSequence* OpMinus::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(OpMinus::firstToken, false);
	return sequence;
}

OpMinus::~OpMinus() {}

void OpMult::initStatic() {
	OpMult::firstToken = TYPE_REFERENCE_TOKEN_MULT;
}

OpMult::OpMult() {}

TokenSequence* OpMult::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(OpMult::firstToken, false);
	return sequence;
}

OpMult::~OpMult() {}

void OpDiv::initStatic() {
	OpDiv::firstToken = TYPE_REFERENCE_TOKEN_DIV;
}

OpDiv::OpDiv() {}

TokenSequence* OpDiv::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(OpDiv::firstToken, false);
	return sequence;
}

OpDiv::~OpDiv() {}

void OpLess::initStatic() {
	OpLess::firstToken = TYPE_REFERENCE_TOKEN_LESS;
}

OpLess::OpLess() {}

TokenSequence* OpLess::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(OpLess::firstToken, false);
	return sequence;
}

OpLess::~OpLess() {}

void OpGreater::initStatic() {
	OpGreater::firstToken = TYPE_REFERENCE_TOKEN_GREATER;
}

OpGreater::OpGreater() {}

TokenSequence* OpGreater::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(OpGreater::firstToken, false);
	return sequence;
}

OpGreater::~OpGreater() {}

void OpEquals::initStatic() {
	OpEquals::firstToken = TYPE_REFERENCE_TOKEN_EQUALS;
}

OpEquals::OpEquals() {}

TokenSequence* OpEquals::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(OpEquals::firstToken, false);
	return sequence;
}

OpEquals::~OpEquals() {}

void OpNotEquals::initStatic() {
	OpNotEquals::firstToken = TYPE_REFERENCE_TOKEN_NOT_EQUALS;
}

OpNotEquals::OpNotEquals() {}

TokenSequence* OpNotEquals::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(OpNotEquals::firstToken, false);
	return sequence;
}

OpNotEquals::~OpNotEquals() {}

void OpAnd::initStatic() {
	OpAnd::firstToken = TYPE_REFERENCE_TOKEN_AND;
}

OpAnd::OpAnd() {}

TokenSequence* OpAnd::first() {
	TokenSequence sequence = new TokenSequence (10, 10);
	sequence.add(OpAnd::firstToken, false);
	return sequence;
}

OpAnd::~OpAnd() {}
