#include "../includes/Scanner.h"
#include <iostream>
#include <sys/time.h>
#include <fstream>

/* copypasted piece of code for time measurements */
typedef unsigned long long timestamp_t;
static timestamp_t
get_timestamp ()
{
   struct timeval now;
   gettimeofday (&now, NULL);
   return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}


int main(int argc, char **argv) {
	timestamp_t t0 = get_timestamp();
	Symboltable* st = new Symboltable();
	Scanner* s = new Scanner(argv[1], st);

	/* collect all tokens in Symboltable */
	std::ofstream output_file;
	output_file.open(argv[2]);
	Token* t;
	Syntax* syntax = new Syntax();
	std::cout << "processing..." << std::endl;
   	while ((t = s->nextToken())) {
   		/* output to console */
   		if (t->getType() == Syntax::PROH_Z) {
   			std::cout << "unknown Token Line: " << t->getLine()
   					  << " Column: " << t->getColumn()
					  << " Symbol: " << t->getSymbol()
					  << std::endl;

   		/* print everything else to file */
   		} else {
   			//output_file << "Token " << Syntax:
   			output_file << "Token " << syntax->getTokenTypeAsChar(t->getType())
						<< " Line: " << t->getLine()
   		   			    << " Column: " << t->getColumn();
   			if (t->getType() == Syntax::IDEN_Z) {
   				output_file << " Lexem: " << t->getLexem();
   			} else if (t->getType() == Syntax::INTG_Z) {
   				output_file << " Value: " << t->getValue();
   			}
   			output_file << std::endl;
   		}
    }

   	/* and now output the Symboltable */
   	//st->print();
   	std::cout << "stop" << std::endl;
    std::cout << "Exec time: " << ((get_timestamp() - t0) / 1000000.0L) << std::endl;
    output_file.close();
}

