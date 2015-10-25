/*
 * Position.h
 *
 *  Created on: Oct 23, 2015
 *      Author: arty
 */

#ifndef SCANNER_INCLUDES_POSITION_H_
#define SCANNER_INCLUDES_POSITION_H_

class Position {
	int currentLine;
	int badArray[50000] = {0}; // TODO: fix this -> use vector!instead!!
public:
	Position();
	virtual ~Position();
	void update(char c);
	void update(int back);
	int seekLineWithOffset(int offset);
	int seekColumnWithOffset(int offset);
};

Position::Position() {
	currentLine = 0;
}

Position::~Position() {
	delete[] badArray;
}

void Position::update(char c) {
	badArray[currentLine]++;
	if (c == '\n') {
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

#endif /* SCANNER_INCLUDES_POSITION_H_ */
