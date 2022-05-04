#pragma once

#include <stdio.h>
#include <stdlib.h>

// This won't work if the array is stored in the heap, or if it decayed into a pointer...
#define ARRAY_LENGTH_STACK(x) (int)(sizeof(x) / sizeof((x)[0]))

char *read_file(const char *filename, size_t *filesize);