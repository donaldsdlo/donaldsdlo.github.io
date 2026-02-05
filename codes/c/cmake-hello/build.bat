@echo off
REM Windows build script for CMake project

echo Building CMake Hello World Project...

REM Create build directory
if not exist build mkdir build
cd build

REM Configure with CMake
echo Configuring with CMake...
cmake -G "MinGW Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..

if %ERRORLEVEL% NEQ 0 (
    echo CMake configuration failed!
    exit /b 1
)

REM Build the project
echo Building project...
cmake --build .

if %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    exit /b 1
)

REM Copy compile_commands.json to project root for language servers
copy compile_commands.json ..\compile_commands.json

echo.
echo Build successful! Executable: build/bin/cmake_hello.exe
echo compile_commands.json generated for language server support.

cd ..
