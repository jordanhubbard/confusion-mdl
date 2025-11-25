/*****************************************************************************/
/*    WASM Entry Point for Confusion MDL Interpreter                        */
/*    This provides JavaScript-callable functions                            */
/*****************************************************************************/

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <stdio.h>
#include <stdlib.h>
#include "gc_stub.h"
#include "macros.hpp"
#include "mdl_internal_defs.h"
#include "mdl_builtins.h"

// Warranty disclaimer (required by macros.cpp)
// Must be defined outside extern "C" since it's referenced from C++ code
const char no_warranty[] = "THERE IS NO WARRANTY FOR THIS PROGRAM, TO THE EXTENT PERMITTED BY\n"
"APPLICABLE LAW.  EXCEPT WHEN OTHERWISE STATED IN WRITING THE COPYRIGHT\n"
"HOLDERS AND/OR OTHER PARTIES PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY\n"
"OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO,\n"
"THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR\n"
"PURPOSE.  THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE PROGRAM\n"
"IS WITH YOU.  SHOULD THE PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF\n"
"ALL NECESSARY SERVICING, REPAIR OR CORRECTION.\n";

extern "C" {

// Initialize the interpreter
EMSCRIPTEN_KEEPALIVE
void mdl_interp_init_wasm() {
    GC_INIT();
    mdl_interp_init();
}

// Start the interpreter with game directory and restore file (REQUIRED to bootstrap game)
// game_dir: Path to game directory (e.g., "/game/mdlzork_810722")
// restore_file: Save file path relative to game directory (e.g., "SAVEFILE/ZORK.SAVE" or "MDL/MADADV.SAVE")
// Note: Save file is REQUIRED - the game cannot start without it
EMSCRIPTEN_KEEPALIVE
void mdl_start_game(const char* game_dir, const char* restore_file) {
    FILE* restorefile = NULL;
    
    // Change to game directory in virtual file system
    if (game_dir && game_dir[0] != '\0') {
        #ifdef __EMSCRIPTEN__
        // Use Emscripten's FS API directly via JavaScript
        EM_ASM({
            if (typeof Module !== 'undefined' && Module.FS) {
                try {
                    Module.FS.chdir(UTF8ToString($0));
                } catch(e) {
                    console.error('Failed to change directory:', e);
                }
            }
        }, game_dir);
        #endif
    }
    
    // Save file is REQUIRED to bootstrap the game
    if (!restore_file || restore_file[0] == '\0') {
        printf("Error: Save file is required to start the game.\n");
        printf("Please select a save file (e.g., SAVEFILE/ZORK.SAVE, MTRZORK/ZORK.SAVE, or MDL/MADADV.SAVE)\n");
        return;
    }
    
    restorefile = fopen(restore_file, "rb");
    if (!restorefile) {
        printf("Couldn't open restore file: %s\n", restore_file);
        return;
    }
    
    mdl_toplevel(restorefile);
}

// Main entry point (for compatibility)
EMSCRIPTEN_KEEPALIVE
int main_wasm(int argc, char** argv) {
    mdl_interp_init_wasm();
    
    FILE* restorefile = NULL;
    if (argc > 2 && strcmp(argv[1], "-r") == 0) {
        restorefile = fopen(argv[2], "rb");
        if (!restorefile) {
            printf("Couldn't open restore file: %s\n", argv[2]);
            return -1;
        }
    }
    
    mdl_toplevel(restorefile);
    return 0;
}

} // extern "C"

#endif // __EMSCRIPTEN__
