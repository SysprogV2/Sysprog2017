/*
 * SymtabEntry.cpp
 *
 *  Created on: Nov 21, 2015
 *      Author: arty
 */
#include "../includes/SymtabEntry.h"
#include "../../Scanner/includes/Information.h"

SymtabEntry::SymtabEntry(Information* info) {
	this->information = info;
	next = this;
}

SymtabEntry::SymtabEntry() {

}

SymtabEntry::SymtabEntry(SymtabEntry* next) {
	this->next = next;
}
void SymtabEntry::setInfo(Information *info) {
	this->information = info;
}
Information* SymtabEntry::getInfo() {
	return this->information;
}
SymtabEntry* SymtabEntry::getNext() {
	return next;
}

SymtabEntry::~SymtabEntry() {

}
