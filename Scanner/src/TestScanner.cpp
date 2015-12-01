#include "../includes/Scanner.h"
#include <iostream>
#include <sys/time.h>



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
	//get the first timestamp
	timestamp_t t0 = get_timestamp();

	Symboltable* st = new Symboltable();
	Scanner* s = new Scanner(argv[1], st);
    Token* t;
   	while ((t = s->nextToken())) {
   		t->print();
   }

	// get the second and output
    std::cout << "Exec time  nnnn: " << ((get_timestamp() - t0) / 1000000.0L) << std::endl;
}

