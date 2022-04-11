@echo off
title Lzz压缩加密安装程序
mode con cols=50 lines=10&color 3F
net.exe session 1>NUL 2>NUL && (goto as_admin) || (goto not_admin)
:not_admin
echo.
echo 	键入安装路径（无输入即安装至默认目录）：
set /p installdir=	或拖拽安装目录到此处→
if "%installdir%" equ "" goto up
if "%installdir:~-2%" equ ":\" set installdir=%installdir:~-0,2%
if not exist "%installdir%\" (
echo.
echo 	无效的目录！
echo 	请重新键入！
echo.
set installdir=
pause
cls
goto not_admin
) else (
echo %installdir%>"%temp%\installdir.lce"
)
:up
echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
echo UAC.ShellExecute "%~s0", "", "", "runas", 1 >> "%temp%\getadmin.vbs"
"%temp%\getadmin.vbs"
exit /B
:as_admin
if exist "%temp%\installdir.lce" (
set /p installdir=<"%temp%\installdir.lce"
del /q "%temp%\installdir.lce"
) else (
echo.
echo 	将自动安装至默认目录！
echo.
pause
set installdir=%ProgramFiles%
)
md "%installdir%\Lzz Compression Encryption\" 1>NUL 2>NUL
copy /y "LzzCompressionEncryption.exe" "%installdir%\Lzz Compression Encryption\" 1>NUL 2>NUL
copy /y "Uninstall.exe" "%installdir%\Lzz Compression Encryption\" 1>NUL 2>NUL
ASSOC .Lzz=LvZhenzong 1>NUL 2>NUL
FTYPE LvZhenzong="%installdir%\Lzz Compression Encryption\LzzCompressionEncryption.exe" %1 1>NUL 2>NUL
str "LzzCompressionEncryptionInstallation.reg" 0 0 /R /asc:"LCEDir" /asc:"%installdir:\=\\%" /A
regedit /s LzzCompressionEncryptionInstallation.reg
exit
