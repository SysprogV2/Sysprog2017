#include "../includes/Symboltable.h"
#include <iostream>
int main(int argc, char **argv) {
	Symboltable* symboltable;
	symboltable = new Symboltable();

	char * c1 = "reallyreal";
	int c1len = 10;
	char * c2 = "a";
	int c2len = 1;
	char * c3 = "b";
	int c3len = 1;
	char * c4 = "c";
	int c4len = 1;
	char * c5 = "d";
	int c5len = 1;
	char * c6 = "mio moi mio";
	int c6len = 11;
	char * c7 = "RACINGTEAM";
	int c7len = 10;
	char * c8 = "trytohandleths";
	int c8len = 14;
	char * c9 = "not impressed at all";
	int c9len = 20;
	char * c10 = "reallyreallyreallyreallyreallyreallyreallyreallyreallyreallyString";
	int c10len = 67;

	char *s1 = symboltable->insert(c1, c1len);
	char *s2 = symboltable->insert(c2, c2len);
	char *s3 = symboltable->insert(c3, c3len);
	char *s4 = symboltable->insert(c4, c4len);
	char *s5 = symboltable->insert(c5, c5len);
	char *s6 = symboltable->insert(c6, c6len);
	char *s7 = symboltable->insert(c7, c7len);
	char *s8 = symboltable->insert(c8, c8len);
	char *s9 = symboltable->insert(c9, c9len);
	char *s10 = symboltable->insert(c10, c10len);

	c1 = ";";
	c2 = ";";
	c3 = "d";
	c9 = ";";
	c10 = ";";
	c8 = "d";

	std::cout << s1 << std::endl;
	std::cout << s2 << std::endl;
	std::cout << s3 << std::endl;
	std::cout << s4 << std::endl;
	std::cout << s5 << std::endl;
	std::cout << s6 << std::endl;
	std::cout << s7 << std::endl;
	std::cout << s8 << std::endl;
	std::cout << s9 << std::endl;
	std::cout << s10<< std::endl;
}
