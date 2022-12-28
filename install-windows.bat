@ECHO OFF
cd  %ProgramFiles%
mkdir clc
attrib clc +h
cd clc
curl "https://raw.githubusercontent.com/Coder-12-ux/clc/main/expression.h" -o expression.h
curl "https://raw.githubusercontent.com/Coder-12-ux/clc/main/main.cpp" -o main.cpp
g++ main.cpp -o clc.exe
set PATH=%PATH%";"%cd%
