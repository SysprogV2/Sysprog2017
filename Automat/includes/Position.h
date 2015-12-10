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
	Node* tailPointer;
	int nodeNumber;
	Node* currentNode;
	int currentLine;
public:
	Position();
	virtual ~Position();
	void update(char c);
	void update(int back);
	void getPos(int offset, int& line, int& col);
};



#endif /* SCANNER_INCLUDES_POSITION_H_ */
