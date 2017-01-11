#include "../includes/Automat.h"
#include <iostream>

#define WSP_Z 12
#define CLSC_Z 16
int main (int argc, char* argv[]){
	Automat* automat = new Automat();
	char* input = (char *) "foo:=12<:10000\0";

	int i = 0;
	char c = input[i];
	while (c != '\0') {
		int back_steps = automat->read(c);
		std::cout << "C: " << c << "  ST: " << automat->getFinalState() << "   LINE: " << automat->getLine()  << "   COL: " << automat->getColumn() << "   BACK: " << automat->back << std::endl;
		// adjust out pointer position & read the next symbol from input
		i = i + 1 - back_steps;
		c = input[i];
		// reset automat iff a new lexem was found during processing
		if (automat->isLexemReady()) {
			std::cout << "Lexem '" << automat->getLexem() << "' is ready. Length = " << automat->getLexemLength() << "   LINE: " << automat->getLine()  << "   COL: " << automat->getColumn() << std::endl;
			automat->reset();
		}


	}



	std::cout << "===========================" << std::endl;

}
