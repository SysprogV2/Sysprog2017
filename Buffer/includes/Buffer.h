/*
 * Buffer.h
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */

#ifndef BUFFER_H_
#define BUFFER_H_
#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h> //
#include <malloc.h>

#define DEFAULT_PATH_NAME "/home/arty/workspace/SysProgTemplate_SS_15/Buffer/buffer1"

class Buffer {
	char *next;
	int fd;
	char *buffer1;
	char *buffer2;
	const static size_t alignment = 4096;
    const static size_t size = 4095;
    char *filename = DEFAULT_PATH_NAME;
    ssize_t byte_read;
public:
	Buffer();
	~Buffer();
	Buffer(char *pathToFile);
	char getChar();
	void ungetChar(int back);
	void load(void * someBuffer);
	void allocateBufferMemory();
};



Buffer::Buffer() {
	/* open filename and return file descriptor */
	fd = open(filename, O_RDONLY, O_DIRECT);
	allocateBufferMemory();
}

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

/* TODO: fix this -> causes a lot of bugs!!!! */
void Buffer::ungetChar(int back) {
	next -= back;
	/*
	if (back < (&buffer1[0] - &next) || back < (&buffer2[0] - &next)) {
		next -= back;
	} else {
		//playbackHead -= back;
		load(buffer1);
	}
	*/
	//lseek(fd, size, SEEK_CUR);
}

/* Load given buffer with the shit from textfile */
void Buffer::load(void * someBuffer) {
	byte_read = read(fd, someBuffer, size - 1);
	if (byte_read < size - 1 && byte_read > 0) {
		char * tmp = (char *) someBuffer;
		tmp[byte_read] = '\0';
	}
	printf("read(%d, %p, %d) = %d\n", fd, someBuffer, size - 1, byte_read);
}


// TODO: make one mem allocation instead of two, idiot!
void Buffer::allocateBufferMemory() {
		int error;

		/* Buffer 1 */
		void *tmp1;
		error = posix_memalign(&tmp1, alignment, size);
	    if (error != 0) {
	        perror("posix_memalign");
	        exit(EXIT_FAILURE);
	    }
	    buffer1 = (char *) tmp1;
	    printf("posix_memalign(%d, %d) = %p\n", alignment, size, buffer1);

	    /* Buffer 2 */
	    void *tmp2;
	    error = posix_memalign(&tmp2, alignment, size);
	    if (error != 0) {
	        perror("posix_memalign");
	        exit(EXIT_FAILURE);
	    }
	    buffer2 = (char *) tmp2;
	    printf("posix_memalign(%d, %d) = %p\n", alignment, size, buffer2);

	    /* Load initial portion of file into Buffer1 */
	    load(buffer1);
	    next = buffer1;

	    /* Put constrains */
	    buffer1[size - 1] = '\0';
	    buffer2[size - 1] = '\0';
}

#endif /* BUFFER_H_ */
