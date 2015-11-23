/*
 * StringTab.cpp
 *
 *  Created on: Oct 28, 2015
 *      Author: arty
 */

#include "../includes/StringTab.h"

StringTab::StringTab() {
	void *gtfo;
	int error = posix_memalign(&gtfo, INITIAL_ALGN, INITIAL_SIZE * sizeof(char));
	if (error != 0) {
	    perror("posix_memalign");
	    exit(EXIT_FAILURE);
	}
	string = (char*) gtfo;
	freeP = string;
	overallSpace = INITIAL_SIZE;
	freeSpace = INITIAL_SIZE;
}


StringTab::~StringTab() {
	delete[] string;
}

/*
 *  add lexem to the end of the array &
 * return pointer to the lexem
 */
char* StringTab::insert(char *lexem, int size) {
	char *tmpToReturn;
	if (size >= freeSpace) {
		resize(string, size);
	}
	tmpToReturn = copy(freeP, lexem, size);
	// move pointer to the new place
	freeP += sizeof(char) * (size + 1);
	return tmpToReturn;
}

/*
 * copy lexem to the end of the string
 */
char * StringTab::copy(char * freepointer, char *lexem, int size) {
	memcpy(freepointer, lexem, size + 1);
	freeSpace -= size + 1;
	return freepointer;
}

/*
 * reallocate space
 */
void StringTab::resize(char * stringItself, int size) {
	/* determine the desired size  for new chararray*/
	int occupiedSpace = overallSpace - freeSpace + 1;
	while (size > freeSpace) {
		freeSpace += overallSpace;
		overallSpace *= 2;
	}

	/* copy the content of old string */
	void *gtfo;
	int error = posix_memalign(&gtfo, 4096, overallSpace * sizeof(char));
	if (error != 0) {
	    perror("posix_memalign");
	    exit(EXIT_FAILURE);
    }
	memcpy(gtfo, string, occupiedSpace * sizeof(char));

	/* update original pointers */
	string = (char*) gtfo;
	freeP = (char*) gtfo + occupiedSpace * sizeof(char);

}

/*
 * how much space is left
 */
int StringTab::getFS() {
	return freeSpace;
}

/*
 * how much space is ALREADY allocated
 */
int StringTab::getOS() {
	return overallSpace;
}
