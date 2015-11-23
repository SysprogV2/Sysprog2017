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



#endif /* SCANNER_INCLUDES_POSITION_H_ */
