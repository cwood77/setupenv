@echo off

if "%1" == "1" goto part1
if "%1" == "2" goto part2

echo indicate 1 or 2 for which part

:part1
mkdir bin\pack\setupenv-1-win64-rel
copy bin\out\release\setupenv.exe bin\pack\setupenv-1-win64-rel\.
goto end

:part2
mkdir C:\ProgramData\cdwe\gordian\freewebstore\packages
mkdir C:\ProgramData\cdwe\gordian\freewebstore\cat\m
echo # vi: ft=json>C:\ProgramData\cdwe\gordian\freewebstore\cat\m\setupenv-1-win64-rel.sst
echo {>>C:\ProgramData\cdwe\gordian\freewebstore\cat\m\setupenv-1-win64-rel.sst
echo    "name": "setupenv",>>C:\ProgramData\cdwe\gordian\freewebstore\cat\m\setupenv-1-win64-rel.sst
echo    "version": 1,>>C:\ProgramData\cdwe\gordian\freewebstore\cat\m\setupenv-1-win64-rel.sst
echo }>>C:\ProgramData\cdwe\gordian\freewebstore\cat\m\setupenv-1-win64-rel.sst

copy bin\pack\setupenv-1-win64-rel.ar.z.s C:\ProgramData\cdwe\gordian\freewebstore\packages\.
:end
