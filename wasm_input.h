/*****************************************************************************/
/*    WASM Input Helper for Emscripten                                      */
/*    Provides non-blocking input wrapper for browser environment           */
/*****************************************************************************/
#ifndef WASM_INPUT_H
#define WASM_INPUT_H

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <stdio.h>

// Wrapper for getc() that yields control back to browser when no input available
static inline int wasm_getc_with_yield(FILE *f) {
    int c;
    
    // Loop indefinitely waiting for input
    // User can always close browser tab if they want to stop
    while (1) {
        c = getc(f);
        if (c != EOF) {
            return c;
        }
        
        // Check if it's a real EOF or just no data available
        if (feof(f)) {
            clearerr(f); // Clear EOF flag
        }
        
        // Yield control back to browser for 10ms
        // ASYNCIFY allows this to work properly
        emscripten_sleep(10);
    }
}

// Replace getc in Emscripten builds
#define getc(f) wasm_getc_with_yield(f)

#endif // __EMSCRIPTEN__

#endif // WASM_INPUT_H
