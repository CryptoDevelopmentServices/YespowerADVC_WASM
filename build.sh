#!/bin/bash

emcc -O3 \
  -s MODULARIZE=1 \
  -s EXPORT_NAME="YespowerADVC" \
  -s EXPORTED_FUNCTIONS='["_malloc", "_free", "_yespower_hash"]' \
  -s EXPORTED_RUNTIME_METHODS='["cwrap", "getValue", "setValue"]' \
  yespoweradvc.c sha256.c yespower_core.c \
  -o yespoweradvc.js
