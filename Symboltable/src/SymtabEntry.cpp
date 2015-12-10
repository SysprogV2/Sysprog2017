/*
 * SymtabEntry.cpp
 *
 *  Created on: Nov 21, 2015
 *      Author: arty
 */
#include "../includes/SymtabEntry.h"
#include "../../Scanner/includes/Information.h"
#include <iostream>
SymtabEntry::SymtabEntry(Information* info) {
	information = info;
	next = this;
}

SymtabEntry::SymtabEntry() {
	//this->information = NULL;
	//next = this;
}

SymtabEntry::SymtabEntry(SymtabEntry* nextE) {
	next = nextE;
}
void SymtabEntry::setInfo(Information *info) {
	information = info;
}
Information* SymtabEntry::getInfo() {
	Information *some = information;
	return  some;
}
SymtabEntry* SymtabEntry::getNext() {
	return next;
}

SymtabEntry::~SymtabEntry() {

}
