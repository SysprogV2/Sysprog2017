/**
 * ParseTree.h
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
#include "../../Scanner/includes/Scanner.h"

#include <iostream>
#include <fstream>
#include "../../Scanner/includes/TokenTypeRegistry.h"

#define TYPE_REFERENCE_TOKEN_INT new Token (34, 0, 0)
#define TYPE_REFERENCE_TOKEN_BRACKETS_START new Token (29, 0, 0)
#define TYPE_REFERENCE_TOKEN_WRITE new Token (35, 0, 0)
#define TYPE_REFERENCE_TOKEN_READ new Token (36, 0, 0)
#define TYPE_REFERENCE_TOKEN_BRACES_START new Token (27, 0, 0)
#define TYPE_REFERENCE_TOKEN_IF new Token (31, 0, 0)
#define TYPE_REFERENCE_TOKEN_WHILE new Token (32, 0, 0)
#define TYPE_REFERENCE_TOKEN_PARANTH_START new Token (25, 0, 0)
#define TYPE_REFERENCE_TOKEN_MINUS new Token (20, 0, 0)
#define TYPE_REFERENCE_TOKEN_NOT new Token (21, 0, 0)
#define TYPE_REFERENCE_TOKEN_PLUS new Token (19, 0, 0)
#define TYPE_REFERENCE_TOKEN_MULT new Token (13, 0, 0)
#define TYPE_REFERENCE_TOKEN_DIV new Token (3, 0, 0)
#define TYPE_REFERENCE_TOKEN_LESS new Token (23, 0, 0)
#define TYPE_REFERENCE_TOKEN_GREATER new Token (24, 0, 0)
#define TYPE_REFERENCE_TOKEN_EQUALS new Token (4, 0, 0)
#define TYPE_REFERENCE_TOKEN_NOT_EQUALS new Token (7, 0, 0)
#define TYPE_REFERENCE_TOKEN_AND new Token (10, 0, 0)
#define TYPE_REFERENCE_TOKEN_SCOL new Token (22, 0, 0)
#define TYPE_REFERENCE_TOKEN_PARANTH_END new Token (26, 0, 0)
#define TYPE_REFERENCE_TOKEN_BRACKETS_END new Token (30, 0, 0)
#define TYPE_REFERENCE_TOKEN_ASGN new Token (8, 0, 0)
#define EPSILON_TOKEN new Token (5, 0, 0)
#define IDENTIFIER_DEFAULT_TOKEN new Token (1, 0, 0)
#define INTEGER_DEFAULT_TOKEN new Token (2, 0, 0)

// in typeCheck()
#define ERROR_EXIT this->checkingType = errorType; return false

/**
 * Represents the generic parse tree.
 */
class ParseTree {
protected:
	CheckableType checkingType;
public:
	static Token* epsToken;
	static Token* bracketsToken; // opening
	static Token* minusToken;
	static Token* integerToken;
	static Token* identifierToken;
	static Token* greaterToken;
	static Token* notEqualsToken;
    static Token* semicolonToken;
    static Token* paranthesisToken; // closing
	static Symboltable* typeTable;
	static std::ofstream codeOutput;
	static LabelFactory* labelFactory;
    static std::ofstream log;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	static TokenTypeRegistry* first();
	static void prepareTreeOperations();
	static void terminateTreeOperations();
	static void cleanupStatic();
	virtual ~ParseTree() = 0;
	virtual bool typeCheck() = 0;
	virtual void makeCode() = 0;
	void setChecktype (CheckableType type);
	CheckableType getChecktype();

};

/**
 * Represents the generic program, as defined by the PROG spec.
 */
class Prog : public ParseTree {
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	static TokenTypeRegistry* first();
};

/**
 * Represents the generic declaration segment, as defined by the DECLS spec.
 */
