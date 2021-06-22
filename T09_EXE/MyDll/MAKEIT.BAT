@echo off

if exist mk5lib.obj del mk5lib.obj
if exist mk5lib.dll del mk5lib.dll

C:\masm32\bin\ml /c /coff mk5lib.asm

C:\masm32\bin\Link /SUBSYSTEM:WINDOWS /DLL /DEF:mk5lib.def mk5lib.obj

dir mk5lib.*

pause