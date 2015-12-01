/*
 * Position.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */


#include "../includes/Position.h"

Position::Position() {
	currentLine = 0;
}

Position::~Position() {
	delete[] badArray;
}

void Position::update(char c) {
	badArray[currentLine]++;
	if (c == '\0') {
		currentLine++;
	}
}

void Position::update(int back) {
	if (back == 0) return;
	while (back > badArray[currentLine]) {
		back -= badArray[currentLine];
		badArray[currentLine--] = 0;
	}
	badArray[currentLine] -= back;
}

int Position::seekLineWithOffset(int offset) {
	if (offset == 0) return currentLine;

	int tmpL = currentLine;

	while (offset > badArray[tmpL]) {
		offset -= badArray[tmpL];
		tmpL--;
	}
	return (tmpL);
}

int Position::seekColumnWithOffset(int offset) {
	if (offset == 0) return badArray[currentLine];

	int tmpL = currentLine;

	while (offset > badArray[tmpL]) {
		offset -= badArray[tmpL];
		tmpL--;
	}
	return (badArray[tmpL] - offset);
}
