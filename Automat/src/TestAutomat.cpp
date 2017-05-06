#define CATCH_CONFIG_MAIN
#include "../includes/Automat.h"
#include <iostream>
#include "../../catch.hpp"
#include <string.h>
#define WSP_Z 12
#define CLSC_Z 16

/**
 * Returns next lexem found in @inputString
 * 
 * @automat
 * @inputString
 */
const char* getNextLexem(Automat* automat, char* inputString) {
	int i = 0;
	char nextChar = inputString[i];
	while (nextChar != '\0') {
		int back_steps = automat->read(nextChar);
		// adjust out pointer position & read the next symbol from input
		i = i + 1 - back_steps;
		nextChar = inputString[i];
		// reset automat iff a new lexem was found during processing
		if (automat->isLexemReady()) {
			//std::cout << "Lexem '" << automat->getLexem() << "' is ready. State: " << automat->getFinalState() << "   Length = " << automat->getLexemLength() << "   LINE: " << automat->getLine()  << "   COL: " << automat->getColumn() << std::endl;
			return automat->getLexem();
			automat->reset();
		}
	}
}

//							NOTICE
// following primitive methods are not tested since they 
// merely retrieve values from the existing tables/arrays:
// 
// Syntax::getTokenTypeAsChar(int num);
// Syntax::getState(int i, int j)


TEST_CASE( "AUTOMAT.CPP TEST: Lexems are processed", "[char]") {
	// TEST CASE SETUP
	Automat* automat = new Automat();
	
	// #1
	char* inputString = "&&&other+=:+probably+:=+:=:qeek+k#oo+=:=:+*\0";
	REQUIRE( !strcmp(getNextLexem(automat, inputString), "&&") );
}


TEST_CASE( "SYNTAX.CPP TEST -> matches()", "[char]") {
	// TEST CASE SETUP
	Syntax* syntax = new Syntax();
	
	// #1
	REQUIRE( syntax->matches("\0", "\0") );
	
	// #2
	REQUIRE( syntax->matches("a\0", "A\0") == false);
	
	// #3
	REQUIRE( syntax->matches("ag\0", "ag\0") );
	
	// #4
	REQUIRE( syntax->matches("ag", "ag") );
	
	// #5
	REQUIRE( syntax->matches("!@$#%@$^^#&^&*(^((){}\0", "!@$#%@$^^#&^&*(^((){}\0") );
	
	// #6
	REQUIRE( syntax->matches("if", "iF") == false);
}

TEST_CASE( "SYNTAX.CPP TEST -> ifKeyword()", "[char]") {
	// TEST CASE SETUP
	Syntax* syntax = new Syntax();
	
	// #1
	REQUIRE( syntax->ifKeyword("if") );

	// #2
	REQUIRE( syntax->ifKeyword("iF") == -1);
	
	// #3
	REQUIRE( syntax->ifKeyword("IF"));
	
	// #4
	REQUIRE( syntax->ifKeyword("while"));
	
	// #5
	REQUIRE( syntax->ifKeyword("WHILE"));
	
	// #6
	REQUIRE( syntax->ifKeyword("WHILe") == -1);
}

TEST_CASE( "SYNTAX.CPP TEST -> isPacked()", "[char]") {
	// TEST CASE SETUP
	Syntax* syntax = new Syntax();
	const char *signArray = new const char[14]
		{'+', '-', '!', ';', '<', '>', '(', ')','{', '}', '[', ']'};
	
	// #1 - #13
	REQUIRE( syntax->isPacked( signArray[0]) );
	REQUIRE( syntax->isPacked( signArray[1]) );
	REQUIRE( syntax->isPacked( signArray[2]) );
	REQUIRE( syntax->isPacked( signArray[3]) );
	REQUIRE( syntax->isPacked( signArray[4]) );
	REQUIRE( syntax->isPacked( signArray[5]) );
	REQUIRE( syntax->isPacked( signArray[6]) );
	REQUIRE( syntax->isPacked( signArray[7]) );
	REQUIRE( syntax->isPacked( signArray[8]) );
	REQUIRE( syntax->isPacked( signArray[9]) );
	REQUIRE( syntax->isPacked( signArray[13]) );
	
	// #13 - #15
	REQUIRE( syntax->isPacked( '&') == -1 );
	REQUIRE( syntax->isPacked( ':') == -1 );
	REQUIRE( syntax->isPacked( '=') == -1 );
}


TEST_CASE( "STACK.CPP TEST -> push(); trim(); get(); flush()", "[char]") {
	// TEST CASE SETUP
	Stack* stack = new Stack();

	// #1
	stack->push('a');
	stack->push('b');
	stack->push('c');
	REQUIRE( !strcmp(stack->get(), "abc") );
	
	// #2
	stack->trim(0);
	REQUIRE( !strcmp(stack->get(), "abc") );
	
	// #3
	stack->trim(2);
	REQUIRE( !strcmp(stack->get(), "a") );
	
	// #4
	stack->trim(1);
	REQUIRE( !strcmp(stack->get(), "") );
	
	// #5
	stack->flush();
	REQUIRE( !strcmp(stack->get(), "") );
	
	// #6
	stack->push('§');
	//REQUIRE( !strcmp(stack->get(), "§") );
	
	// #7
	stack->trim(1);
	REQUIRE( !strcmp(stack->get(), "") );
}

TEST_CASE( "AUTOMAT.CPP TEST -> read(char currentChar); reset()", "[char]") {
	// TEST CASE SETUP
	Automat* automat = new Automat();
	
	// #1
	automat->reset();
	automat->read('=');
	automat->read(':');
	int result1 = automat->read('x');
	REQUIRE( result1 == 2 );
	
	// #2
	automat->reset();
	automat->read(':');
	automat->read('=');
	int result2 = automat->read('x');
	REQUIRE( result2 == 1 );
	
	// #3
	automat->reset();
	automat->read('=');
	automat->read(':');
	automat->read('=');
	int result3 = automat->read('x');
	REQUIRE( result3 == 1 );
	
	// #4
	automat->reset();
	int result4 = automat->read('x');
	REQUIRE( result4 == 0 );
}

TEST_CASE( "AUTOMAT.CPP TEST -> updatePos(char c); :getLine(); getColumn()", "[char]") {
	// TEST CASE SETUP
	Automat* automat = new Automat();
	
	// #1
	automat->reset();
	automat->read('\n');
	automat->read('\n');
	automat->read('\n');
	automat->read('a');
	automat->read('!');
	int line1 = automat->getLine();
	int col1 = automat->getColumn();
	REQUIRE( line1 == 3 );
	REQUIRE( col1 == 2 );

}