
REM must call this bat first to set razzle env
call "C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\vcvarsall.bat"

REM compiler flags must not have -WX ar -W3
REM /EHsc must be added to end
REM Based on Casey Muratori's Handmade Hero build file 
set CommonCompilerFlags=-O2 -MTd -nologo -fp:fast -fp:except- -Gm- -GR- -EHa- -Zo -Oi -W3 -wd4201 -wd4100 -wd4189 -wd4505 -wd4127 -FC -Z7 /EHsc

REM call with flags, errors to text file
cl.exe %CommonCompilerFlags% callex.cpp > compiler_err.txt 2>&1


REM see source code nots in CPP file
