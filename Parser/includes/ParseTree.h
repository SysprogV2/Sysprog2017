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
#define EPSILON_TOKEN nullptr // TODO change to constructor of Epsilon Token

#define PFR friend class Parser;

class ParseTree {
protected:
	static Token* epsToken;
	static Token* bracketsToken;
	static Token* minusToken;
public:
	static void initStatic();
	static bool isMatching();
	static TokenSequence* first();
	virtual ~ParseTree() = 0;
	// later: virtual bool typeCheck() = 0;
	// later: virtual void makeCode() = 0;
};

class Prog : public ParseTree {
public:
	static void initStatic();
	static TokenSequence* first();
};

class Decls : public ParseTree {
public:
	static void initStatic();
    static TokenSequence* first();
};

class Decl : public ParseTree {
public:
	static void initStatic();
    static TokenSequence* first();
};

class Array : public ParseTree {
public:
	static void initStatic();
	static TokenSequence* first();
};

class Statements : public ParseTree {
public:
	static void initStatic();
	static TokenSequence* first();
};

class Statement : public ParseTree {
public:
	static void initStatic();
	static TokenSequence* first();
};

class Exp : public ParseTree {
public:
	static void initStatic();
	static TokenSequence* first();
};

class Exp2 : public ParseTree {
public:
	static void initStatic();
	static TokenSequence* first();
};

class Index : public ParseTree {
public:
	static void initStatic();
	static TokenSequence* first();
};

class OpExp : public ParseTree {
public:
	static void initStatic();
	static TokenSequence* first();
};

class Op : public ParseTree {
public:
	static void initStatic();
	static TokenSequence* first();
};

class ProgOnly : public Prog {
private:
	Decls* declarationSegment;
	Statements* statementSegment;
public:
	static void initStatic();
	ProgOnly();
	static bool isMatching();
	static TokenSequence* first();
	~ProgOnly();
	PFR
};

class DeclsSeq : public Decls {
private:
	Decl* firstDeclaration;
	Decls* restOfDeclarations;
public:
	static void initStatic();
	DeclsSeq();
	static bool isMatching();
	static TokenSequence* first();
	~DeclsSeq();
	PFR
};

class DeclsEps : public Decls {
public:
	static void initStatic();
	DeclsEps();
	static bool isMatching();
	static TokenSequence* first();
	~DeclsEps();
	PFR
};

class DeclOnly : public Decl {
private:
	Array* size;
	Token* identifier;
	static Token* firstToken;
public:
	static void initStatic();
	DeclOnly();
	static bool isMatching();
	static TokenSequence* first();
	~DeclOnly();
	PFR
};

class ArrayIndex : public Array {
private:
	Token* integer;
	static Token* firstToken;
public:
	static void initStatic();
	ArrayIndex();
	static bool isMatching();
	static TokenSequence* first();
	~ArrayIndex();
	PFR
};

class ArrayEps : public Array {
public:
	static void initStatic();
	ArrayEps();
	static bool isMatching();
	static TokenSequence* first();
	~ArrayEps();
	PFR
};

class StatementsSeq : public Statements {
private:
	Statement* firstStatement;
	Statements* restOfStatements;
public:
	static void initStatic();
	StatementsSeq();
	static bool isMatching();
	static TokenSequence* first();
	~StatementsSeq();
	PFR
};

class StatementsEps : public Statements {
public:
	static void initStatic();
	StatementsEps();
	static bool isMatching();
	static TokenSequence* first();
	~StatementsEps();
	PFR
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
	static bool isMatching();
	static TokenSequence* first();
	~StatementSetValue();
	PFR
};

class StatementWrite : public Statement {
private:
	Exp* toPrint;
	static Token* firstToken;
public:
	static void initStatic();
	StatementWrite();
	static bool isMatching();
	static TokenSequence* first();
	~StatementWrite();
	PFR
};

class StatementRead : public Statement {
private:
	Token* identifier;
	Index* index;
	static Token* firstToken;
public:
	static void initStatic();
	StatementRead();
	static bool isMatching();
	static TokenSequence* first();
	~StatementRead();
	PFR
};

