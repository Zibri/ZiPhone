@echo off 
echo "Building ZiPhone Windows CLI ..."
cd ..\
mkdir ZiPhone
cd ZiPhone
mkdir ZiPhone
cd ..\ziphone-win-mac-os-x-cli
xcopy ziphone.exe ..\ZiPhone\ZiPhone\ziphone.exe*
xcopy QTMLClient.dll ..\ZiPhone\ZiPhone\QTMLClient.dll*
xcopy iTunesMobileDevice.dll ..\ZiPhone\ZiPhone\iTunesMobileDevice.dll*
xcopy "ENTER DFU MODE.bat" "..\ZiPhone\ZiPhone\ENTER DFU MODE.bat"*
xcopy "FULL AUTOMATIC.bat" "..\ZiPhone\ZiPhone\FULL AUTOMATIC.bat"*
del ziphone.o
del md5.o
del ziphone.exe
cd ..\
xcopy dfu.dat ZiPhone\ZiPhone\dfu.dat*
xcopy victor.dat ZiPhone\ZiPhone\victor.dat*
xcopy igor.dat ZiPhone\ZiPhone\igor.dat*
xcopy zibri.dat ZiPhone\ZiPhone\zibri.dat*
xcopy docs ZiPhone\docs\
echo "Built in directory ../ZiPhone"