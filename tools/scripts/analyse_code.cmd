@echo off
cd ..
cd ..
echo ======================= CHECKING ENGINE =========================
set CHECK=..\..\tools\cppcheck\cppcheck.exe --enable=all --suppress=unusedFunction --template vs
set MINI_CHECK=tools\cppcheck\cppcheck.exe --enable=all --suppress=unusedFunction --template vs
cd engine
cd source
%CHECK% coffee.h
cd ..
cd ..
%MINI_CHECK% engine\source\coffee.cpp
%MINI_CHECK% engine\source\coffee_debug.h
%MINI_CHECK% engine\source\coffee_includes.h
%MINI_CHECK% engine\source\coffee_modules.hpp
%MINI_CHECK% engine\source\kernel\
%MINI_CHECK% engine\source\system\
%MINI_CHECK% engine\source\wide\
echo ======================= CHECKING EDITOR =========================
cd editor
cd source
%CHECK% coffee_editor.h
cd ..
cd ..
%MINI_CHECK% editor\source\coffee_editor.cpp
%MINI_CHECK% editor\source\coffee_editor_includes.h
%MINI_CHECK% editor\source\asset\
%MINI_CHECK% editor\source\component\
%MINI_CHECK% editor\source\config\
%MINI_CHECK% editor\source\document\
%MINI_CHECK% editor\source\project\
%MINI_CHECK% editor\source\widget\
echo ======================= CHECKING PLAYER =========================
cd player
cd source
%CHECK% coffee_player.h
%CHECK% coffee_player_includes.h
%CHECK% coffee_player.cpp
cd ..
cd ..
cd tools
cd scripts
echo Done.
