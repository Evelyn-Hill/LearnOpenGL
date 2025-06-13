@echo off

start cmake -B build -G "Ninja"

start cmake --build build

start ./build/OpenGL.exe
