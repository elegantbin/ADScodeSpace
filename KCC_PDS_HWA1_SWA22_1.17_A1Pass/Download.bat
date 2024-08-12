echo off
set FileName=KCC_PDS_HWA1_SW0x
set Elf2HexCmd="C:\NXP\S32DS_ARM_v2.2\S32DS\build_tools\gcc_v4.9\gcc-arm-none-eabi-4_9\bin\arm-none-eabi-objcopy.exe"
set JlinkDownloadCmd="C:\Program Files (x86)\SEGGER\JLink\JLink.exe"
set JlinkDownloadCfg=".\s32k142.txt"


cd .\Debug_FLASH
make -j4  all

cd ..\
if exist %FileName%.hex (del/q %FileName%.hex)

::  pause

echo Creating %FileName%.hex ...

%Elf2HexCmd% -O ihex .\Debug_FLASH\%FileName%.elf %FileName%.hex

if not exist %FileName%.hex (goto exit)
echo Created %FileName%.hex file successful!

%JlinkDownloadCmd% %JlinkDownloadCfg%

:exit

 pause 