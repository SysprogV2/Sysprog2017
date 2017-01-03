/*
 * ParseTree.h
 *
 * Created retyping the ParseTree_h.txt template. Methods will be added as necessary.
 *
 *  Created on: 29.12.2015
 *      Author: ehx
 */

#ifndef PARSER_INCLUDES_PARSETREE_H_
#define PARSER_INCLUDES_PARSETREE_H_

#include "TokenSequence.h"
#include "Errors.h"
#include "../../Symboltable/includes/Symboltable.h"
#include "../../Buffer/includes/Buffer.h"

#include <iostream>
#include <fstream>

#define TYPE_REFERENCE_TOKEN_INT new Token (32, 0, 0)
#define TYPE_REFERENCE_TOKEN_BRACKETS_START new Token (28, 0, 0)
#define TYPE_REFERENCE_TOKEN_WRITE new Token (33, 0, 0)
#define TYPE_REFERENCE_TOKEN_READ new Token (35, 0, 0)
#define TYPE_REFERENCE_TOKEN_BRACES_START new Token (26, 0, 0)
#define TYPE_REFERENCE_TOKEN_IF new Token (30, 0, 0)
#define TYPE_REFERENCE_TOKEN_WHILE new Token (31, 0, 0)
#define TYPE_REFERENCE_TOKEN_PARANTH_START new Token (24, 0, 0)
#define TYPE_REFERENCE_TOKEN_MINUS new Token (20, 0, 0)
#define TYPE_REFERENCE_TOKEN_NOT new Token (21, 0, 0)
#define TYPE_REFERENCE_TOKEN_PLUS new Token (19, 0, 0)
#define TYPE_REFERENCE_TOKEN_MULT new Token (13, 0, 0)
#define TYPE_REFERENCE_TOKEN_DIV new Token (5, 0, 0)
#define TYPE_REFERENCE_TOKEN_LESS new Token (3, 0, 0)
#define TYPE_REFERENCE_TOKEN_GREATER new Token (4, 0, 0)
#define TYPE_REFERENCE_TOKEN_EQUALS new Token (6, 0, 0)
#define TYPE_REFERENCE_TOKEN_NOT_EQUALS new Token (7, 0, 0)
#define TYPE_REFERENCE_TOKEN_AND new Token (22, 0, 0)
#define EPSILON_TOKEN new Token (18, 0, 0)
#define IDENTIFIER_DEFAULT_TOKEN new Token (1, 0, 0)
#define INTEGER_DEFAULT_TOKEN new Token (2, 0, 0)

#define ERROR_EXIT this->checkingType = errorType; return false;

class ParseTree {
protected:
	static Token* epsToken;
	static Token* bracketsToken;
	static Token* minusToken;
	static Token* integerToken;
	static Token* identifierToken;
	static Token* greaterToken;
	static Token* notEqualsToken;
	static Token* failureToken;
	static IntQueue* splitIndexes;
	static Symboltable* typeTable;
	static std::ofstream codeOutput;
	static LabelFactory* labelFactory;
	CheckableType checkingType;
public:
	static void initStatic();
	static TokenTypeRegistry* first();
	static void prepareTreeOperations();
	static void terminateTreeOperations();
	virtual ~ParseTree() = 0;
	virtual bool typeCheck() = 0;
	virtual void makeCode() = 0;
	void setChecktype (CheckableType type);
	CheckableType getChecktype();

};

class Prog : public ParseTree {
public:
	static void initStatic();
	static TokenTypeRegistry* first();
};

class Decls : public ParseTree {
public:
	static void initStatic();
    static TokenTypeRegistry* first();
    virtual bool isEps() = 0;
};

class Decl : public ParseTree {
public:
	static void initStatic();
    static TokenTypeRegistry* first();
};

class Array : public ParseTree {
public:
	static void initStatic();
	static TokenTypeRegistry* first();
	virtual bool isEps() = 0;
};

class Statements : public ParseTree {
public:
	static void initStatic();
	static TokenTypeRegistry* first();
	virtual bool isEps() = 0;
};

class Statement : public ParseTree {
public:
	static void initStatic();
	static TokenTypeRegistry* first();
};

class Exp : public ParseTree {
public:
	static void initStatic();
	static TokenTypeRegistry* first();
};

class Exp2 : public ParseTree {
public:
	static void initStatic();
	static TokenTypeRegistry* first();
};

class Index : public ParseTree {
public:
	static void initStatic();
	static TokenTypeRegistry* first();
	virtual bool isEps() = 0;
};

class OpExp : public ParseTree {
public:
	static void initStatic();
	static TokenTypeRegistry* first();
	virtual bool isEps() = 0;
};

class Op : public ParseTree {
public:
	static void initStatic();
	static TokenTypeRegistry* first();
};

