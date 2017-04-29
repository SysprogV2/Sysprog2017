#define CATCH_CONFIG_MAIN
#include "../includes/Automat.h"
#include <iostream>
#include "../../catch.hpp"
#define WSP_Z 12
#define CLSC_Z 16

/**
 * Returns next lexem found in @inputString
 * 
 * @automat
 * @inputString
 */
char* getNextLexem(Automat* automat, char* inputString) {
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

// NOTICE: seems like Catch can not match a char* with a string,
// so we have to make a convertion char*->std::str manually

TEST_CASE( "AUTOMAT TEST CASE: Lexems are processed", "[char]") {
	// TEST CASE SETUP
	Automat* automat = new Automat();
	char* inputString = "&&&other+=:+probably+:=+:=:qeek+k#oo+=:=:+*\0";
	std::string someString(getNextLexem(automat, inputString));
	REQUIRE( someString == "&&");
	//REQUIRE( getNextLexem(automat, inputString) == "&");
}

TEST_CASE( "STACK TEST CASE: Lexems are processed", "[char]") {
	// TEST CASE SETUP
	Stack* stack = new Stack();
	//virtual ~Stack();
	//void push(char c);
    //void trim(int back);
    //void flush();
    //char* get();
	
	// test chars got pushed into right order 1
	stack->push('a');
	stack->push('b');
	std::string expected1("ab");
	std::string result1(stack->get());
	REQUIRE( expected1 == result1) ;
	
	// test chars got removed from stack after flush()
	stack->flush();
	std::string expected2("");
	std::string result2(stack->get());
	REQUIRE( expected2 == result2) ;
	
	// test we can fill the stack up again
	stack->push('a');
	stack->push('b');
	std::string expected3("ab");
	std::string result3(stack->get());
	REQUIRE( expected3 == result3) ;

}