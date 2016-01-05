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
	fd = open(filename, O_RDONLY, O_DIRECT); // TODO find a Windows replacement for O_DIRECT and define it as O_DIRECT in compab.h
	allocateBufferMemory();
	shift = 0;
	isAnymoreToRead = true;
	shouldLoadNewPortion = true;
}

char Buffer::getChar() {
	if (isAnymoreToRead) {
		if (next == terminator1) {
			theEndOfPrevBuffer = --next;
			if (shouldLoadNewPortion) load(buffer2);
			next = buffer2;
			shouldLoadNewPortion = true; // perhaps better: shouldLoadNewPortion = isAnymoreToRead;
		} else if (next == terminator2) {
			theEndOfPrevBuffer = --next;
			if (shouldLoadNewPortion) load(buffer1);
			next = buffer1;
			shouldLoadNewPortion = true; // perhaps better: shouldLoadNewPortion = isAnymoreToRead;
		}
	} else {
		if (byte_read == 0) {
			return '\0';
		}
	}
	shift++;
	return next++[0];
}

void Buffer::ungetChar(int back) {
	next -= back;
	shift -= back;

	if (shift < 0) {
		shift++;
		next = theEndOfPrevBuffer;
		next -= (shift) * sizeof(char);
		shouldLoadNewPortion = false;
	}

}

/* Load given buffer with a content of a textfile */
void Buffer::load(void * someBuffer) {
	byte_read = read(fd, someBuffer, (BUFFER_SIZE / 2) - 1);
	if (byte_read < (signed) ((BUFFER_SIZE / 2) - 1) && byte_read >= 0) {
		char * tmp = (char *) someBuffer;
		tmp[byte_read++] = '\n';
		tmp[byte_read] = '\0';
		isAnymoreToRead = false;
	}
	shift = 0;
}

void Buffer::allocateBufferMemory() {
		void *tmp1;
		int error = posix_memalign(&tmp1, BUFFER_ALIGNMENT, BUFFER_SIZE);
		if (error != 0) {
		    std::cout << "Couldn't allocate memory. Exiting..." << std::endl;
		    exit(EXIT_FAILURE);
		}

		buffer1 = (char *) tmp1;
		terminator1 = buffer1 + ((BUFFER_SIZE / 2) - 1) * sizeof(char);
		terminator1[0] = '\0';

		buffer2 = terminator1 + sizeof(char);
		terminator2 = buffer2 + ((BUFFER_SIZE / 2) - 1) * sizeof(char);
		terminator2[0] = '\0';

	    load(buffer1);
	    next = buffer1;


}

