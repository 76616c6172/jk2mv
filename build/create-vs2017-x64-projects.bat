@REM Create JK2MV projects for Visual Studio 2017 using CMake
@echo off
for %%X in (cmake.exe) do (set FOUND=%%~$PATH:X)
if not defined FOUND (
	echo CMake was not found on your system. Please make sure you have installed CMake
	echo from http://www.cmake.org/ and cmake.exe is installed to your system's PATH
	echo environment variable.
	echo.
	pause
	exit /b 1
) else (
	echo Found CMake!
)
mkdir msvc15_x64
cd msvc15_x64
cmake -G "Visual Studio 15 Win64" ../..
pause