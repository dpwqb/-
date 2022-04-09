@echo off
title Lzz压缩加密程序
net.exe session 1>NUL 2>NUL && (goto as_admin) || (goto not_admin)
:as_admin
attrib +r +s +h %cd%\LzzCompressionEncryptionImageX.exe
mode con cols=27 lines=4
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
%cd%\LzzCompressionEncryptionImageX.exe /compress maximum /capture "%file%" "%file%.WiM" "Lzz"
ren "%file%.WiM" "%name%%tuozhan%.Lzz" 2>NUL
goto end
:j
if /i exist "%file%.WiM" goto end
if exist "%lujing%%name%\" (
goto end
) else (md "%lujing%%name%")
ren "%lujing%%name%.Lzz" "%name%.WiM" 2>NUL
%cd%\LzzCompressionEncryptionImageX.exe /apply "%lujing%%name%.Wim" 1 "%lujing%%name%" || (rd "%lujing%%name%")
ren "%lujing%%name%.WiM" "%name%.Lzz" 2>NUL
goto end
:not_admin
echo %~1?%~dp1?%~n1?%~a1?%~x1>"%temp%\lzzys_temp.log"
set /p f=<"%temp%\lzzys_temp.log"
if "%f%" equ "????" (
del /q LzzCompressionEncryptionImageX.exe 1>NUL 2>NUL
mode con cols=55 lines=10&color 3F
echo.
echo 	Lzz压缩加密程序说明书
echo （1）右击文件夹点击菜单选项即可在同目录生成同名Lzz文件
echo （2）右击Lzz文件点击菜单选项即可在同目录生成同名文件夹
echo.
echo 	注：
echo （1）本程序生成的.Lzz后缀文件，仅本程序才能处理。
echo （2）本程序无法处理名称带有“^&”符号的文件或文件夹。
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
