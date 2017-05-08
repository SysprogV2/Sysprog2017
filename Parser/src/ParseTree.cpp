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
