#include "../includes/Buffer.h"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"
#include <regex.h>
#define CATCH_CONFIG_MAIN
#include "../../CatchLib/includes/catch.hpp"


bool TEST_getChar(const char* filename);
bool TEST_ungetChar(const char* filename);

#define TEST_TAG "[buffer]"

#define FILE0 "../test/scanner0.txt"
#define FILE1 "../test/scanner1.txt"
#define FILE2 "../test/scanner2.txt"
#define FILE3 "../test/scanner3.txt"
#define FILE4 "../test/scanner4.txt"
#define FILE5 "../test/scanner5.txt"
#define FILE6 "../test/scanner6.txt"
#define FILE7 "../test/scanner7.txt"
#define FILE8 "../test/scanner8.txt"
#define FILE9 "../test/scanner9.txt"

TEST_CASE("getChar", TEST_TAG) {
    REQUIRE(TEST_getChar(FILE0));
    REQUIRE(TEST_getChar(FILE1));
    REQUIRE(TEST_getChar(FILE2));
    REQUIRE(TEST_getChar(FILE3));
    REQUIRE(TEST_getChar(FILE4));
    REQUIRE(TEST_getChar(FILE5));
    REQUIRE(TEST_getChar(FILE6));
    REQUIRE(TEST_getChar(FILE7));
    REQUIRE(TEST_getChar(FILE8));
    REQUIRE(TEST_getChar(FILE9));
}

TEST_CASE("ungetChar", TEST_TAG) {
    REQUIRE(TEST_ungetChar(FILE0));
    REQUIRE(TEST_ungetChar(FILE1));
    REQUIRE(TEST_ungetChar(FILE2));
    REQUIRE(TEST_ungetChar(FILE3));
    REQUIRE(TEST_ungetChar(FILE4));
    REQUIRE(TEST_ungetChar(FILE5));
    REQUIRE(TEST_ungetChar(FILE6));
    REQUIRE(TEST_ungetChar(FILE7));
    REQUIRE(TEST_ungetChar(FILE8));
    REQUIRE(TEST_ungetChar(FILE9));
}

TEST_CASE("constructor", TEST_TAG) {
    SECTION("on stack") {
        Buffer buffer = Buffer(FILE0);
        REQUIRE(buffer.getFileLength() > 0);
        REQUIRE_FALSE(buffer.isEnd());
    }
    SECTION("on heap") {
        Buffer* buffer = new Buffer(FILE0);
        REQUIRE(buffer->getFileLength() > 0);
        REQUIRE_FALSE(buffer->isEnd());
    }
}

bool TEST_getChar(const char *filename) {
    // Initialize Buffer 1
    Buffer bufferIntern = Buffer(filename);

    // Initialize Buffer 2
    ifstream* bufferExtern = new ifstream();
    bufferExtern->open(filename);

    int length = bufferIntern.getFileLength();
    int lengthExtern = Buffer::getFileLength(bufferExtern);

    if(length != lengthExtern) {
        printf("Unexpected Error: Buffers have unequal lengths");
        return false;
    }

    // Create 2 buffers and empty them
    char *bufferOutputIntern = new char[length];
    char *bufferOutputExtern = new char[length];
    for (int i = 0; i < length; i++) {
        bufferOutputExtern[i] = '\0';
        bufferOutputIntern[i] = '\0';
    }

    // Load Buffer Intern

    for (int count = 0; !bufferIntern.isEnd()/*count < length*/; count++) {
        bufferOutputIntern[count] = bufferIntern.getChar();
    }

    // Load Buffer Extern

    bufferExtern->read(bufferOutputExtern, length);
    bufferExtern->close();

    // Compare both buffers
    for (int i = 0; i < length; i++) {
        printf("%d: %c vs %c\n", i, bufferOutputIntern[i], bufferOutputExtern[i]);
        if (bufferOutputIntern[i] != bufferOutputExtern[i]) {
            printf("ERROR!\n");
            return false;
        }
    }
    return true;
}

bool TEST_ungetChar(const char *filename) {
    // Initialize Buffer
    Buffer buffer = Buffer(filename);

    int length = buffer.getFileLength();

    char *bufferOutput = new char[length];
    for (int i = 0; i < length; i++) {
        bufferOutput[i] = '\0';
    }

    // Load Buffer
    for (int count = 0; !buffer.isEnd()/*count < length*/; count++) {
        bufferOutput[count] = buffer.getChar();
        buffer.ungetChar(0);
    }

    // Compare both buffers
    for (int i = length-1; i >= 0; i--) {
        char newUngetChar = buffer.ungetChar(1);
        buffer.ungetChar(0);
        printf("%d: %c vs %c\n", i, bufferOutput[i], newUngetChar);
        if (bufferOutput[i] != newUngetChar) {
            printf("ERROR!\n");
            return false;
        }
    }

    // Compare until half
    for (int i = 0; i < length/2; i++) {
        buffer.ungetChar(0);
        char newGetChar = buffer.getChar();

        printf("%d: %c vs %c\n", i, bufferOutput[i], newGetChar);
        if (bufferOutput[i] != newGetChar) {
            printf("ERROR!\n");
            return false;
        }
    }

    // Compare back
    for (int i = (length/2)-1; i >= 0; i--) {
        char newGetChar = buffer.ungetChar(1);
        buffer.ungetChar(0);
        printf("%d: %c vs %c\n", i, bufferOutput[i], newGetChar);
        if (bufferOutput[i] != newGetChar) {
            printf("ERROR!\n");
            return false;
        }
    }
    return true;
}
#pragma clang diagnostic pop