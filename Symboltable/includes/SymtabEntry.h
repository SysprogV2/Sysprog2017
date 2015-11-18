/*
 * SymtabEntry.h
 *
 *  Created on: Nov 12, 2015
 *      Author: arty
 */

#ifndef SYMBOLTABLE_INCLUDES_SYMTABENTRY_H_
#define SYMBOLTABLE_INCLUDES_SYMTABENTRY_H_

#include "../Scanner/includes/Information.h"

class SymtabEntry {
	Information* information;
public:
	SymtabEntry(Information* info);
	virtual ~SymtabEntry();

};

SymtabEntry::SymtabEntry(Information* info) {
	information = info;
}

#endif /* SYMBOLTABLE_INCLUDES_SYMTABENTRY_H_ */
