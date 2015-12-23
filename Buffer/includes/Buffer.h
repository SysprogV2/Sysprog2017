/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include <iostream>
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h> //
#include <malloc.h>

#define BUFFER_SIZE 2048
#define BUFFER_ALIGNMENT 4096

class Buffer {
	char *filename;
	int fd;
	char *buffer1;
	char *buffer2;
	char *terminator1;
	char *terminator2;

	char *next;
    char *theEndOfPrevBuffer;
    ssize_t byte_read;
    int shift;
    bool isAnymoreToRead;
    bool shouldLoadNewPortion;

    char *currentWorkingBuffer;
public:
	~Buffer();
	Buffer(char *pathToFile);
	char getChar();
	void ungetChar(int back);
	void load(void * someBuffer);
	void allocateBufferMemory();
};


#endif /* BUFFER_H_ */
