@ECHO OFF
mkdir clc
cd clc
curl "https://raw.githubusercontent.com/Coder-12-ux/clc/main/expression.h" -o expression.h
curl "https://raw.githubusercontent.com/Coder-12-ux/clc/main/main.cpp" -o main.cpp
g++ main.cpp -o clc.exe
move clc %ProgramFiles%
set PATH=%PATH%";"%cd%
