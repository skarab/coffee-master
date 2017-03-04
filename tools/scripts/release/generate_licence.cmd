@echo off
echo ******** GENERATING LICENCE
echo Coffee, build %1  > coffee_license.txt
for /f "delims=ù" %%a in (..\..\..\LICENSE) do (
echo %%a >> coffee_license.txt
)


