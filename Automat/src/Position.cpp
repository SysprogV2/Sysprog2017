/*
 * Position.cpp
 *
 *  Created on: Nov 18, 2015
 *      Author: arty
 */


#include "../includes/Position.h"

Position::Position() {
	currentNode = new Node;
	tailPointer = currentNode;
	globalLine = 0;
	nodeNumber = 0;
}

Position::~Position() {

}

void Position::update(char c) {
	currentNode->col++;

	if (c == '\n') {
		globalLine++;
		/* add new node and link it to the previous */
		Node* tmp = new Node();
		currentNode->next = tmp;
		tmp->prev = currentNode;
		currentNode = tmp;

		/*
		nodeNumber++;
		if (nodeNumber > 90) {
			Node* tmps = tailPointer;
			tailPointer = tailPointer->next;
			delete tmps;
			nodeNumber--;
		}
		*/
	}
}

void Position::update(int back) {
	if (back == 0) return;
	while (back > currentNode->col) {
		back -= currentNode->col;
		currentNode->col = 0;
		currentNode = currentNode->prev;
		globalLine--;
	}
	currentNode->col -= back;
}

void Position::getPos(int offset, int& line, int& col) {
	if (offset == 0) {
		line = globalLine;
		col = currentNode->col;
	}

	Node *tmp = currentNode;
	int tmpLine = globalLine;
	while (offset > tmp->col) {
		offset -= tmp->col;
		tmp = tmp->prev;
		tmpLine--;
	}

	line = tmpLine + 1;
	col = tmp->col - offset + 1;
}
