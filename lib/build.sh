#!/usr/bin/env bash
loc="dist"
if [[ "$1" == "web" ]]; then
  loc="."
fi
emcc src/cpp/*.cpp -s WASM=1 -o $loc/main.js
cp src/js/*.js $loc
cp src/*.html $loc
