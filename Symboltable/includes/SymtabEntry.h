/*
 * SymtabEntry.h
 *
 *  Created on: Nov 12, 2015
 *      Author: arty
 */

#ifndef SYMBOLTABLE_INCLUDES_SYMTABENTRY_H_
#define SYMBOLTABLE_INCLUDES_SYMTABENTRY_H_

#include "../../Scanner/includes/Information.h"

class SymtabEntry {
	Information* information;
	SymtabEntry* next;
public:
	explicit SymtabEntry(SymtabEntry* next);
	explicit SymtabEntry(Information* info);
	SymtabEntry();
	void setInfo(Information* info);
	Information* getInfo();
	SymtabEntry* getNext();
	virtual ~SymtabEntry();

};


#endif /* SYMBOLTABLE_INCLUDES_SYMTABENTRY_H_ */
