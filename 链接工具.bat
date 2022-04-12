@echo off
title 链接工具
cd /d %~dp0
net.exe session 1>NUL 2>NUL && (goto as_admin) || (goto not_admin)
:as_admin
mode con cols=64 lines=5&color 3F
setlocal enabledelayedexpansion
for /f "tokens=1,2 delims=?" %%i in (%temp%\linkbat_temp.log) do (
set linkpath=%%i
set attribute=%%j
)
if /i "%attribute:~0,1%" equ "d" (goto d) else (goto f)
:not_admin
mode con cols=50 lines=13
echo %~1?%~a1>"%temp%\linkbat_temp.log"
set /p f=<"%temp%\linkbat_temp.log"
if "%f%" equ "?" (
echo.
echo 	链接工具说明书
echo （1）将本程序改名为要创建的新链接的名称
echo （2）将本程序放入要创建的新链接所在的目录
echo （3）将新链接所引用的目录或文件拖拽到本程序
echo （4）即可选择链接方式并为目录或文件创建新链接
echo.
echo 	注：
echo （1）跨盘符为文件创建链接时，自动创建符号链接。
echo （2）为SMB文件或目录创建链接时，自动创建符号链接。
echo.
pause
exit
)
echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
echo UAC.ShellExecute "%~s0", "", "", "runas", 1 >> "%temp%\getadmin.vbs"
"%temp%\getadmin.vbs"
exit /B
:d
if /i "%linkpath:~0,2%" equ "\\" (
set way=d
) else (
echo.
echo 	在本程序目录下，为文件夹创建符号链接请输入：D
echo 	在本程序目录下，为文件夹创建目录链接请输入：J
echo.
set /p way=请输入（d/j）：
)
if /i "%way%" equ "d" (mklink /d "%~dpn0" "%linkpath%" 1>NUL 2>NUL)
if /i "%way%" equ "j" (mklink /j "%~dpn0" "%linkpath%" 1>NUL 2>NUL)
exit
:f
if /i "%linkpath:~0,2%" equ "\\" (goto w)
if /i "%linkpath:~0,2%" equ "%~d0" (
echo.
echo 	在本程序目录下，为文件创建符号链接请输入：D
echo 	在本程序目录下，为文件创建硬链接请输入：H
echo.
set /p way=请输入（d/h）：
goto fhd
) else (
:w
set way=d
goto fd
)
:fhd
if /i "%way%" equ "h" (mklink /h "%~dpn0" "%linkpath%" 1>NUL 2>NUL)
:fd
if /i "%way%" equ "d" (mklink "%~dpn0" "%linkpath%" 1>NUL 2>NUL)
exit
