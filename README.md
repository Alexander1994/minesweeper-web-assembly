# minesweeper-web-assembly

The purpose of this is to create a primitve version of minesweeper using web assembly.
With the long term goal of writing a computer algorithm to solve minesweeper.

url: [AlexMcCallum.me/minesweeper-web-assembly](http://AlexMcCallum.me/minesweeper-web-assembly)


# Build locally

first install [emsdk](http://webassembly.org/getting-started/developers-guide/) to compile the C++ to WebAssembly
```
cd minesweeper-web-assembly
mkdir dist
./lib/setEnvVars.sh
./lib/build.sh
./lib/server.sh
```
Then checkout localhost:8000
