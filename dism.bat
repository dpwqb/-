@echo off
net.exe session 1>NUL 2>NUL && (goto as_admin) || (goto not_admin)
:as_admin
setlocal enabledelayedexpansion
if "%~1" equ "" (goto filetemp) else (goto readpath)
:filetemp
for /f "tokens=1-5 delims=?" %%i in (%temp%\dism_temp.log) do (
set filepath=%%i
set lujing=%%j
set filename=%%k
set attribute=%%l
set tuozhan=%%m
)
del /q "%temp%\dism_temp.log"
goto dirorfile
:readpath
set filepath=%~1
set lujing=%~dp1
set filename=%~n1
set attribute=%~a1
set tuozhan=%~x1
goto dirorfile
:dirorfile
cd /d c:\
if /i "%attribute:~0,1%" equ "d" goto file
if /i "%tuozhan%" equ ".wim" goto image
if /i "%tuozhan%" equ ".esd" goto image
else
goto end
:not_admin
echo %~1?%~dp1?%~n1?%~a1?%~x1>"%temp%\dism_temp.log"
set /p f=<"%temp%\dism_temp.log"
if "%f%" equ "????" (
mode con cols=78 lines=10&color 3F
echo.
echo 	Dism工具说明书
echo （1）将.wim.esd后缀映像文件或待处理的文件夹拖拽至本程序上
echo （2）根据功能键入序号并回车，键入q并回车即退出程序
echo.
echo 	注：
echo （1）提取过大的映像到recovery压缩级别的.esd映像文件会消耗大量的时间以及性能！
echo （2）本程序无法处理名称带有“^&”符号的文件或文件夹。
echo.
pause
exit
)
echo Set UAC = CreateObject^("Shell.Application"^) > "%temp%\getadmin.vbs"
echo UAC.ShellExecute "%~s0", "", "", "runas", 1 >> "%temp%\getadmin.vbs"
"%temp%\getadmin.vbs"
exit /B
:file
set which=0
echo （1）卸载此文件夹到映像文件
echo （2）打包此文件夹到映像文件
echo.
echo q→回车，退出程序
echo.
set /p which=对%filename%文件夹执行什么操作：
if "%which%" equ "1" goto unmount
if "%which%" equ "2" goto capture
if /i "%which%" equ "q" goto end
else (
cls
goto file
)
:unmount
echo commit→保留更改并卸载
echo discard→不保留更改直接卸载
set /p save=是否保留更改:
Dism /Unmount-Wim /Mountdir:%filepath% /%save% || (goto unmountUnsuccessful)
set save=
rd %filepath%
pause
exit
:unmountUnsuccessful
set save=
pause
cls
goto file
:capture
set /p name=打包后映像文件里的映像的名称：
set /p description=打包后映像文件里的映像的描述：
echo none→不压缩直接存储
echo fast→简单压缩后存储
echo max→最佳压缩后存储
set /p compress=打包的映像文件的压缩方式：
if /i exist "%filepath%_%compress%.wim" (
echo 与%filename%%tuozhan%_%compress%.wim映像文件同名，程序已终止。
) else (
Dism /Capture-Image /ImageFile:%filepath%_%compress%.wim /CaptureDir:%filepath% /Name:%name% /Description:%description% /Compress:%compress%
)
set name=
set description=
set compress=
pause
cls
goto file
:image
set which=0
echo （1）查看此映像文件基本信息
echo （2）从此映像文件中提取映像到其他映像文件
echo （3）将此映像部署
if /i "%tuozhan%" equ ".wim" (echo （4）将此映像挂载)
echo.
echo q→回车，退出程序
echo.
set /p which=对%filename%%tuozhan%映像文件执行什么操作：
if "%which%" equ "1" goto information
if "%which%" equ "2" goto export
if "%which%" equ "3" goto apply
if /i "%tuozhan%" equ ".wim" (if "%which%" equ "4" goto mount)
if /i "%which%" equ "q" goto end
else (
cls
goto image
)
:information
Dism /Get-Wiminfo /Wimfile:%filepath%
pause
cls
goto image
:export
set /p sourceIndex=提取的映像的索引号：
set /p tofilename=提取到的其他映像文件的文件名（加上.wim或.sed后缀）：
set /p name=保存到其他映像文件里的映像的名称：
if not "%name%" equ "" (set name= /DestinationName:"!name!")
if not exist %lujing%%tofilename% (
echo none→不压缩直接存储
echo fast→简单压缩后存储
echo max→最佳压缩后存储
echo recovery→究极压缩后存储（后缀应为.esd）
set /p compress=提取到的其他映像文件的压缩方式：
set compress= /Compress:!compress!
)
Dism /Export-Image /SourceImageFile:%filepath% /SourceIndex:%sourceIndex% /DestinationImageFile:%lujing%%tofilename%%name%%compress%
set sourceIndex=
set tofilename=
set name=
set compress=
pause
cls
goto image
:mount
if not exist "%lujing%挂载%filename%\" (
md "%lujing%挂载%filename%"
) else (
echo 有同名文件夹"挂载%filename%"，程序已终止。
goto mountend
)
set /p sourceIndex=挂载的映像的索引号：
Dism /Mount-Wim /Wimfile:%filepath% /Index:%sourceIndex% /Mountdir:%lujing%挂载%filename% || (rd "%lujing%挂载%filename%")
set sourceIndex=
:mountend
pause
cls
goto image
:apply
if not exist "%lujing%部署%filename%\" (
md "%lujing%部署%filename%"
) else (
echo 有同名文件夹"部署%filename%"，程序已终止。
goto applyend
)
set /p sourceIndex=部署的映像的索引号：
Dism /Apply-Image /ImageFile:%filepath% /Index:%sourceIndex% /ApplyDir:%lujing%部署%filename% || (rd "%lujing%部署%filename%")
set sourceIndex=
:applyend
pause
cls
goto image
:end
