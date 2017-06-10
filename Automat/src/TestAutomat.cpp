#include "../includes/Automat.h"
#include "../../Parser/includes/ParseTree.h"
#include "gtest/gtest.h"

/**
 * Returns next lexem found in @inputString
 *
 * @automat
 * @inputString
 */
const char *getNextLexem(Automat *automat, const char *inputString) {
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
        }
    }
}

// NOTICE
// following primitive methods are not tested since they
// merely retrieve values from the existing tables/arrays:
//
// Syntax::getTokenTypeAsChar(int num);
// Syntax::getState(int i, int j)

TEST(automat, read_isLexemReady_getLexem) {
    // TEST CASE SETUP
    Automat *automat = new Automat();

    // #1
    const char *inputString = "&&&other+=:+probably+:=+:=:qeek+k#oo+=:=:+*\0";
    EXPECT_TRUE(!strcmp(getNextLexem(automat, inputString), "&&"));
}

TEST(automat, matches) {
    Syntax *syntax = new Syntax();

    // When two strings are equal, they should match
    EXPECT_TRUE(syntax->matches("\0", "\0"));

    EXPECT_TRUE(syntax->matches("ag\0", "ag\0"));
    EXPECT_TRUE(syntax->matches("ag", "ag"));
    EXPECT_TRUE(syntax->matches("!@$#%@$^^#&^&*(^((){}\0", "!@$#%@$^^#&^&*(^((){}\0"));

    EXPECT_FALSE(syntax->matches("a\0", "A\0"));
    EXPECT_FALSE(syntax->matches("if", "iF"));
}

TEST(syntax, ifKeyword) {
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

TEST(syntax, isPacked) {
    // TEST CASE SETUP
    Syntax *syntax = new Syntax();
    const char *signArray = new const char[14]
            {'+', '-', '!', ';', '<', '>', '(', ')', '{', '}', '[', ']'};

    // #1 - #13
    EXPECT_TRUE(syntax->isPacked(signArray[0]));
    EXPECT_TRUE(syntax->isPacked(signArray[1]));
    EXPECT_TRUE(syntax->isPacked(signArray[2]));
    EXPECT_TRUE(syntax->isPacked(signArray[3]));
    EXPECT_TRUE(syntax->isPacked(signArray[4]));
    EXPECT_TRUE(syntax->isPacked(signArray[5]));
    EXPECT_TRUE(syntax->isPacked(signArray[6]));
    EXPECT_TRUE(syntax->isPacked(signArray[7]));
    EXPECT_TRUE(syntax->isPacked(signArray[8]));
    EXPECT_TRUE(syntax->isPacked(signArray[9]));
    EXPECT_TRUE(syntax->isPacked(signArray[13]));

    // Unknown symbols should not be recognized
    EXPECT_TRUE(syntax->isPacked('&') == -1);
    EXPECT_TRUE(syntax->isPacked(':') == -1);
    EXPECT_TRUE(syntax->isPacked('=') == -1);

}


TEST(stack, push_trim_get_flush) {
    // TEST CASE SETUP
    Stack *stack = new Stack();

    // #1
    stack->push('a');
    stack->push('b');
    stack->push('c');

    // #2
    stack->trim(0);
    EXPECT_TRUE(!strcmp(stack->get(), "abc"));

    // #3
    stack->trim(2);
    EXPECT_TRUE(!strcmp(stack->get(), "a"));

    // #4
    stack->trim(1);
    EXPECT_TRUE(!strcmp(stack->get(), ""));

    // #5
    stack->flush();
    EXPECT_TRUE(!strcmp(stack->get(), ""));

    // #6
    // stack->push('§');
    //REQUIRE( !strcmp(stack->get(), "§") );

    // #7
    stack->trim(1);
    EXPECT_TRUE(!strcmp(stack->get(), ""));

}


TEST(automat, read_reset) {
    // TEST CASE SETUP
    Automat *automat = new Automat();

    // #1
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
    // TEST CASE SETUP
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