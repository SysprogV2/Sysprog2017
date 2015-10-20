#include "../includes/Buffer.h"
#include "../../Automat/includes/Automat.h"
#include <iostream>


int main(int argc, char **argv) {
	char p = 'a';
	Buffer* buffer = new Buffer();
	Automat* automat = new Automat();

	int combobreaker = 50;

	while ( p != '\0' && combobreaker-- > 0) {
		p = buffer->getChar();
		int back_steps = automat->read(p);
		buffer->ungetChar(back_steps);
		//std::cout << p;
	}
	return 0;
}
