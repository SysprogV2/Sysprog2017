#include "../includes/Buffer.h"
#include "../../Automat/includes/Automat.h"
#include <iostream>



bool TEST_getChar(char* filename) {
    // Create 2 buffers and empty them
    char *bufferOutputIntern = new char[10000];
    char *bufferOutputExtern = new char[10000];
    for (int i = 0; i < 10000; i++) {
        bufferOutputExtern[i] = '\0';
        bufferOutputIntern[i] = '\0';
    }

    // Load Buffer Intern
    Buffer bufferIntern = Buffer(filename);
    for (int count = 0; !bufferIntern.isEnd() && count < 10000; count++) {
        bufferOutputIntern[count] = bufferIntern.getChar();
    }

    // Load Buffer Extern
    ifstream* bufferExtern = new ifstream();
    bufferExtern->open(filename);
    bufferExtern->read(bufferOutputExtern, 10000);
    bufferExtern->close();

    // Compare both buffers
    for (int i = 0; i < 10000; i++) {
        if (bufferOutputIntern[i] != bufferOutputExtern[i]) {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[]) {

	char* filename;
		if (argc > 0) {
			filename = argv[1];
		} else {
			std::cout << "Failed to read file. No filename is given!" << std::endl;
			return 1;
		}


    printf("Test %d %s\n", 0, TEST_getChar(filename) ? "success" : "FAIL");
    //   printf("Test %d %s\n", 1, TEST_ungetChar() ? "success" : "FAIL");
    //   printf("Test %d %s\n", 2, TEST_getungetChar() ? "success" : "FAIL");


    printf("All tests run.\n");
    return 0;
}
