#define CATCH_CONFIG_MAIN

#include "../includes/Automat.h"
#include "../../CatchLib/includes/catch.hpp"


// NOTICE
// following primitive methods are not tested since they
// merely retrieve values from the existing tables/arrays:
//
// Syntax::getTokenTypeAsChar(int num);
// Syntax::getState(int i, int j)

TEST_CASE("SYNTAX.CPP TEST -> matches()", "[char]") {
    Syntax *syntax = new Syntax();

    SECTION("When two strings are equal, they should match") {
        REQUIRE(syntax->matches("\0", "\0"));
        REQUIRE(syntax->matches("ag\0", "ag\0"));
        REQUIRE(syntax->matches("ag", "ag"));
        REQUIRE(syntax->matches("!@$#%@$^^#&^&*(^((){}\0", "!@$#%@$^^#&^&*(^((){}\0"));
    }
    SECTION("When two strings are not equal, they should not match") {
        REQUIRE(!syntax->matches("a\0", "A\0"));
        REQUIRE(!syntax->matches("if", "iF"));
    }
}

TEST_CASE("SYNTAX.CPP TEST -> ifKeyword()", "[char]") {
    Syntax *syntax = new Syntax();

    SECTION("lower case keywords should be recognized") {
        REQUIRE(syntax->ifKeyword("if"));
        REQUIRE(syntax->ifKeyword("while"));
    }
    SECTION("upper case keywords should be recognized") {
        REQUIRE(syntax->ifKeyword("IF"));
        REQUIRE(syntax->ifKeyword("WHILE"));
    }
    SECTION("mixed case keywords should NOT be recognized") {
        REQUIRE(syntax->ifKeyword("iF") == -1);
        REQUIRE(syntax->ifKeyword("WHILe") == -1);
    }
}

TEST_CASE("SYNTAX.CPP TEST -> isPacked()", "[char]") {
    Syntax *syntax = new Syntax();

    SECTION("Known symbols should be recognized") {
        REQUIRE(syntax->isPacked('+'));
        REQUIRE(syntax->isPacked('-'));
        REQUIRE(syntax->isPacked('!'));
        REQUIRE(syntax->isPacked(';'));
        REQUIRE(syntax->isPacked('<'));
        REQUIRE(syntax->isPacked('>'));
        REQUIRE(syntax->isPacked('('));
        REQUIRE(syntax->isPacked(')'));
        REQUIRE(syntax->isPacked('{'));
        REQUIRE(syntax->isPacked('}'));
        REQUIRE(syntax->isPacked('['));
        REQUIRE(syntax->isPacked(']'));
    }
    SECTION("Unknown symbols should not be recognized") {
        REQUIRE(syntax->isPacked('&') == -1);
        REQUIRE(syntax->isPacked(':') == -1);
        REQUIRE(syntax->isPacked('=') == -1);
    }
}


TEST_CASE("STACK.CPP TEST -> push(); trim(); get(); flush()", "[char]") {
    Stack *stack = new Stack();

    SECTION("empty") {
        REQUIRE(!strcmp(stack->get(), ""));

        stack->push('a');
        stack->push('b');
        stack->push('c');

        SECTION("abc") {
            REQUIRE(!strcmp(stack->get(), "abc"));

            stack->trim(0);
            REQUIRE(!strcmp(stack->get(), "abc"));
            stack->trim(2);
            REQUIRE(!strcmp(stack->get(), "a"));
            stack->trim(1);
            REQUIRE(!strcmp(stack->get(), ""));
        }

        SECTION("abc") {
            REQUIRE(!strcmp(stack->get(), "abc"));

            stack->flush();
            REQUIRE(!strcmp(stack->get(), ""));

        }
    }
}

TEST_CASE("AUTOMAT.CPP TEST -> read(char currentChar); reset()", "[char]") {
    Automat *automat = new Automat();

    SECTION("")
    automat->reset();
    automat->read('=');
    automat->read(':');
    int result1 = automat->read('x');
    REQUIRE(result1 == 2);

    // #2
    automat->reset();
    automat->read(':');
    automat->read('=');
    int result2 = automat->read('x');
    REQUIRE(result2 == 1);

    // #3
    automat->reset();
    automat->read('=');
    automat->read(':');
    automat->read('=');
    int result3 = automat->read('x');
    REQUIRE(result3 == 1);

    // #4
    automat->reset();
    int result4 = automat->read('x');
    REQUIRE(result4 == 0);
}

TEST_CASE("AUTOMAT.CPP TEST -> updatePos(char c); :getLine(); getColumn()", "[char]") {
    Automat *automat = new Automat();

    // #1
    automat->reset();
    automat->read('\n');
    automat->read('\n');
    automat->read('\n');
    automat->read('a');
    automat->read('!');
    int line1 = automat->getLine();
    int col1 = automat->getColumn();
    REQUIRE(line1 == 3);
    REQUIRE(col1 == 2);
}