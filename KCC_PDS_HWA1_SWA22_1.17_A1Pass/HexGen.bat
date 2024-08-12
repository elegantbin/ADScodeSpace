::echo off
set FileName= KCC_PDS_HWA1_SW0x 
set Elf2HexCmd="C:\NXP\S32DS_ARM_v2.2\S32DS\build_tools\gcc_v4.9\gcc-arm-none-eabi-4_9\bin\arm-none-eabi-objcopy.exe"

if exist %FileName%.hex (del/q %FileName%.hex)

::  pause

echo Creating %FileName%.hex ...
%Elf2HexCmd% -O ihex %FileName%.elf %FileName%.hex
if not exist %FileName%.hex (goto exit)

echo Created %FileName%.hex file successful!
:exit
pause