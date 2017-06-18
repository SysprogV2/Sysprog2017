/*
 * Errors.cpp
 *
 *  Created on: 20.01.2016
 *      Author: root
 */


#include "../includes/Errors.h"

void throwError(ErrorType type) {
	const char* errorString = errorTypeToString(type);
	throw errorString;
}

const char* errorTypeToString(ErrorType type) {
	switch(type) {
	case PROHIBITED_TOKEN:
		return "Error: Token is not defined by the standard";
	case INVALID_SEMANTICS:
		return "Error: Tokens form incompilable code";
	case NON_MATCHING_TYPES:
		return "Error: Cannot convert from int[] to int";
	}

	return "Unknown error";
}
