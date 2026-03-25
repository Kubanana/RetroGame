#!/bin/bash

mkdir build
cd build
cmake ..
cmake --build .
chmod +x debug/RetroGame
./debug/RetroGame
