@echo off

for /f %%i in ('git rev-list --count head') do set version=%%i

DEL ..\\src\\game\\version.hpp
echo #define VERSION %version% >> ..\\src\\game\\version.hpp

echo Version is %version%.