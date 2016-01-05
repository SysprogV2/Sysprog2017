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
	this->information = info;
	this->next = this;
}

SymtabEntry::SymtabEntry() {
	this->information = nullptr;
	this->next = nullptr;
}

SymtabEntry::SymtabEntry(SymtabEntry* nextEntry) {
	this->next = nextEntry;
}
void SymtabEntry::setInfo(Information *info) {
	this->information = info;
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
