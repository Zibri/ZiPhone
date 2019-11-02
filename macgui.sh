#!/bin/sh

if [ -d "ziphone-3.6-cli-mac" ]; then
    echo "Found directory of ZiPhone Mac CLI"
else 
    echo "You need to build Mac CLI before the GUI!"
    exit 1
fi
cd "gui-mac"
rm -rf ZiPhoneOSX.app
rm -rf build 
rm -rf ConsoleResources
rm -rf Base.lproj
cp -r English.lproj Base.lproj
xcodebuild 
rm -rf ConsoleResources
rm -rf build
rm -rf Base.lproj
tar -xvf ZiPhoneOSX-3.6.tbz
rm ZiPhoneOSX-3.6.tbz
cp -r ZiPhoneOSX.app ../ZiPhoneOSX.app
rm -r ZiPhoneOSX.app
cd ../
cp ziphone-3.6-cli-mac/ziphone ZiPhoneOSX.app/Contents/Resources/ziphone
cp dfu.dat ZiPhoneOSX.app/Contents/Resources/dfu.dat
cp zibri.dat ZiPhoneOSX.app/Contents/Resources/zibri.dat
cp igor.dat ZiPhoneOSX.app/Contents/Resources/igor.dat
cp victor.dat ZiPhoneOSX.app/Contents/Resources/victor.dat
cp docs/readme.txt ZiPhoneOSX.app/Contents/Resources/readme.txt
cp docs/troubleshooting.txt ZiPhoneOSX.app/Contents/Resources/troubleshooting.txt