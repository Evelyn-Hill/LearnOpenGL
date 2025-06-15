@echo off

start cmake -B build -G "Ninja"

start cmake --build build
	
pause

start ./build/OpenGL.exe
