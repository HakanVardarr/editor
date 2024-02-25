@echo off

MSBuild.exe .\build\Terminal.sln /verbosity:q 
.\build\Debug\Terminal.exe