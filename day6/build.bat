@echo off
mkdir build

pushd build
cl /nologo /std:c++20 /EHsc /Zi ..\main.cpp
popd
