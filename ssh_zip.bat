@echo off
color F

set NAME=te13-DemonSteele-ssh
set /p TYPE="Would you like to build a pk3 or pk7? (default pk3): " % = %

cd ssh

if (%TYPE%) == (pk7) (goto PK7) else (goto PK3)

:PK7
echo Building PK7
..\tools\7za a -t7z ..\%NAME%.pk7 *.* *
goto Done

:PK3
echo Building PK3
..\tools\7za a -tzip ..\%NAME%.pk3 *.* *
goto Done

:Done
pause >nul
