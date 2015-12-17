/*
 * Buffer.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: knad0001
 */
#include "../includes/Buffer.h"
Buffer::~Buffer() {
	/* Close file descriptor */
	close(fd);
}

Buffer::Buffer(char *pathToFile) {
	filename = pathToFile;
	fd = open(filename, O_RDONLY, O_DIRECT);
	allocateBufferMemory();
	shift = 0;
}

char Buffer::getChar() {
	if (next[0] == '\0') {
		if (next == &buffer1[(BUFFER_SIZE / 2) - 1]) {
			load(buffer2);
			next = buffer2;
		} else if (next == &buffer2[(BUFFER_SIZE / 2) - 1]) {
			load(buffer1);
			next = buffer1;
		} else {
			return next[0];
		}
	}
	shift++;
	return next++[0];
}

/* TODO: fix this -> could cause a lot of bugs!!! */
void Buffer::ungetChar(int back) {
	next -= back;
	shift -= back;
	if (shift > -1 && shift < 1) printf(" %d \n", shift);
}

/* Load given buffer with a content of a textfile */
void Buffer::load(void * someBuffer) {
	byte_read = read(fd, someBuffer, (BUFFER_SIZE / 2) - 1);
	if (byte_read < (signed) ((BUFFER_SIZE / 2)) && byte_read > 0) {
		char * tmp = (char *) someBuffer;
		tmp[byte_read] = '\0';
	}
	shift = 1;
	//printf("read(%d, %p, %d) = %d\n", fd, someBuffer, (BUFFER_SIZE / 2) - 1, byte_read);
}

void Buffer::allocateBufferMemory() {
		void *tmp1;
		int error = posix_memalign(&tmp1, BUFFER_ALIGNMENT, BUFFER_SIZE);
		if (error != 0) {
		    std::cout << "Couldn't allocate memory. Exiting..." << std::endl;
		    exit(EXIT_FAILURE);
		}
		char* terminator;

		buffer1 = (char *) tmp1;
		terminator = buffer1 + ((BUFFER_SIZE / 2) - 1) * sizeof(char);
		terminator[0] = '\0';

		buffer2 = buffer1 + sizeof(char);
		terminator = buffer2 + ((BUFFER_SIZE / 2) - 1) * sizeof(char);
		terminator[0] = '\0';

	    load(buffer1);
	    next = buffer1;


}