class Decls : public ParseTree {
public:
    /**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
    static TokenTypeRegistry* first();
    virtual bool isEps() = 0;
};

/**
 * Represents the generic declaration, as defined by the DECL spec.
 */
class Decl : public ParseTree {
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
    static TokenTypeRegistry* first();
};

/**
 * Represents the generic array modifier, as defined by the ARRAY spec.
 */
class Array : public ParseTree {
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	static TokenTypeRegistry* first();
	virtual bool isEps() = 0;
};

/**
 * Represents the generic statement segment, as defined by the STATEMENTS spec.
 */
class Statements : public ParseTree {
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	static TokenTypeRegistry* first();
	virtual bool isEps() = 0;
};

/**
 * Represents the generic statement, as defined by the STATEMENT spec.
 */
class Statement : public ParseTree {
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	static TokenTypeRegistry* first();
};

/**
 * Represents the generic expression, as defined by the EXP spec.
 */
class Exp : public ParseTree {
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	static TokenTypeRegistry* first();
};

/**
 * Represents the generic single subexpression, as defined by the EXP2 spec.
 */
class Exp2 : public ParseTree {
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	static TokenTypeRegistry* first();
};

/**
 * Represents the generic array index, as defined by the INDEX spec.
 */
class Index : public ParseTree {
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	static TokenTypeRegistry* first();
	virtual bool isEps() = 0;
};

/**
 * Represents the generic combined expression, as defined by the OP_EXP spec.
 */
class OpExp : public ParseTree {
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	static TokenTypeRegistry* first();
	virtual bool isEps() = 0;
};

/**
 * Represents the generic operator, as defined by the OP spec.
 */
class Op : public ParseTree {
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	static TokenTypeRegistry* first();
};

/**
 * Represents the rule `PROG ::= DECLS STATEMENTS`, i.e. the default program.
 */
class ProgOnly : public Prog {
private:
	Decls* declarationSegment;
	Statements* statementSegment;
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	ProgOnly(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~ProgOnly();

};

/**
 * Represents the rule `DECLS ::= DECL;DECLS`, i.e. the declaration sequence.
 */
class DeclsSeq : public Decls {
private:
	Decl* firstDeclaration;
	Decls* restOfDeclarations;
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	DeclsSeq(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~DeclsSeq();

};

/**
 * Represents the rule `DECLS ::= ε`, i.e. the empty declaration sequence.
 */
class DeclsEps : public Decls {
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	DeclsEps(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~DeclsEps();

};

/**
 * Represents the rule `DECL ::= int ARRAY identifier`, i.e. the default declaration.
 */
class DeclOnly : public Decl {
private:
	Array* size;
	Token* identifier;
public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	DeclOnly(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~DeclOnly();
	friend class ParseTree;
};

/**
 * Represents the rule `ARRAY ::= [integer]`, i.e. the existant array modifier.
 */
class ArrayIndex : public Array {
private:
	Token* integer;
public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	ArrayIndex(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~ArrayIndex();
	friend class ParseTree;

};

/**
 * Represents the rule `ARRAY ::= €`, i.e. the nonexistant array modifier.
 */
class ArrayEps : public Array {
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	ArrayEps(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~ArrayEps();

};

/**
 * Represents the rule `STATEMENTS ::= STATEMENT;STATEMENTS`, i.e. the statement sequence.
 */
class StatementsSeq : public Statements {
private:
	Statement* firstStatement;
	Statements* restOfStatements;
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	StatementsSeq(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~StatementsSeq();

};

/**
 * Represents the rule `STATEMENTS ::= ε`, i.e. the empty statement sequence.
 */
class StatementsEps : public Statements {
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	StatementsEps(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~StatementsEps();

};

/**
 * Represents the rule `STATEMENT ::= identifier INDEX := EXP`, i.e. the assignment.
 */
class StatementSetValue : public Statement {
private:
	Token* identifier;
	Index* index;
	Exp* aimValue;
public:
	static Token* defaultIdentifier;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	StatementSetValue(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~StatementSetValue();
	friend class ParseTree;

};

/**
 * Represents the rule `STATEMENT ::= write(EXP)`, i.e. the console output.
 */
class StatementWrite : public Statement {
private:
	Exp* toPrint;
public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	StatementWrite(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~StatementWrite();
	friend class ParseTree;

};

/**
 * Represents the rule `STATEMENT ::= read(identifier INDEX)`, i.e. the console input.
 */
class StatementRead : public Statement {
private:
	Token* identifier;
	Index* index;
public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	StatementRead(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~StatementRead();
	friend class ParseTree;

};

/**
 * Represents the rule `STATEMENT ::= {STATEMENTS}`, i.e. the block of statements.
 */
class StatementBlock : public Statement {
private:
	Statements* blockContent;
public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	StatementBlock(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~StatementBlock();
	friend class ParseTree;

};

/**
 * Represents the rule `STATEMENT ::= if(EXP)STATEMENT else STATEMENT`, i.e. the conditional flow fork.
 */
class StatementIfElse : public Statement {
private:
	Exp* condition;
	Statement* thenCase;
	Statement* elseCase;
public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	StatementIfElse(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~StatementIfElse();
	friend class ParseTree;

};

/**
 * Represents the rule `while(EXP) STATEMENT`, i.e. the flow loop.
 */
class StatementWhile : public Statement {
private:
	Exp* condition;
	Statement* loop;
public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	StatementWhile(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~StatementWhile();
	friend class ParseTree;

};

/**
 * Represents the rule `EXP ::= EXP2 OP_EXP`, i.e. the default expression.
 */
class ExpOnly : public Exp {
private:
	Exp2* rawExpression;
	OpExp* calculateWith;
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	ExpOnly(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~ExpOnly();

};

/**
 * Represents the rule `EXP2 ::= (EXP)`, i.e. the nested expression.
 */
class Exp2Nested : public Exp2 {
private:
	Exp* nestedExpression;
public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	Exp2Nested(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~Exp2Nested();
	friend class ParseTree;

};

/**
 * Represents the rule `EXP2 ::= identifier INDEX`, i.e. the variable value readout.
 */
class Exp2Variable : public Exp2 {
private:
	Token* identifier;
	Index* index;
public:
	static Token* defaultIdentifier;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	Exp2Variable(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~Exp2Variable();
	friend class ParseTree;

};

/**
 * Represents the rule `EXP2 ::= integer`, i.e. the constant expression.
 */
class Exp2Constant : public Exp2 {
private:
	Token* integer;

public:
	static Token* defaultInteger;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	Exp2Constant(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~Exp2Constant();
	friend class ParseTree;

};

/**
 * Represents the rule `EXP2 ::= -EXP2`, i.e. the numeric expression value negation.
 */
class Exp2NumericNegation : public Exp2 {
private:
	Exp2* toNegate;

public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	Exp2NumericNegation(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~Exp2NumericNegation();
	friend class ParseTree;

};

/**
 * Represents the rule `EXP2 ::= !EXP2`, i.e. the logical (a.k.a. boolean value scope) expression value negation.
 */
class Exp2LogicalNegation : public Exp2 {
private:
	Exp2* toNegate;

public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	Exp2LogicalNegation(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~Exp2LogicalNegation();
	friend class ParseTree;

};

/**
 * Represents the rule `INDEX ::= [EXP]`, i.e. the existant array index.
 */
class IndexPosition : public Index {
private:
	Exp* index;

public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	IndexPosition(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~IndexPosition();
	friend class ParseTree;

};

/**
 * Represents the rule `INDEX ::= ε`, i.e. the nonexistant array index.
 */
class IndexEps : public Index {
private:
    static Token* followingToken;
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	IndexEps(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~IndexEps();
    friend class ParseTree;

};

/**
 * Represents the rule `OP_EXP ::= OP EXP`, i.e. the existant combined expression.
 */
class OpExpNext : public OpExp {
	Op* Operator;
	Exp* operand;
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	OpExpNext(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	bool isOperatorGreater();
	bool isOperatorNotEquals();
	~OpExpNext();

};

/**
 * Represents the rule `OP_EXP ::= ε`, i.e. the nonexistant combined expression.
 */
class OpExpEps : public OpExp {
private:
    static Token* followingToken;
public:
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	OpExpEps(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	bool isEps();
	~OpExpEps();
    friend class ParseTree;

};

/**
 * Represents the rule `OP ::= +`, i.e. the addition operator.
 */
class OpPlus : public Op {
private:

public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	OpPlus(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpPlus();
	friend class ParseTree;

};

/**
 * Represents the rule `OP ::= -`, i.e. the substraction operator.
 */
class OpMinus : public Op {
private:

public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	OpMinus(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpMinus();
	friend class ParseTree;

};

/**
 * Represents the rule `OP ::= *`, i.e. the multiplication operator.
 */
class OpMult : public Op {
private:

public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	OpMult(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpMult();
	friend class ParseTree;

};

/**
 * Represents the rule `OP ::= /`, i.e. the division operator.
 */
class OpDiv : public Op {
private:

public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	OpDiv(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpDiv();
	friend class ParseTree;

};

/**
 * Represents the rule `OP ::= <`, i.e. the less comparision operator.
 */
class OpLess : public Op {
private:

public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	OpLess(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpLess();
	friend class ParseTree;

};

/**
 * Represents the rule `OP :== >`, i.e. the greater comparision operator.
 */
class OpGreater : public Op {
private:

public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	OpGreater(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpGreater();
	friend class ParseTree;

};

/**
 * Represents the rule `OP ::= =`, i.e. the equality comparision opeator.
 */
class OpEquals : public Op {

public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	OpEquals(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpEquals();
	friend class ParseTree;

};

/**
 * Represents the rule `OP ::= =:=`, i.e. the inequality comparision operator.
 */
class OpNotEquals : public Op {

public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	OpNotEquals(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpNotEquals();
	friend class ParseTree;

};

/**
 * Represents the rule `OP ::= &&`, i.e. the conjunction operator.
 */
class OpAnd : public Op {

public:
	static Token* firstToken;
	/**
	 * Initializes static members of itself and related classes.
	 */
	static void initStatic();
	OpAnd(Scanner* scanner);
	static TokenTypeRegistry* first();
	bool typeCheck();
	void makeCode();
	~OpAnd();
	friend class ParseTree;

};

#endif /* PARSER_INCLUDES_PARSETREE_H_ */
