/*
 * compab.h
 *
 *  Created on: 01.01.2016
 *      Author: work
 */

#define __WIN32__ //always use Windows

#ifndef COMPATIBILITY_COMPAB_H_
#define COMPATIBILITY_COMPAB_H_

#ifndef nullptr // skips if nullptr is a keyword? ok it does... phew...
#define nullptr 0
#endif

#if defined(__MINGW32__ ) || defined(__WIN32__) // mapping posix_memalign on __mingw_assigned_malloc to ensure Windows compability (via MinGW)
#ifndef __WIN32_DEF__
#define __WIN32_DEF__

#include <stdlib.h>
#include <malloc.h>
#include <errno.h>

extern int check_align(size_t align);
extern int posix_memalign(void **ptr, size_t align, size_t size);

#endif // __WIN32_DEF__
#endif // __MINGW32__ || __WIN32__

#endif /* COMPATIBILITY_COMPAB_H_ */
