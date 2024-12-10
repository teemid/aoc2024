@echo off
mkdir build

pushd build
cl /nologo /std:c++20 /Zi /EHsc ..\main.cpp
popd
