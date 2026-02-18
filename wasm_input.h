/*****************************************************************************/
/*    WASM Input Helper for Emscripten                                      */
/*    Provides async stdin via EM_ASYNC_JS for browser environment          */
/*****************************************************************************/
#ifndef WASM_INPUT_H
#define WASM_INPUT_H

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <stdio.h>

/*
 * Async JavaScript function that waits for stdin input from the browser.
 *
 * This uses Emscripten's EM_ASYNC_JS which creates a proper async import
 * that Asyncify handles at the WASM boundary.  This is much more reliable
 * than the FS.init stdin callback approach, which runs inside a JavaScript
 * loop that Asyncify cannot save/restore (it only saves the WASM stack).
 *
 * On the JS side:
 *   Module.stdinBuffer  - array of pending character codes
 *   Module.stdinResolve - Promise resolve callback when waiting for input
 */
EM_ASYNC_JS(int, wasm_stdin_getchar, (), {
    if (Module.stdinBuffer && Module.stdinBuffer.length > 0) {
        return Module.stdinBuffer.shift();
    }
    return await new Promise(function(resolve) {
        Module.stdinResolve = resolve;
    });
});

/* Use fgetc (guaranteed to be a function, not a macro) for non-stdin files */
#ifdef getc
#undef getc
#endif

static inline int wasm_getc_wrapper(FILE *f) {
    if (f == stdin) {
        return wasm_stdin_getchar();
    }
    return fgetc(f);
}

#define getc(f) wasm_getc_wrapper(f)

#endif /* __EMSCRIPTEN__ */
#endif /* WASM_INPUT_H */
