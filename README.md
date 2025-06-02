# YespowerADVC_WASM

This project provides a WebAssembly (WASM) build of the dual-variant `yespower` hashing algorithm used by [AdventureCoin (ADVC)](https://github.com/AdventureCoin-ADVC/AdventureCoin). It supports:

- `yespower 1.0` (after timestamp `1553904000`)
- `yespower 0.5` with personalization string `"Client Key"` (before timestamp `1553904000`)

It is optimized for use in web-based miners and JavaScript environments.

---

## 🔧 Prerequisites

Install the [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html):

```bash
git clone https://github.com/emscripten-core/emsdk.git
cd emsdk
./emsdk install latest
./emsdk activate latest
source ./emsdk_env.sh
```

## 📦 Clone This Repo
```bash
git clone https://github.com/CryptoDevelopmentServices/YespowerADVC_WASM.git
cd YespowerADVC_WASM
```
## 🚀 Build Instructions
Simply run the provided build script:

```bash
./build.sh
```
This will compile the `yespoweradvc.wasm` and `yespoweradvc.js` files, which can be used in browser or JavaScript environments.

🔔 If you see the message:
#warning "Note: building generic code for non-x86. That's OK."
— this is normal and expected for WebAssembly builds.

## 📂 Output Files
After building, you will get:

`yespoweradvc.wasm` – WebAssembly binary

`yespoweradvc.js` – JavaScript loader/glue code

## 🧪 Sample Browser Usage
Here's how to use it in a web page:

`index.html`
```html
<!DOCTYPE html>
<html>
<head>
  <meta charset="UTF-8">
  <title>YespowerADVC WASM Demo</title>
  <script src="yespoweradvc.js"></script>
</head>
<body>
  <h2>YespowerADVC Hash Demo</h2>
  <button onclick="runHash()">Run Test Hash</button>
  <pre id="result">Click the button above.</pre>

  <script>
    YespowerADVC().then(Module => {
      window.Module = Module;
    });

    function runHash() {
      const input = new Uint8Array(80);
      input.fill(0);
      
      // Set test timestamp >1553904000
      const ts = 1600000000;
      input[68] = ts & 0xff;
      input[69] = (ts >> 8) & 0xff;
      input[70] = (ts >> 16) & 0xff;
      input[71] = (ts >> 24) & 0xff;

      const inPtr = Module._malloc(80);
      const outPtr = Module._malloc(32);
      Module.HEAPU8.set(input, inPtr);

      Module._yespower_hash(inPtr, outPtr);

      const hash = Module.HEAPU8.slice(outPtr, outPtr + 32);
      const hex = Array.from(hash).map(b => b.toString(16).padStart(2, '0')).join('');

      Module._free(inPtr);
      Module._free(outPtr);

      document.getElementById("result").textContent = hex;
    }
  </script>
</body>
</html>
```
## 🧠 Notes
The WASM version is optimized for compatibility, not raw speed.

For performance mining, use a native binary (e.g., cpuminer or sugarmaker).

This is suitable for learning, experimenting, and building front-end miners.

#📜 License
MIT License © CryptoDevelopmentServices
