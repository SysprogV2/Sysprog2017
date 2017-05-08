/*
 * compab.h
 *
 *  Created on: 01.01.2016
 *      Author: work
 */

#ifndef COMPATIBILITY_COMPAB_H_
#define COMPATIBILITY_COMPAB_H_

#ifndef nullptr // skips if nullptr is a keyword? ok it does... phew...
#define nullptr 0
#endif

#ifdef __MINGW32__ // mapping posix_memalign on __mingw_assigned_malloc to ensure Windows compability (via MinGW)

#include <malloc.h>

int posix_memalign(void** pointer, size_t alignment, size_t size) { //
	int error = 0;
	*pointer = __mingw_aligned_malloc (size, alignment);
	if (*pointer == nullptr) {
		error = errno;
	}
	return error;
}

// TODO add include for O_DIRECT (location in MinGW) OR migrate project to Cygwin toolchain

#endif // MinGW mapping utility

#endif /* COMPATIBILITY_COMPAB_H_ */
