#include "../includes/Buffer.h"
#include "gtest/gtest.h"

bool TEST_getChar(const char *filename);

bool TEST_ungetChar(const char *filename);

#define FILE0 (string(PROJECT_SOURCE_DIR) + string("/test/scanner0.txt"))
#define FILE1 (string(PROJECT_SOURCE_DIR) + string("/test/scanner1.txt"))
#define FILE2 (string(PROJECT_SOURCE_DIR) + string("/test/scanner2.txt"))
#define FILE3 (string(PROJECT_SOURCE_DIR) + string("/test/scanner3.txt"))
#define FILE4 (string(PROJECT_SOURCE_DIR) + string("/test/scanner4.txt"))
#define FILE5 (string(PROJECT_SOURCE_DIR) + string("/test/scanner5.txt"))
#define FILE6 (string(PROJECT_SOURCE_DIR) + string("/test/scanner6.txt"))
#define FILE7 (string(PROJECT_SOURCE_DIR) + string("/test/scanner7.txt"))
#define FILE8 (string(PROJECT_SOURCE_DIR) + string("/test/scanner8.txt"))
#define FILE9 (string(PROJECT_SOURCE_DIR) + string("/test/scanner9.txt"))


TEST(buffer, constructor) {
	// on stack") {
	Buffer buffer = Buffer(FILE0.c_str());
	EXPECT_TRUE(buffer.getFileLength() > 0);
	EXPECT_FALSE(buffer.isEnd());

	// on heap") {
	Buffer *buffer2 = new Buffer(FILE0.c_str());
	EXPECT_TRUE(buffer2->getFileLength() > 0);
	EXPECT_FALSE(buffer2->isEnd());

}

TEST(buffer, getChar) {
	EXPECT_TRUE(TEST_getChar(FILE0.c_str()));
	EXPECT_TRUE(TEST_getChar(FILE1.c_str()));
	EXPECT_TRUE(TEST_getChar(FILE2.c_str()));
	EXPECT_TRUE(TEST_getChar(FILE3.c_str()));
	EXPECT_TRUE(TEST_getChar(FILE4.c_str()));
	EXPECT_TRUE(TEST_getChar(FILE5.c_str()));
	EXPECT_TRUE(TEST_getChar(FILE6.c_str()));
	EXPECT_TRUE(TEST_getChar(FILE7.c_str()));
	EXPECT_TRUE(TEST_getChar(FILE8.c_str()));
	EXPECT_TRUE(TEST_getChar(FILE9.c_str()));
}

TEST(buffer, ungetChar) {
	EXPECT_TRUE(TEST_ungetChar(FILE0.c_str()));
	EXPECT_TRUE(TEST_ungetChar(FILE1.c_str()));
	EXPECT_TRUE(TEST_ungetChar(FILE2.c_str()));
	EXPECT_TRUE(TEST_ungetChar(FILE3.c_str()));
	EXPECT_TRUE(TEST_ungetChar(FILE4.c_str()));
	EXPECT_TRUE(TEST_ungetChar(FILE5.c_str()));
	EXPECT_TRUE(TEST_ungetChar(FILE6.c_str()));
	EXPECT_TRUE(TEST_ungetChar(FILE7.c_str()));
	EXPECT_TRUE(TEST_ungetChar(FILE8.c_str()));
	EXPECT_TRUE(TEST_ungetChar(FILE9.c_str()));
}


bool TEST_getChar(const char *filename) {
	// Initialize Buffer 1
	Buffer bufferIntern = Buffer(filename);

	// Initialize Buffer 2
	ifstream *bufferExtern = new ifstream();
	bufferExtern->open(filename);

	int length = bufferIntern.getFileLength();
	int lengthExtern = Buffer::getFileLength(bufferExtern);

	if (length != lengthExtern) {
		printf("Unexpected Error: Buffers have unequal lengths");
		return false;
	}

	// Create 2 buffers and empty them
	auto bufferOutputIntern = new char[length];
	auto bufferOutputExtern = new char[length];
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
		// printf("%d: %c vs %c\n", i, bufferOutputIntern[i], bufferOutputExtern[i]);
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

	auto bufferOutput = new char[length];
	for (int i = 0; i < length; i++) {
		bufferOutput[i] = '\0';
	}

	// Load Buffer
	for (int count = 0; !buffer.isEnd()/*count < length*/; count++) {
		bufferOutput[count] = buffer.getChar();
		buffer.ungetChar(0);
	}

	// Compare both buffers
	for (int i = length - 1; i >= 0; i--) {
		char newUngetChar = buffer.ungetChar(1);
		buffer.ungetChar(0);
		// printf("%d: %c vs %c\n", i, bufferOutput[i], newUngetChar);
		if (bufferOutput[i] != newUngetChar) {
			printf("ERROR!\n");
			return false;
		}
	}

	// Compare until half
	for (int i = 0; i < length / 2; i++) {
		buffer.ungetChar(0);
		char newGetChar = buffer.getChar();

		// printf("%d: %c vs %c\n", i, bufferOutput[i], newGetChar);
		if (bufferOutput[i] != newGetChar) {
			printf("ERROR!\n");
			return false;
		}
	}

	// Compare back
	for (int i = (length / 2) - 1; i >= 0; i--) {
		char newGetChar = buffer.ungetChar(1);
		buffer.ungetChar(0);
		// printf("%d: %c vs %c\n", i, bufferOutput[i], newGetChar);
		if (bufferOutput[i] != newGetChar) {
			printf("ERROR!\n");
			return false;
		}
	}
	return true;
}