#!/usr/bin/env bash
emcc src/cpp/*.cpp -s WASM=1 -o dist/main.js
cp src/js/*.js dist
cp src/*.html dist
