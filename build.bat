@echo off
setlocal EnableExtensions DisableDelayedExpansion
pushd "%~dp0"
if errorlevel 1 exit /b 1

set "RESULT=1"
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if not exist "%VSWHERE%" goto missing_vs
set "VS_DIR="
for /f "usebackq delims=" %%I in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do set "VS_DIR=%%I"
if not defined VS_DIR goto missing_vs

set "CMAKE_EXE=%VS_DIR%\Common7\IDE\CommonExtensions\Microsoft\CMake\CMake\bin\cmake.exe"
if exist "%CMAKE_EXE%" goto tools_ready
set "CMAKE_EXE="
for /f "delims=" %%I in ('where cmake.exe 2^>nul') do if not defined CMAKE_EXE set "CMAKE_EXE=%%I"
if not defined CMAKE_EXE goto missing_cmake

:tools_ready
set "VS_VERSION="
set "VS_YEAR="
for /f "usebackq delims=" %%I in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationVersion`) do set "VS_VERSION=%%I"
for /f "tokens=1 delims=." %%I in ("%VS_VERSION%") do set "VS_MAJOR=%%I"
if "%VS_MAJOR%"=="17" set "VS_YEAR=2022"
if "%VS_MAJOR%"=="18" set "VS_YEAR=2026"
if not defined VS_YEAR goto missing_vs

echo Configuring the project...
"%CMAKE_EXE%" -S . -B build -G "Visual Studio %VS_MAJOR% %VS_YEAR%" -A x64 "-DCMAKE_GENERATOR_INSTANCE=%VS_DIR%"
if errorlevel 1 goto build_failed
echo Building all labs into one executable...
"%CMAKE_EXE%" --build build --config Release
if errorlevel 1 goto build_failed
if not exist "build\Release\oop_labs.exe" goto build_failed
copy /Y "build\Release\oop_labs.exe" "oop_labs.exe" >nul
if errorlevel 1 goto copy_failed
echo.
echo Build completed successfully.
echo Executable: "%CD%\oop_labs.exe"
set "RESULT=0"
goto finish

:missing_vs
echo ERROR: Visual Studio C++ build tools were not found.
echo Install Visual Studio 2022 or newer, or Build Tools,
echo with Desktop development with C++ and Windows SDK.
goto finish

:missing_cmake
echo ERROR: CMake was not found.
echo Install C++ CMake tools for Windows in Visual Studio Installer.
goto finish

:build_failed
echo.
echo ERROR: Build failed. See the messages above.
echo If build was created with another generator, rename the build folder and retry.
goto finish

:copy_failed
echo.
echo ERROR: Could not copy oop_labs.exe to the project folder.
echo Close the running oop_labs.exe and try again.

:finish
echo.
if /i not "%~1"=="--no-pause" pause
popd
exit /b %RESULT%
