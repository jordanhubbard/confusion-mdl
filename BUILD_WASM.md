# Building Confusion for WebAssembly

## Prerequisites

1. **Install Emscripten SDK**:
```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh  # On Windows: emsdk_env.bat
```

2. **Verify Installation**:
```bash
emcc --version
```

## Building

### Step 1: Navigate to confusion-mdl directory
```bash
cd confusion-mdl
```

### Step 2: Build WASM version
```bash
make -f Makefile.wasm
```

This will create:
- `mdli.js` - JavaScript wrapper
- `mdli.wasm` - WebAssembly binary
- `mdli.data` - Preloaded game files (if using --preload-file)

### Step 3: Test in Browser

1. Copy the generated files to a web server directory:
```bash
cp mdli.js mdli.wasm test_wasm.html /path/to/web/server/
cp -r ../../mdlzork_810722/patched_confusion /path/to/web/server/game
```

2. Serve with a local web server (required for WASM):
```bash
# Python 3
python3 -m http.server 8000

# Or Node.js
npx http-server -p 8000
```

3. Open browser: `http://localhost:8000/test_wasm.html`

## Troubleshooting

### Error: "Emscripten not found"
- Make sure Emscripten is installed and activated
- Run `source ./emsdk_env.sh` in your terminal

### Error: "mdli.js not found" in browser
- Make sure you're serving files through a web server (not file://)
- Check that mdli.js and mdli.wasm are in the same directory

### Error: "Game files not found"
- Make sure game files are preloaded or accessible via Emscripten FS
- Check the `--preload-file` path in Makefile.wasm

### Compilation Errors

**Error: "gc/gc.h: No such file"**
- This is expected - we're using `gc_stub.h` instead
- Make sure all `#include <gc/gc.h>` have been replaced with `#include "gc_stub.h"`

**Error: "undefined reference to GC_*"**
- Check that `gc_stub.h` is being included
- Verify `-DEMSCRIPTEN` flag is set

## Development Tips

### Debug Build
Change `-O2` to `-g` in Makefile.wasm for debugging:
```makefile
COPTFLAGS = -g  # Instead of -O2
```

### Memory Limits
If you get memory errors, increase limits in Makefile.wasm:
```makefile
-s INITIAL_MEMORY=32MB  # Increase from 16MB
-s MAXIMUM_MEMORY=512MB  # Increase from 256MB
```

### File System
To add more game files, update the preload path:
```makefile
--preload-file ../../mdlzork_810722/patched_confusion@/game
```

## Next Steps

1. **Test Basic Functionality**: Verify interpreter initializes
2. **Add Input Handling**: Implement stdin redirection
3. **Add Save/Restore**: Use IndexedDB for persistence
4. **Polish UI**: Integrate xterm.js for better terminal

## Files Created

- `gc_stub.h` - GC replacement for WASM
- `Makefile.wasm` - WASM build configuration
- `mdli_wasm.cpp` - WASM entry point (optional)
- `test_wasm.html` - Test page
- `BUILD_WASM.md` - This file

## Notes

- Memory leaks are acceptable for browser sessions (see GC_ANALYSIS.md)
- Game files are preloaded into Emscripten's virtual file system
- Save files can use IndexedDB for browser persistence
