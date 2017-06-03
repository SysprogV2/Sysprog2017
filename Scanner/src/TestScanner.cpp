#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#include "../includes/Scanner.h"

#define CATCH_CONFIG_MAIN

#include "../../CatchLib/includes/catch.hpp"


TEST_CASE("scanner main", "[scanner]") {
    const char *INPUT_FILE = "../../test/scanner0.txt";
    const char *OUTPUT_FILE = "out.txt";

    Symboltable *st = new Symboltable();
    Scanner *s = new Scanner((char *) INPUT_FILE, st);
    Token *t;
    Syntax *syntax = new Syntax();
    std::cout << "processing..." << std::endl;


    std::ofstream output_file;
    output_file.open(OUTPUT_FILE);

    REQUIRE(output_file.is_open());

    // TODO: Test more!

    while ((t = s->nextToken())) {
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
    output_file.close();

}


#pragma clang diagnostic pop