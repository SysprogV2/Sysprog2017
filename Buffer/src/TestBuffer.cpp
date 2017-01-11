#include "../includes/Buffer.h"
#include "../../Automat/includes/Automat.h"
#include <iostream>

int main(int argc, char **argv) {
	char* filename;
	if (argc > 0) {
		filename = argv[1];
	} else {
		std::cout << "Failed to read file. No filename is given!" << std::endl;
		return 1;
	}
	Buffer* buffer = new Buffer(filename);

	// print out all chars from a given file
	char p = buffer->getChar();
	while ( p != '\0' ) {
		std::cout << p;
		p = buffer->getChar();
	}
	return 0;
}
