@echo off
title Lzz压缩程序
net.exe session 1>NUL 2>NUL && (goto as_admin) || (goto not_admin)
:as_admin
mode con cols=60 lines=7
if "%~1" equ "" (goto filetemp) else (goto readpath)
:filetemp
for /f "tokens=1-5 delims=?" %%i in (%temp%\lzzys_temp.log) do (
set file=%%i
set lujing=%%j
set name=%%k
set attribute=%%l
set tuozhan=%%m
)
del /q "%temp%\lzzys_temp.log"
goto dirorfile
:readpath
set file=%~1
set lujing=%~dp1
set name=%~n1
set attribute=%~a1
set tuozhan=%~x1
goto dirorfile
:dirorfile
cd /d c:\
if /i "%attribute:~0,1%" equ "d" goto y
if /i "%tuozhan%" equ ".Lzz" goto j
exit
:y
if /i exist "%file%.Lzz" exit
if /i exist "%file%.EsD" exit
Dism /Capture-Image /ImageFile:"%file%.EsD" /CaptureDir:"%file%" /Name:Lzz /Description:盗版必究 /Compress:max
ren "%file%.EsD" "%name%%tuozhan%.Lzz" 2>NUL
exit
:j
if /i exist "%file%.EsD" exit
if exist "%lujing%%name%\" (
exit
) else (md "%lujing%%name%")
ren "%lujing%%name%.Lzz" "%name%.EsD" 2>NUL
Dism /Apply-Image /ImageFile:"%lujing%%name%.EsD" /Index:1 /ApplyDir:"%lujing%%name%" || (rd "%lujing%%name%")
ren "%lujing%%name%.EsD" "%name%.Lzz" 2>NUL
exit
:not_admin
echo %~1?%~dp1?%~n1?%~a1?%~x1>"%temp%\lzzys_temp.log"
set /p f=<"%temp%\lzzys_temp.log"
if "%f%" equ "????" (
mode con cols=75 lines=10&color 3F
echo.
echo 	Lzz压缩程序说明书
echo （1）将要压缩的文件夹拖拽到本程序上即可在同目录生成同名文件（.Lzz拓展名）
echo （2）将要解压的文件（.Lzz拓展名）拖拽到本程序上即可在同目录生成同名文件夹
echo.
echo 	注：
echo （1）若压缩的文件夹过大，本程序会消耗大量的时间以及性能！
echo （2）本程序无法处理名称带有“^&”符号的文件或文件夹。
echo.
pause
exit
)
echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
echo UAC.ShellExecute "%~s0", "", "", "runas", 1 >> "%temp%\getadmin.vbs"
"%temp%\getadmin.vbs"
exit /B