class StatementBlock : public Statement {
private:
	Statements* blockContent;
	static Token* firstToken;
public:
	static void initStatic();
	StatementBlock();
	static bool isMatching();
	static TokenSequence* first();
	~StatementBlock();
	PFR
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
	static bool isMatching();
	static TokenSequence* first();
	~StatementIfElse();
	PFR
};

class StatementWhile : public Statement {
private:
	Exp* condition;
	Statement* loop;
	static Token* firstToken;
public:
	static void initStatic();
	StatementWhile();
	static bool isMatching();
	static TokenSequence* first();
	~StatementWhile();
	PFR
};

class ExpOnly : public Exp {
private:
	Exp2* rawExpression;
	OpExp* calculateWith;
public:
	static void initStatic();
	ExpOnly();
	static bool isMatching();
	static TokenSequence* first();
	~ExpOnly();
	PFR
};

class Exp2Nested : public Exp2 {
private:
	Exp* nestedExpression;
	static Token* firstToken;
public:
	static void initStatic();
	Exp2Nested();
	static bool isMatching();
	static TokenSequence* first();
	~Exp2Nested();
	PFR
};

class Exp2Variable : public Exp2 {
private:
	Token* identifier;
	Index* index;
	static Token* defaultIdentifier;
public:
	static void initStatic();
	Exp2Variable();
	static bool isMatching();
	static TokenSequence* first();
	~Exp2Variable();
	PFR
};

class Exp2Constant : public Exp2 {
private:
	Token* integer;
	static Token* defaultInteger;
public:
	static void initStatic();
	Exp2Constant();
	static bool isMatching();
	static TokenSequence* first();
	~Exp2Constant();
	PFR
};

class Exp2NumericNegation : public Exp2 {
private:
	Exp2* toNegate;
	static Token* firstToken;
public:
	static void initStatic();
	Exp2NumericNegation();
	static bool isMatching();
	static TokenSequence* first();
	~Exp2NumericNegation();
	PFR
};

class Exp2LogicalNegation : public Exp2 {
private:
	Exp2* toNegate;
	static Token* firstToken;
public:
	static void initStatic();
	Exp2LogicalNegation();
	static bool isMatching();
	static TokenSequence* first();
	~Exp2LogicalNegation();
	PFR
};

class IndexPosition : public Index {
private:
	Exp* index;
	static Token* firstToken;
public:
	static void initStatic();
	IndexPosition();
	static bool isMatching();
	static TokenSequence* first();
	~IndexPosition();
};

class IndexEps : public Index {
public:
	static void initStatic();
	IndexEps();
	static bool isMatching();
	static TokenSequence* first();
	~IndexEps();
	PFR
};

class OpExpNext : public OpExp {
	Op* Operator;
	Exp* operand;
public:
	static void initStatic();
	OpExpNext();
	static bool isMatching();
	static TokenSequence* first();
	~OpExpNext();
	PFR
};

class OpExpEps : public OpExp {
public:
	static void initStatic();
	OpExpEps();
	static bool isMatching();
	static TokenSequence* first();
	~OpExpEps();
	PFR
};

class OpPlus : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpPlus();
	static bool isMatching();
	static TokenSequence* first();
	~OpPlus();
	PFR
};

class OpMinus : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpMinus();
	static bool isMatching();
	static TokenSequence* first();
	~OpMinus();
	PFR
};

class OpMult : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpMult();
	static bool isMatching();
	static TokenSequence* first();
	~OpMult();
	PFR
};

class OpDiv : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpDiv();
	static bool isMatching();
	static TokenSequence* first();
	~OpDiv();
	PFR
};

class OpLess : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpLess();
	static bool isMatching();
	static TokenSequence* first();
	~OpLess();
	PFR
};

class OpGreater : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpGreater();
	static bool isMatching();
	static TokenSequence* first();
	~OpGreater();
	PFR
};

class OpEquals : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpEquals();
	static bool isMatching();
	static TokenSequence* first();
	~OpEquals();
	PFR
};

class OpNotEquals : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpNotEquals();
	static bool isMatching();
	static TokenSequence* first();
	~OpNotEquals();
	PFR
};

class OpAnd : public Op {
private:
	static Token* firstToken;
public:
	static void initStatic();
	OpAnd();
	static bool isMatching();
	static TokenSequence* first();
	~OpAnd();
	PFR
};

#endif /* PARSER_INCLUDES_PARSETREE_H_ */
