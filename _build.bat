@ECHO OFF

VERIFY OTHER 2>nul
SETLOCAL ENABLEEXTENSIONS ENABLEDELAYEDEXPANSION
IF NOT ERRORLEVEL 0 (
  echo Unable to enable extensions
)

SET "zigBin=D:\zig\zig.exe"

FOR /F "delims=" %%A IN ('cd') DO SET "ORIGINAL_DIR=%%A"
ECHO orig dir: %ORIGINAL_DIR%

SET "logFolder=.\_build_logs"

GOTO :main

:doCommand
SET "logFile=%logFolder%\%~1.log"
SET "command=%~2"
ECHO %command%>"%ORIGINAL_DIR%\%logFile%" 2>&1
%command%>>"%ORIGINAL_DIR%\%logFile%" 2>&1
EXIT /B %ERRORLEVEL%

:main

RMDIR /S /Q "%ORIGINAL_DIR%\%logFolder%"
RMDIR /S /Q "%ORIGINAL_DIR%\out"

MKDIR "%ORIGINAL_DIR%\%logFolder%"
MKDIR "%ORIGINAL_DIR%\out"

CALL :doCommand "00_made_build_logs" "echo we did it" && cd>NUL || Goto :END

cd "%ORIGINAL_DIR%\out"

CALL :doCommand "01_build_for_linux" "%zigBin% c++ -o libCursedModNative_Linux.so -target x86_64-linux -fno-debug-macro -g0 -fno-standalone-debug -dynamic -shared -pthread -I D:/linux-libraries/usr/include/libmount -I D:/linux-libraries/usr/include/blkid -I D:/linux-libraries/usr/include/glib-2.0 -I D:/linux-libraries/usr/lib/x86_64-linux-gnu/glib-2.0/include -L D:/linux-libraries/bin -l gio-2.0 -l gobject-2.0 -l glib-2.0 -std=c++20 -stdlib=libc++ -Wall -Wextra -Xlinker -s -Xlinker -S ..\src\common.cpp ..\src\main.cpp ..\src\lin\main.cpp" && cd>NUL || Goto :END

CALL :doCommand "01_build_for_mac_os" "%zigBin% c++ -o libCursedModNative_MacOS.dylib -target x86_64-macos -fno-debug-macro -g0 -fno-standalone-debug -dynamic -shared -std=c++20 -stdlib=libc++ -Wall -Wextra -Xlinker -s -Xlinker -S ..\src\common.cpp ..\src\main.cpp ..\src\mac\main.cpp" && cd>NUL || Goto :END

CALL :doCommand "01_build_for_windows" "%zigBin% c++ -o CursedModNative_Windows.dll -target x86_64-windows -fno-debug-macro -g0 -fno-standalone-debug -dynamic -shared -l UxTheme -l Dwmapi -l User32 -std=c++20 -stdlib=libc++ -Wall -Wextra -Xlinker -s -Xlinker -S ..\src\common.cpp ..\src\main.cpp ..\src\win\main.cpp" && cd>NUL || Goto :END

ECHO success

:END
cd "%ORIGINAL_DIR%"
ENDLOCAL
EXIT /B %ERRORLEVEL%
