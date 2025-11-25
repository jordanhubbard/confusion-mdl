# Quick Start: WASM Build

## 1: Install Emscripten (One-time setup)

```bash
# Clone Emscripten SDK
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk

# Install and activate latest version
./emsdk install latest
./emsdk activate latest

# Activate in current shell
source ./emsdk_env.sh  # On macOS/Linux
# OR
emsdk_env.bat          # On Windows
```

## Step 2: Build WASM

```bash
cd confusion-mdl
make -f Makefile.wasm
```

Expected output:
- `mdli.js` - JavaScript wrapper (~100-500 KB)
- `mdli.wasm` - WebAssembly binary (~500 KB - 2 MB)
- `mdli.data` - Preloaded files (if using --preload-file)

## Step 3: Test

```bash
# Start a web server (required for WASM)
python3 -m http.server 8000

# Open browser
open http://localhost:8000/test_wasm.html
```

## Troubleshooting

**"emcc: command not found"**
→ Run `source ./emsdk_env.sh` in your terminal

**"mdli.js not found" in browser**
→ Make sure you're using a web server (not file://)

**Compilation errors about gc/gc.h**
→ Check that all files use `gc_stub.h` (should already be done)

## What's Next?

Once it builds:
1. Test interpreter initialization
2. Add input handling
3. Test game loading
4. Implement save/restore

See `BUILD_WASM.md` for detailed instructions.
