#include "../includes/Scanner.h"
#include <sys/time.h>


/* copypasted piece of code for time measurements */
typedef unsigned long long timestamp_t;
static timestamp_t
get_timestamp ()
{
    struct timeval now;
    gettimeofday (&now, nullptr);
    return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}


int main(int argc, char **argv) {
    timestamp_t t0 = get_timestamp();
    Symboltable* st = new Symboltable();
    Scanner* s = new Scanner(argv[1], st);
    Token* t;
    Syntax* syntax = new Syntax();
    std::cout << "processing..." << std::endl;

    /* check if all arguments are given */
    if (argc == 3) {
        std::ofstream output_file;
        output_file.open(argv[2]);
        if (output_file.is_open()) {
            while ((t = s->nextToken()) && t->getType() != Syntax::States::EOF_Z) {
                /* console output */
                if (t->getType() == Syntax::PROH_Z) {
                    std::cout << t->getErrorMessage()
                              << " Line: " << t->getLine()
                              << " Column: " << t->getColumn();
                    if (t->getSymbol() != nullptr) {
                        std::cout << " Symbol: " << t->getSymbol();
                    }
                    std::cout << std::endl;
                    /* print everything else to the output file */
                } else if (t->getType() != Syntax::WSP_Z) {
                    output_file
                            << syntax->getTokenTypeAsChar(t->getType())
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
            std::cout << "stop" << std::endl
                      << "Exec time: " << ((get_timestamp() - t0) / 1000000.0L) << std::endl;
            output_file.close();
        } else {
            std::cout << "Error: couldn't open output file. Exiting..." << std::endl;
        }
    } else {
        std::cout << "Error: path to input and/or output file is not given. Exiting..." << std::endl;
    }
    return EXIT_SUCCESS;
}

