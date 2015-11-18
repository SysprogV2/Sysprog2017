#include "../includes/Scanner.h"
#include <iostream>
#include <sys/time.h>



/* copypasted piece of code for running time measuring */
typedef unsigned long long timestamp_t;
static timestamp_t
get_timestamp ()
{
   struct timeval now;
   gettimeofday (&now, NULL);
   return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}



int main(int argc, char **argv) {
	/*
	// get the first timestamp
    timestamp_t t0 = get_timestamp();

	Scanner* scanner = new Scanner(argv[1], false);
	while (!scanner->isEofReached()) {
		scanner->nextToken();
	}

	// get the second and output
    timestamp_t t1 = get_timestamp();
    double secs = (t1 - t0) / 1000000.0L;
    std::cout << "Exec time: " << secs << std::endl;
    */
}

