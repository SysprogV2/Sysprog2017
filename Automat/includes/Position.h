/*
 * Position.h
 *
 *  Created on: Oct 23, 2015
 *      Author: arty
 */

#ifndef SCANNER_INCLUDES_POSITION_H_
#define SCANNER_INCLUDES_POSITION_H_
#include <iostream>
class Position {
	struct Node {
		Node* prev;
		Node* next;
		int col = 0;
	};
	int globalLine;
	Node* currentNode;
	int currentLine;
	int stateN;
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
