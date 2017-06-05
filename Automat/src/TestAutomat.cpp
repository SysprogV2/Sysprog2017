#include "../includes/Automat.h"
#include "../../Parser/includes/ParseTree.h"
#include "gtest/gtest.h"

// NOTICE
// following primitive methods are not tested since they
// merely retrieve values from the existing tables/arrays:
//
// Syntax::getTokenTypeAsChar(int num);
// Syntax::getState(int i, int j)

TEST(automat, matches) {
    Syntax *syntax = new Syntax();

    // When two strings are equal, they should match
    EXPECT_TRUE(syntax->matches("\0", "\0"));
    EXPECT_TRUE(syntax->matches("ag\0", "ag\0"));
    EXPECT_TRUE(syntax->matches("ag", "ag"));
    EXPECT_TRUE(syntax->matches("!@$#%@$^^#&^&*(^((){}\0", "!@$#%@$^^#&^&*(^((){}\0"));

    // When two strings are not equal, they should not match
    EXPECT_FALSE(syntax->matches("a\0", "A\0"));
    EXPECT_FALSE(syntax->matches("if", "iF"));
}

TEST(automat, ifKeyword) {
    Syntax *syntax = new Syntax();

    // lower case keywords should be recognized
    EXPECT_TRUE(syntax->ifKeyword("if"));
    EXPECT_TRUE(syntax->ifKeyword("while"));

    // upper case keywords should be recognized
    EXPECT_TRUE(syntax->ifKeyword("IF"));
    EXPECT_TRUE(syntax->ifKeyword("WHILE"));

    // mixed case keywords should NOT be recognized
    EXPECT_TRUE(syntax->ifKeyword("iF") == -1);
    EXPECT_TRUE(syntax->ifKeyword("WHILe") == -1);

}

TEST(automat, isPacked) {
    Syntax *syntax = new Syntax();

    // Known symbols should be recognized
    EXPECT_TRUE(syntax->isPacked('+'));
    EXPECT_TRUE(syntax->isPacked('-'));
    EXPECT_TRUE(syntax->isPacked('!'));
    EXPECT_TRUE(syntax->isPacked(';'));
    EXPECT_TRUE(syntax->isPacked('<'));
    EXPECT_TRUE(syntax->isPacked('>'));
    EXPECT_TRUE(syntax->isPacked('('));
    EXPECT_TRUE(syntax->isPacked(')'));
    EXPECT_TRUE(syntax->isPacked('{'));
    EXPECT_TRUE(syntax->isPacked('}'));
    EXPECT_TRUE(syntax->isPacked('['));
    EXPECT_TRUE(syntax->isPacked(']'));

    // Unknown symbols should not be recognized
    EXPECT_TRUE(syntax->isPacked('&') == -1);
    EXPECT_TRUE(syntax->isPacked(':') == -1);
    EXPECT_TRUE(syntax->isPacked('=') == -1);

}


TEST(automat, push_trim_get_flush) {
    Stack *stack = new Stack();

    // empty
    EXPECT_FALSE(strcmp(stack->get(), ""));

    stack->push('a');
    stack->push('b');
    stack->push('c');

    // abc
    EXPECT_FALSE(strcmp(stack->get(), "abc"));

    stack->trim(0);
    EXPECT_FALSE(strcmp(stack->get(), "abc"));
    stack->trim(2);
    EXPECT_FALSE(strcmp(stack->get(), "a"));
    stack->trim(1);
    EXPECT_FALSE(strcmp(stack->get(), ""));


    // abc
    EXPECT_FALSE(strcmp(stack->get(), "abc"));

    stack->flush();
    EXPECT_FALSE(strcmp(stack->get(), ""));

}


TEST(automat, read_reset) {
    Automat *automat = new Automat();

    automat->reset();

    automat->read('=');
    automat->read(':');
    int result1 = automat->read('x');
    EXPECT_EQ(result1, 2);

    // #2
    automat->reset();

    automat->read(':');
    automat->read('=');
    int result2 = automat->read('x');
    EXPECT_EQ(result2, 1);

    // #3
    automat->reset();

    automat->read('=');
    automat->read(':');
    automat->read('=');
    int result3 = automat->read('x');
    EXPECT_EQ(result3, 1);

    // #4
    automat->reset();

    int result4 = automat->read('x');
    EXPECT_EQ(result4, 0);
}

TEST(automat, updatePos_getLine_getColumn) {
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
    EXPECT_EQ(line1, 3);
    EXPECT_EQ(col1, 2);
}