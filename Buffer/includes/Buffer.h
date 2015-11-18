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

Buffer::~Buffer() {
	/* Close file descriptor */
	close(fd);
}

Buffer::Buffer(char *pathToFile) {
	filename = pathToFile;
	fd = open(filename, O_RDONLY, O_DIRECT);
	allocateBufferMemory();
}

char Buffer::getChar() {
	if (next[0] == '\0') {
		if (next == &buffer1[size - 1]) {
			load(buffer2);
			next = buffer2;
		} else if (next == &buffer2[size - 1]) {
			load(buffer1);
			next = buffer1;
		} else {
			return next[0];
		}
	}
	return next++[0];
}

/* TODO: fix this -> could cause a shitload of bugs!!! */
void Buffer::ungetChar(int back) {
	next -= back;
}

/* Load given buffer with the shit from textfile */
void Buffer::load(void * someBuffer) {
	byte_read = read(fd, someBuffer, size - 1);
	if (byte_read < (signed) (size - 1) && byte_read > 0) {
		char * tmp = (char *) someBuffer;
		tmp[byte_read] = '\0';
	}
	//printf("read(%d, %p, %d) = %d\n", fd, someBuffer, size - 1, byte_read);
}

void Buffer::allocateBufferMemory() {
		int error;

		/* Buffer 1 */
	    buffer1 = (char *) alloc();

	    /* Buffer 2 */
	    buffer2 = (char *) alloc();

	    /* Load initial portion of file into Buffer1 */
	    load(buffer1);
	    next = buffer1;

	    /* Put constrains */
	    buffer1[size - 1] = '\0';
	    buffer2[size - 1] = '\0';
}

void* Buffer::alloc() {
	void *tmp1;
	int error = posix_memalign(&tmp1, alignment, size);
	if (error != 0) {
	    perror("posix_memalign");
	    exit(EXIT_FAILURE);
	}
	printf("posix_memalign(%d, %d) = %p\n", alignment, size, (char*)tmp1);
	return tmp1;
}
#endif /* BUFFER_H_ */
