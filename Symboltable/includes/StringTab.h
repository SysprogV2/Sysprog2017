/*
 * StringTab.h
 *
 *  Created on: Oct 28, 2015
 *      Author: arty
 */

#ifndef SYMBOLTABLE_STRINGTAB_H_
#define SYMBOLTABLE_STRINGTAB_H_

#define INITIAL_SIZE 16
#define INITIAL_ALGN 4096

#include <cstdio>  // perror()
#include <cstdlib> // throw()
#include <cerrno>  // errors' list
#include <cstring> // memcpy()
#include "../../Compab/includes/compab.hpp"

class StringTab {
	char *string;
	char *freeP;
	int overallSpace;
	int freeSpace;
public:
	StringTab();
	virtual ~StringTab();
	char* insert(const char *lexem, int size);
	void resize(int moreSpace);
	char* copy(char * freepointer, const char *lexem, int size);
	void resize(char * stringItself, int size);
	int getFS();
	int getOS();
};


#endif /* SYMBOLTABLE_STRINGTAB_H_ */
