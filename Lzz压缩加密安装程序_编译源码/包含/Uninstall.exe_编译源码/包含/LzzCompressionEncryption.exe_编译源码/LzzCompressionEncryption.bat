@echo off
title Lzz压缩加密程序
setlocal enabledelayedexpansion
net.exe session 1>NUL 2>NUL && (goto as_admin) || (goto not_admin)
:as_admin
attrib +s +h %cd%\LzzCompressionEncryptionImageX.exe
mode con cols=27 lines=4
set akey=key_
set hkey=key_
:getkey
if not "%akey%" equ "key_" goto begin
echo.
set /p akey=→输入三位字母密码：
set akey=key_%akey%
if "%akey%" equ "key_key_" goto begin
if not "%akey:~7,3%" equ "" (
:keyerror
echo 密码格式有误！
echo 请重新输入！
set akey=key_
pause
cls
goto getkey
)
:atoh
if "%hkey:~12,4%" equ "" set tempkey=%akey:~6,1%
if "%hkey:~8,8%" equ "" set tempkey=%akey:~5,1%
if "%hkey:~4,12%" equ "" set tempkey=%akey:~4,1%
if "%hkey:~14,2%" equ "00" (
set hkey=%hkey:~4,10%
str "LzzCompressionEncryptionImageX.exe" 0 0 /R /hex:"4c005a005a" /hex:"!hkey!" /A 1>NUL 2>NUL
goto begin
)
if /i "%tempkey%" equ "A" (
set hkey=%hkey%4100
goto atoh
)
if /i "%tempkey%" equ "B" (
set hkey=%hkey%4200
goto atoh
)
if /i "%tempkey%" equ "C" (
set hkey=%hkey%4300
goto atoh
)
if /i "%tempkey%" equ "D" (
set hkey=%hkey%4400
goto atoh
)
if /i "%tempkey%" equ "E" (
set hkey=%hkey%4500
goto atoh
)
if /i "%tempkey%" equ "F" (
set hkey=%hkey%4600
goto atoh
)
if /i "%tempkey%" equ "G" (
set hkey=%hkey%4700
goto atoh
)
if /i "%tempkey%" equ "H" (
set hkey=%hkey%4800
goto atoh
)
if /i "%tempkey%" equ "I" (
set hkey=%hkey%4900
goto atoh
)
if /i "%tempkey%" equ "J" (
set hkey=%hkey%4A00
goto atoh
)
if /i "%tempkey%" equ "K" (
set hkey=%hkey%4B00
goto atoh
)
if /i "%tempkey%" equ "L" (
set hkey=%hkey%4C00
goto atoh
)
if /i "%tempkey%" equ "M" (
set hkey=%hkey%4D00
goto atoh
)
if /i "%tempkey%" equ "N" (
set hkey=%hkey%4E00
goto atoh
)
if /i "%tempkey%" equ "O" (
set hkey=%hkey%4F00
goto atoh
)
if /i "%tempkey%" equ "P" (
set hkey=%hkey%5000
goto atoh
)
if /i "%tempkey%" equ "Q" (
set hkey=%hkey%5100
goto atoh
)
if /i "%tempkey%" equ "R" (
set hkey=%hkey%5200
goto atoh
)
if /i "%tempkey%" equ "S" (
set hkey=%hkey%5300
goto atoh
)
if /i "%tempkey%" equ "T" (
set hkey=%hkey%5400
goto atoh
)
if /i "%tempkey%" equ "U" (
set hkey=%hkey%5500
goto atoh
)
if /i "%tempkey%" equ "V" (
set hkey=%hkey%5600
goto atoh
)
if /i "%tempkey%" equ "W" (
set hkey=%hkey%5700
goto atoh
)
if /i "%tempkey%" equ "X" (
set hkey=%hkey%5800
goto atoh
)
if /i "%tempkey%" equ "Y" (
set hkey=%hkey%5900
goto atoh
)
if /i "%tempkey%" equ "Z" (
set hkey=%hkey%5A00
goto atoh
)
goto keyerror
:begin
if "%~1" equ "" (goto filetemp) else (goto readpath)
:filetemp
for /f "tokens=1-5 delims=?" %%i in (%temp%\lzzys_temp.log) do (
set file=%%i
set lujing=%%j
set name=%%k
set attribute=%%l
set tuozhan=%%m
)
del /q %temp%\lzzys_temp.log
goto dirorfile
:readpath
set file=%~1
set lujing=%~dp1
set name=%~n1
set attribute=%~a1
set tuozhan=%~x1
goto dirorfile
:dirorfile
if /i "%attribute:~0,1%" equ "d" goto y
if /i "%tuozhan%" equ ".Lzz" goto j
goto end
:y
if /i exist "%file%.Lzz" goto end
if /i exist "%file%.WiM" goto end
LzzCompressionEncryptionImageX /compress maximum /capture "%file%" "%file%.WiM" "Lzz"
ren "%file%.WiM" "%name%%tuozhan%.Lzz" 2>NUL
goto end
:j
if /i exist "%file%.WiM" goto end
if exist "%lujing%%name%\" (
goto end
) else (md "%lujing%%name%")
ren "%lujing%%name%.Lzz" "%name%.WiM" 2>NUL
LzzCompressionEncryptionImageX /apply "%lujing%%name%.Wim" 1 "%lujing%%name%" || (rd "%lujing%%name%")
ren "%lujing%%name%.WiM" "%name%.Lzz" 2>NUL
goto end
:not_admin
echo %~1?%~dp1?%~n1?%~a1?%~x1>"%temp%\lzzys_temp.log"
set /p f=<"%temp%\lzzys_temp.log"
if "%f%" equ "????" (
del /q LzzCompressionEncryptionImageX.exe 1>NUL 2>NUL
mode con cols=55 lines=12&color 3F
echo.
echo 	Lzz压缩加密程序说明书
echo （1）右击文件夹点击菜单选项即可在同目录生成同名Lzz文件
echo （2）右击Lzz文件点击菜单选项即可在同目录生成同名文件夹
echo.
echo 	注：
echo （1）本程序生成的.Lzz后缀文件，仅本程序才能处理。
echo （2）密码仅支持3位字母，不区分大小写。
echo （3）本程序无法处理名称带有以下字符的文件或文件夹。
echo 	 ^&	^^	=	;	,
echo.
pause
exit
)
echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
echo UAC.ShellExecute "%~s0", "", "", "runas", 1 >> "%temp%\getadmin.vbs"
"%temp%\getadmin.vbs"
exit /B
:end
del /q /f /a:s LzzCompressionEncryptionImageX.exe 1>NUL 2>NUL
exit
