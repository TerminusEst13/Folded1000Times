@echo off

set PATH=C:\Program Files\7-Zip
set PK3NAME=te13-DemonSteele

cd pk3

echo Building PK3
7z a -tzip ..\%PK3NAME%.pk3 *.* *

rem echo Building PK7
rem 7z a -t7z ..\%PK3NAME%.pk7 *.* *

pause >nul
