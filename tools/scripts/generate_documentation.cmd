@echo off
cd ..
cd ..
echo ======================= GENERATING DOCUMENTATION =========================
tools\doxys\doxys.exe tools\doxys\coffee.doxyfile
cd tools
cd scripts
echo Done.
