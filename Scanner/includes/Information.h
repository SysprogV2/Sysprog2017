/*
 * Information.h
 *
 *  Created on: Nov 11, 2015
 *      Author: arty
 */

#ifndef SCANNER_INCLUDES_INFORMATION_H_
#define SCANNER_INCLUDES_INFORMATION_H_

class Information {
	char* lexem;
public:
	Information();
	Information(char* lexem);
	virtual ~Information();
	void setLexem(char* lexem);
	char* getLexem();
	bool matches(char* other);
};

Information::Information() {

}

Information::Information(char* lexem) {
	setLexem(lexem);
}

Information::~Information() {
	this->lexem = lexem;
}

void Information::setLexem(char* lexem) {
	this->lexem = lexem;
}

char* Information::getLexem() {
	return lexem;
}

bool Information::matches(char* other) {
	char* tmp1 = this->lexem;
	char* tmp2 = other;
	while (tmp1[0] != '\0' && tmp2[0] != '\0') {
		if (tmp1++[0] != tmp2++[0]) {
			return false;
		}
	}
	return true;
}

#endif /* SCANNER_INCLUDES_INFORMATION_H_ */
