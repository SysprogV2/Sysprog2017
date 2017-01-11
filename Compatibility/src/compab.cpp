//
// Created by Angelo on 14.12.2016.
//

#include "../includes/compab.h"

int check_align(size_t align) {
	for (size_t i = sizeof(void *); i != 0; i *= 2)
		if (align == i)
			return 0;
	return EINVAL;
}

int posix_memalign(void **ptr, size_t align, size_t size) {
	if (check_align(align))
		return EINVAL;

	int saved_errno = errno;
	void *p = aligned_alloc(size, align);
	if (p == NULL) {
		errno = saved_errno;
		return ENOMEM;
	}

	*ptr = p;
	return 0;
}