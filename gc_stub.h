/*
 * gc_stub.h - Boehm GC stub for WebAssembly builds
 * 
 * This file provides replacements for Boehm GC functions when building
 * for WebAssembly with Emscripten. Since WASM has its own memory management
 * and the Boehm GC is not available/practical in WASM, we use simple
 * malloc/free wrappers.
 *
 * NOTE: This is a minimal implementation. We rely on:
 * 1. WASM's memory growth capabilities
 * 2. Short game sessions (memory leaks won't accumulate much)
 * 3. Browser tab closure for ultimate cleanup
 *
 * Future improvements could add a simple mark-and-sweep collector
 * if memory usage becomes problematic.
 */

#ifndef GC_STUB_H
#define GC_STUB_H

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Basic memory allocation - just wrap malloc/free */
#define GC_MALLOC(n) malloc(n)
#define GC_MALLOC_ATOMIC(n) malloc(n)
#define GC_MALLOC_IGNORE_OFF_PAGE(n) malloc(n)
#define GC_REALLOC(p, n) realloc(p, n)
#define GC_FREE(p) free(p)

/* Initialization - no-op */
#define GC_INIT() ((void)0)

/* Manual collection - no-op (could implement simple collector later) */
static inline void GC_gcollect(void) {
    /* No-op for now. WASM memory model handles this. */
}

/* GC cycle number - used for tracking when to clean weak references
 * We'll just increment a counter on each "collection" attempt */
typedef unsigned long GC_word;
extern GC_word GC_gc_no;

/* Weak reference support - simplified 
 * Disappearing links allow objects to be collected even if referenced
 * We'll stub these out since WASM doesn't have the same GC semantics */
static inline int GC_GENERAL_REGISTER_DISAPPEARING_LINK(void **link, void *obj) {
    /* In a real implementation, this would register 'link' to be 
     * cleared when 'obj' is collected. For now, do nothing. */
    (void)link;
    (void)obj;
    return 0;
}

static inline int GC_unregister_disappearing_link(void **link) {
    /* Unregister a disappearing link */
    (void)link;
    return 0;
}

/* Debug support */
#ifdef GC_DEBUG
#define GC_DEBUG_ENABLED 1
#else
#define GC_DEBUG_ENABLED 0
#endif

#ifdef __cplusplus
}

/* C++ STL allocator support - just use standard allocator */
#include <memory>
#include <new>

template<typename T>
using gc_allocator = std::allocator<T>;

template<typename T>
using traceable_allocator = std::allocator<T>;

/* Boehm GC placement new support
 * The real GC uses special operators, we just redirect to standard new */
class GCPlacement {};
extern GCPlacement UseGC;
extern GCPlacement NoGC;

/* Override placement new to ignore the GC hint */
inline void* operator new(size_t size, GCPlacement) {
    return ::operator new(size);
}

inline void* operator new[](size_t size, GCPlacement) {
    return ::operator new[](size);
}

#endif

#endif /* GC_STUB_H */
