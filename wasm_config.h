/*
 * wasm_config.h - Configuration for WebAssembly builds
 * 
 * This file defines WASM-specific settings and disables features
 * that are not available or practical in a browser environment.
 */

#ifndef WASM_CONFIG_H
#define WASM_CONFIG_H

/* Use GC stub instead of Boehm GC */
#define USE_GC_STUB 1

/* Disable features not available in WASM */
#define NO_SIGNALS 1
#define NO_FORK 1
#define NO_PROCESS_CONTROL 1

/* Emscripten filesystem configuration */
#define WASM_FS_ROOT "/game"
#define WASM_SAVE_PATH "/saves"

/* Memory configuration */
#define WASM_INITIAL_MEMORY (16 * 1024 * 1024)  /* 16MB initial */
#define WASM_MAX_MEMORY (256 * 1024 * 1024)      /* 256MB max */
#define WASM_STACK_SIZE (5 * 1024 * 1024)        /* 5MB stack */

/* Platform detection */
#ifdef __EMSCRIPTEN__
#define PLATFORM_WASM 1
#else
#define PLATFORM_WASM 0
#endif

#endif /* WASM_CONFIG_H */
