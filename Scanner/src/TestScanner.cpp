#include "../includes/Scanner.h"
#include "gtest/gtest.h"

#define FILE0 string(PROJECT_SOURCE_DIR "/test/scanner1.txt")
#define OUT_FILE (string(PROJECT_SOURCE_DIR "/out.txt"))

TEST(scanner, main) {
    Symboltable *st = new Symboltable();
    Scanner *s = new Scanner((char *) FILE0.c_str(), st);
    Token *t;
    Syntax *syntax = new Syntax();

    std::cout << endl;
    std::cout << "Input file: " << FILE0.c_str() << endl;
    std::cout << "Output file: " << OUT_FILE.c_str() << endl;
    std::cout << "processing..." << std::endl;


    std::ofstream output_file;
    output_file.open(OUT_FILE.c_str());

    ASSERT_TRUE(output_file.is_open());
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