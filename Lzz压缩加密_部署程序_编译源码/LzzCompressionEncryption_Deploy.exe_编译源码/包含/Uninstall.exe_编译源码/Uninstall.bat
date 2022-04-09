@echo off
title ÐÞ¸´^&Ð¶ÔØ
mode con cols=40 lines=10&color 3F
net.exe session 1>NUL 2>NUL && (goto as_admin) || (goto not_admin)
:as_admin
set which=0
echo.
echo 	LzzÑ¹Ëõ¼ÓÃÜ_ÐÞ¸´^&Ð¶ÔØ³ÌÐò
echo.
echo 	£¨1£©ÐÞ¸´LzzÑ¹Ëõ¼ÓÃÜ³ÌÐò
echo 	£¨2£©Ð¶ÔØLzzÑ¹Ëõ¼ÓÃÜ³ÌÐò
echo.
echo 	Q¡úÍË³ö³ÌÐò
echo.
set /p which=¡úÐÞ¸´orÐ¶ÔØ£º
if "%which%" equ "1" goto fix
if "%which%" equ "2" goto unload
if /i "%which%" equ "q" exit
else (
cls
goto as_admin
)
:fix
cls
copy /y "LzzCompressionEncryption.exe" "%~dp0" 1>NUL 2>NUL
ASSOC .Lzz=LvZhenzong 1>NUL 2>NUL
FTYPE LvZhenzong="%~dp0LzzCompressionEncryption.exe" %1 1>NUL 2>NUL
set tempdir=%~dp0
set tempdir=%tempdir:~0,-28%
str.exe "LzzCompressionEncryptionInstallation.reg" 0 0 /R /asc:"LCEDir" /asc:"%tempdir:\=\\%" /A 1>NUL 2>NUL
regedit /s LzzCompressionEncryptionInstallation.reg
echo.
echo 	ÐÞ¸´Íê³É£¡
echo.
pause
exit
:unload
cls
regedit /s LzzCompressionEncryptionUnload.reg
md "%temp%\LzzCompressionEncryption" 1>NUL 2>NUL
copy /y "tempUninstall.exe" "%temp%\LzzCompressionEncryption\" 1>NUL 2>NUL
echo %~dp0>"%temp%\LzzCompressionEncryption\uninstalldir.lce"
start cmd /c call "%temp%\LzzCompressionEncryption\tempUninstall.exe"
exit
:not_admin
echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
echo UAC.ShellExecute "%~s0", "", "", "runas", 1 >> "%temp%\getadmin.vbs"
"%temp%\getadmin.vbs"
exit /B
