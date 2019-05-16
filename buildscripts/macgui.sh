#!/bin/sh

echo "Building Mac OS X CLI..."
./maccli.sh
cd ../
echo "Preparing to build ZiPhone Mac OS X GUI..."
cp dfu.dat  ZiPhone/
cp zibri.dat ZiPhone/
cp igor.dat  ZiPhone/
cp victor.dat  ZiPhone/
cp -r docs ZiPhone/docs
cp -r "ziphone-win-mac-os-x-cli/" ZiPhone/
echo "Building ZiPhone Mac OS X GUI..."
cd "ziphone-mac-os-x-gui"
rm -rf build 
rm -rf ConsoleResources
rm -rf Base.lproj
cp -r English.lproj Base.lproj
xcodebuild 
rm -rf ConsoleResources
rm -rf build
rm -rf Base.lproj
tar -xvf ZiPhoneOSX-3.4.tbz
rm ZiPhoneOSX-3.4a.tbz
cp -r ZiPhoneOSX.app ../ZiPhoneOSX.app
rm -r ZiPhoneOSX.app
cd ../
cp ZiPhone/ziphone ZiPhoneOSX.app/Contents/Resources/ziphone
cp dfu.dat ZiPhoneOSX.app/Contents/Resources/dfu.dat
cp zibri.dat ZiPhoneOSX.app/Contents/Resources/zibri.dat
cp igor.dat ZiPhoneOSX.app/Contents/Resources/igor.dat
cp victor.dat ZiPhoneOSX.app/Contents/Resources/victor.dat
cp docs/readme.txt ZiPhoneOSX.app/Contents/Resources/readme.txt
cp docs/troubleshooting.txt ZiPhoneOSX.app/Contents/Resources/troubleshooting.txt
rm -rf ZiPhone
mkdir ZiPhone
mkdir ZiPhone/docs
cp docs/license.txt ZiPhone/docs/license.txt
cp docs/plugin-howto.txt ZiPhone/docs/plugin-howto.txt
cp docs/run.txt ZiPhone/docs/run.txt
cp docs/restore.txt ZiPhone/docs/restore.txt
cp -r ZiPhoneOSX.app ZiPhone/ZiPhoneOSX.app
rm -r ZiPhoneOSX.app
echo "Built in directory ../ZiPhone."
