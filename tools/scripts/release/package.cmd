@echo off
del /Q *.exe
echo ******** GENERATING BUILDER
call build.cmd externals vs2008 release jenkins
call build.cmd coffee_engine vs2008 release jenkins
call build.cmd builder vs2008 release jenkins
echo ******** MOVE COFFEE BUILDER FILES
mkdir tools\builder\
copy /Y binaries\win32-vs2008-release\coffee_engine.dll tools\builder\
copy /Y binaries\win32-vs2008-release\builder.exe tools\builder\
echo ******** CLEAN BUILD FILES
call build.cmd clean vs2008 jenkins
call build.cmd clean builder vs2008 jenkins
cd tools
cd scripts
cd release
del /Q *.exe
echo ******** GENERATING INSTALLER
call generate_licence.cmd %1.%2
"c:\Program Files (x86)\NSIS\makensis.exe" coffee.nsi
copy /Y coffee.exe ..\..\..\coffee-%1.%2.exe
cd ..
cd ..
cd ..
echo Done.