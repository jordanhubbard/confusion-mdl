/*
 * GC Stub Header for WASM Compilation
 * 
 * This file provides a drop-in replacement for Boehm GC when compiling
 * to WebAssembly. It uses standard malloc/free instead of garbage collection.
 * 
 * For native builds, include the real GC headers.
 * For WASM builds, use standard C library functions.
 */

#ifndef GC_STUB_H
#define GC_STUB_H

#ifdef __EMSCRIPTEN__
    // WASM Build: Use standard malloc/free
    // Memory leaks are acceptable for browser game sessions
    
    #include <stdlib.h>
    #include <string.h>
    
    // Replace GC functions with standard equivalents
    #define GC_MALLOC malloc
    #define GC_REALLOC realloc
    #define GC_FREE free
    #define GC_MALLOC_ATOMIC malloc
    #define GC_MALLOC_IGNORE_OFF_PAGE malloc
    
    // GC initialization (no-op for WASM)
    #define GC_INIT() 
    
    // GC collection (no-op for WASM)
    #define GC_gcollect()
    
    // GC disappearing links (no-op for WASM - not needed without GC)
    #define GC_GENERAL_REGISTER_DISAPPEARING_LINK(link, obj) ((void)0)
    #define GC_unregister_disappearing_link(link) ((void)0) 
    
    // GC types (stubs)
    typedef int GC_word;
    
    // GC generation counter (stub function)
    inline GC_word GC_get_gc_no(void) { return 0; }
    
    // GC allocator for STL containers (use standard allocator)
    // Note: This is defined in macros.hpp via gc_allocator.h for native builds
    // For WASM, we'll use standard allocator
    #ifdef __cplusplus
        #include <memory>
        template<typename T>
        using traceable_allocator = std::allocator<T>;
        
        // Alias gc_allocator to std::allocator for WASM builds
        // (gc_allocator is what the code expects from gc/gc_allocator.h)
        template<typename T>
        using gc_allocator = std::allocator<T>;
        
        // UseGC placement new - for WASM, use std::nothrow as a placement tag
        // This allows new (UseGC) to compile and use regular allocation
        #include <new>
        #define UseGC std::nothrow
    #endif
    
#else
    // Native Build: Use Boehm GC
    #include <gc/gc.h>
    
    // Only include C++ headers when compiling C++ code
    #ifdef __cplusplus
        #include <gc/gc_allocator.h>
        #include <gc/gc_cpp.h>
        // UseGC placement new for GC-aware allocation
        #define UseGC GC
    #endif
#endif

#endif // GC_STUB_H
