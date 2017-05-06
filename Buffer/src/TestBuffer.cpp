#include "../includes/Buffer.h"
#include "../../Automat/includes/Automat.h"
#include <iostream>
#include <string>




bool TEST_getChar(char* filename) {
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

bool TEST_ungetChar(char* filename) {
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

int main(int argc, char *argv[]) {

	char* filename;
		if (argc > 0) {
			filename = argv[1];
		} else {
			std::cout << "Failed to read file. No filename is given!" << std::endl;
			return 1;
		}


    //printf("Test %d %s\n", 0, TEST_getChar(filename) ? "success" : "FAIL");
		printf("Test %d %s\n", 0, TEST_ungetChar(filename) ? "success" : "FAIL");
    //   printf("Test %d %s\n", 1, TEST_ungetChar() ? "success" : "FAIL");
    //   printf("Test %d %s\n", 2, TEST_getungetChar() ? "success" : "FAIL");


    printf("All tests run.\n");
    return 0;
}
