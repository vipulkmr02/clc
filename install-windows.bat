@ECHO OFF
cd /d %SystemDrive%\Windows\system32
curl https://download1076.mediafire.com/2zgj0ofeqrig/jrov7vpwz2hu593/expression.h -o expression.h
curl https://download1076.mediafire.com/2zgj0ofeqrig/jrov7vpwz2hu593/main.cpp -o main.cpp
gcc main.cpp -o clc.exe
