#include "../includes/Scanner.h"
#include <iostream>
int main(int argc, char **argv) {

	Scanner* scanner = new Scanner();
	std::cout << "token: "<< scanner->nextToken() << std::endl;
	std::cout << "token: "<< scanner->nextToken() << std::endl;
	std::cout << "token: "<< scanner->nextToken() << std::endl;
	std::cout << "token: "<< scanner->nextToken() << std::endl;


}

