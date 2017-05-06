/*
 * TokenSequence.cpp
 *
 *  Created on: 03.01.2016
 *      Author: work
 */

#include "../includes/TokenSequence.h"

TokenSequence::TokenSequence(int initialCapacity, int initialIncrement) {
	this->capacity = initialCapacity < 0 ? 0 : initialCapacity;
	this->increment = initialIncrement < 1 ? 1 : initialIncrement;
	this->sequence = new Token* [this->capacity];
	this->size = 0;
	this->currentPos = 0;
	this->tokensReferenced = true;
}

TokenSequence::TokenSequence(TokenSequence* other) {
	this->capacity = other->capacity;
	this->increment = other->increment;
	this->sequence = new Token*[this->capacity];
	for (int i = 0; i < other->size; i++) {
		this->sequence[i] = other->sequence[i];
	}
	this->size = other->size;
	this->currentPos = other->currentPos;
	this->tokensReferenced = other->tokensReferenced;
}

void TokenSequence::add (Token* token, bool setAsCurrent) {
	if (this->size == this->capacity) {
		Token** temp = this->sequence;
		this->capacity += this->increment;
		this->sequence = new Token* [this->capacity];
		for (int i = 0; i < this->size; i++) {
			this->sequence[i] = temp [i];
			temp [i] = nullptr;
		}
		delete[] temp;
	}
	this->sequence [this->size++] = token;
	if (setAsCurrent) {
		this->currentPos = this->size - 1;
	}
}

void TokenSequence::clear (bool areStillReferenced) {
	for (int i = 0; i < this->size; i++) {
		if (!areStillReferenced) delete this->sequence[i];
		else this->sequence[i] = nullptr;
	}
	this->size = 0;
}

Token* TokenSequence::tokenAt (int index, bool jumpTo) {
	if (jumpTo) this->currentPos = index;
	return this->sequence[index];
}

Token* TokenSequence::current() {
	return this->sequence[this->currentPos];
}

Token* TokenSequence::next (bool jumpTo) {
	if (jumpTo) this->currentPos++;
	return this->sequence [this->currentPos + (jumpTo ? 0 : 1)];
}

Token* TokenSequence::previous (bool jumpTo) {
	if (jumpTo) this->currentPos--;
	return this->sequence [this->currentPos - (jumpTo ? 0 : 1)];
}

void TokenSequence::setIncrement( int nextIncrement) {
	this->increment = nextIncrement < 1 ? 1 : nextIncrement;
}

int TokenSequence::getSize() {
	return this->size;
}

TokenSequence* TokenSequence::splitOn(int index, TokenSequence** subsequence2) {
	if (index < 0) {
		*subsequence2 = new TokenSequence (this); // subsequence2 is entire sequence
		return new TokenSequence (10, 10); // subsequence1 is empty
	}
	if (index >= this->size - 1) {
		*subsequence2 = new TokenSequence (10, 10); // subsequence2 is empty
		return new TokenSequence (this); // subsequence1 is entire sequence
	}
	TokenSequence* subsequence1 = new TokenSequence (10, 10);
	*subsequence2 = new TokenSequence (10, 10);
	// entire array is being copied -> might be a runtime issue
	for (int i = 0; i < this->size; i++) {
		if (i <= index) {
			subsequence1->add(this->sequence[i], false);
		} else {
			(*subsequence2)->add(this->sequence[i], false);
		}
	}
	return subsequence1;
}

void TokenSequence::prepareDelete(bool tokensReferenced) {
	this->tokensReferenced = tokensReferenced;
}

TokenSequence::~TokenSequence () {
	this->clear(this->tokensReferenced);
	delete[] this->sequence;
}

IntQueue::IntLinker::IntLinker() {
	this->value = 0;
	this->next = nullptr;
	this->previous = nullptr;
}

IntQueue::IntLinker::~IntLinker() {
	delete this->next;
	delete this->previous;
}

IntQueue::IntQueue() {
	this->size = 0;
	this->first = nullptr;
	this->last = nullptr;
}

void IntQueue::push(int value){
	IntLinker* temp = this->last;
	this->last = new IntLinker();
	this->last->value = value;
	this->last->next = nullptr;
	if (this->size++ == 0) {
		this->first = this->last;
		this->first->previous = nullptr;
	} else {
		temp->next = this->last;
		this->last->previous = temp;
	}
}

void IntQueue::undoPushing() {
	if (this->size == 0) return;
	if (this->size-- == 1 ) {
		std::cout << "Dangerous spot in IntQueue started\n";
		delete this->first;
		//delete this->last;
		std::cout << "Dangerous spot passed without error\n";
	} else {
		this->last = this->last->previous;
		this->last->next->previous = nullptr;
		delete this->last->next;
	}
}

int IntQueue::pop() {
	if (this->size == 0) return 0;
	int temp = this->first->value;
	if (this->size-- == 1 ) {
		delete this->first;
		//delete this->last;
	} else {
		this->first = this->first->next;
		this->first->previous->next = nullptr;
		delete this->first->previous;
	}
	return temp;
}

int IntQueue::fetch() {
	return this->first->value;
}

int IntQueue::getSize() {
	return this->size;
}

IntQueue::~IntQueue() {
	delete this->first;
	//delete this->last;
}

LabelFactory::LabelFactory(int firstLabelNo) {
	this->currentLabelNo = firstLabelNo;
}

int LabelFactory::newLabel() {
	return this->currentLabelNo++;
}

LabelFactory::~LabelFactory() {}