class ProgOnly : public Prog {
private:
	Decls* declarationSegment;
	Statements* statementSegment;
public:
	static void initStatic();
	ProgOnly();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~ProgOnly();

};

class DeclsSeq : public Decls {
private:
	Decl* firstDeclaration;
	Decls* restOfDeclarations;
public:
	static void initStatic();
	DeclsSeq();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~DeclsSeq();

};

class DeclsEps : public Decls {
public:
	static void initStatic();
	DeclsEps();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~DeclsEps();

};

class DeclOnly : public Decl {
private:
	Array* size;
	Token* identifier;
	static Token* firstToken;
public:
	static void initStatic();
	DeclOnly();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~DeclOnly();

};

class ArrayIndex : public Array {
private:
	Token* integer;
	static Token* firstToken;
public:
	static void initStatic();
	ArrayIndex();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~ArrayIndex();

};

class ArrayEps : public Array {
public:
	static void initStatic();
	ArrayEps();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~ArrayEps();

};

class StatementsSeq : public Statements {
private:
	Statement* firstStatement;
	Statements* restOfStatements;
public:
	static void initStatic();
	StatementsSeq();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~StatementsSeq();

};

class StatementsEps : public Statements {
public:
	static void initStatic();
	StatementsEps();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~StatementsEps();

};

class StatementSetValue : public Statement {
private:
	Token* identifier;
	Index* index;
	Exp* aimValue;
	static Token* defaultIdentifier;
public:
	static void initStatic();
	StatementSetValue();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~StatementSetValue();

};

class StatementWrite : public Statement {
private:
	Exp* toPrint;
	static Token* firstToken;
public:
	static void initStatic();
	StatementWrite();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~StatementWrite();

};

class StatementRead : public Statement {
private:
	Token* identifier;
	Index* index;
	static Token* firstToken;
public:
	static void initStatic();
	StatementRead();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~StatementRead();

};

class StatementBlock : public Statement {
private:
	Statements* blockContent;
	static Token* firstToken;
public:
	static void initStatic();
	StatementBlock();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~StatementBlock();

};

class StatementIfElse : public Statement {
private:
	Exp* condition;
	Statement* thenCase;
	Statement* elseCase;
	static Token* firstToken;
public:
	static void initStatic();
	StatementIfElse();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~StatementIfElse();

};

class StatementWhile : public Statement {
private:
	Exp* condition;
	Statement* loop;
	static Token* firstToken;
public:
	static void initStatic();
	StatementWhile();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~StatementWhile();

};

class ExpOnly : public Exp {
private:
	Exp2* rawExpression;
	OpExp* calculateWith;
public:
	static void initStatic();
	ExpOnly();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~ExpOnly();

};

class Exp2Nested : public Exp2 {
private:
	Exp* nestedExpression;
	static Token* firstToken;
public:
	static void initStatic();
	Exp2Nested();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~Exp2Nested();

};

class Exp2Variable : public Exp2 {
private:
	Token* identifier;
	Index* index;
	static Token* defaultIdentifier;
public:
	static void initStatic();
	Exp2Variable();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~Exp2Variable();

};

class Exp2Constant : public Exp2 {
private:
	Token* integer;
	static Token* defaultInteger;
public:
	static void initStatic();
	Exp2Constant();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~Exp2Constant();

};

class Exp2NumericNegation : public Exp2 {
private:
	Exp2* toNegate;
	static Token* firstToken;
public:
	static void initStatic();
	Exp2NumericNegation();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~Exp2NumericNegation();

};

class Exp2LogicalNegation : public Exp2 {
private:
	Exp2* toNegate;
	static Token* firstToken;
public:
	static void initStatic();
	Exp2LogicalNegation();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~Exp2LogicalNegation();

};

class IndexPosition : public Index {
private:
	Exp* index;
	static Token* firstToken;
public:
	static void initStatic();
	IndexPosition();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~IndexPosition();

};

class IndexEps : public Index {
public:
	static void initStatic();
	IndexEps();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~IndexEps();

};

class OpExpNext : public OpExp {
	Op* Operator;
	Exp* operand;
public:
	static void initStatic();
	OpExpNext();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	bool isOperatorGreater();
	bool isOperatorNotEquals();
	~OpExpNext();

};

class OpExpEps : public OpExp {
public:
	static void initStatic();
	OpExpEps();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~OpExpEps();

};

class OpPlus : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpPlus();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpPlus();

};

class OpMinus : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpMinus();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpMinus();

};

class OpMult : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpMult();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpMult();

};

class OpDiv : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpDiv();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpDiv();

};

class OpLess : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpLess();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpLess();

};

class OpGreater : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpGreater();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpGreater();

};

class OpEquals : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpEquals();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpEquals();

};

class OpNotEquals : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpNotEquals();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpNotEquals();

};

class OpAnd : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpAnd();
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpAnd();

};

#endif /* PARSER_INCLUDES_PARSETREE_H_ */
