@echo off
title п╤ть
mode con cols=40 lines=10&color 3F
set /p uninstalldir=<"%temp%\LzzCompressionEncryption\uninstalldir.lce"
del /f /s /q "%temp%\LzzCompressionEncryption\uninstalldir.lce" 1>NUL 2>NUL
del /f /s /q "%uninstalldir%LzzCompressionEncryption.exe" 1>NUL 2>NUL
del /f /s /q "%uninstalldir%Uninstall.exe" 1>NUL 2>NUL
rd /s /q "%uninstalldir%" 1>NUL 2>NUL
echo.
echo 	п╤тьмЙЁиё║
echo.
pause
exit
