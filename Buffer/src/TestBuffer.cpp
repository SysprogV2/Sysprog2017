#include "../includes/Buffer.h"
#include "../../Automat/includes/Automat.h"
#include <iostream>


int main(int argc, char **argv) {
	Buffer* buffer = new Buffer();
	char p = 'x';
	while ( p != '\0' ) {
		p = buffer->getChar();
		std::cout << p;
	}
	return 0;
}
