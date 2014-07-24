@echo off
color F

set PATH=..\ACC
set SRC=.\pk3\acs
set OBJ=.\pk3\acs

echo Compiling Weeaboo

acc %SRC%\weeaboo.c %OBJ%\weeaboo.o

echo Done!

pause >nul
