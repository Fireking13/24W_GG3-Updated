mkdir build
cd build
"C:\Program Files\CMake\bin\cmake" ..
rem Build a second time to fix PCH folder
"C:\Program Files\CMake\bin\cmake" ..
pause
cd..
call BuildShaders.bat
exit
