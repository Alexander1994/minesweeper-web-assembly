#!/usr/bin/env bash
source ./../../Programs/emsdk/emsdk_env.sh
cd dist/
emrun --no_browser --port 8000 .
