/*
 * Errors.h
 *
 *  Created on: 20.01.2016
 *      Author: root
 */

#ifndef PARSER_INCLUDES_ERRORS_H_
#define PARSER_INCLUDES_ERRORS_H_

typedef enum {
	PROHIBITED_TOKEN,
	INVALID_SEMANTICS,
	NON_MATCHING_TYPES
}ErrorType;

void throwError(ErrorType type);
char* errorTypeToString(ErrorType type);

#endif /* PARSER_INCLUDES_ERRORS_H_ */
