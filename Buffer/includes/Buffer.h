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

class Buffer {
	char *next;
	int fd;
	char *buffer1;
	char *buffer2;
	const static size_t alignment = 4096;
    const static size_t size = 4096;
    char *filename;
    ssize_t byte_read;

    char *currentWorkingBuffer;
public:
	~Buffer();
	Buffer(char *pathToFile);
	char getChar();
	void ungetChar(int back);
	void load(void * someBuffer);
	void allocateBufferMemory();
	void* alloc();
};


#endif /* BUFFER_H_ */
