/*
 * gc_stub.c - Implementation of GC stub globals
 */

#include "gc_stub.h"

/* Global GC cycle counter - incremented on each "collection" */
GC_word GC_gc_no = 0;

#ifdef __cplusplus
/* C++ placement new helpers */
GCPlacement UseGC;
GCPlacement NoGC;
#endif
