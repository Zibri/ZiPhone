#!/bin/sh

echo "Building ZiPhone Mac OS X CLI..."
cd ../
rm -rf ZiPhone
mkdir -p ZiPhone
cd ZiPhone
mkdir ZiPhone
cd ../
cd "ziphone-win-mac-os-x-cli"
rm -rf obj
make -f Makefile.osx
cp ziphone ../ZiPhone/ZiPhone/ziphone
make clean -f Makefile.osx
cp libMobileDevice742.dylib ../ZiPhone/ZiPhone/libMobileDevice742.dylib
cd ../
cp dfu.dat  ZiPhone/ZiPhone/
cp zibri.dat ZiPhone/ZiPhone/
cp igor.dat  ZiPhone/ZiPhone/
cp victor.dat  ZiPhone/ZiPhone/
cp -r docs ZiPhone/docs
mv ZiPhone ziphone-3.4e-mac-os-x-cli
zip -r ziphone-3.4e-mac-os-x-cli.zip ziphone-3.4e-mac-os-x-cli
rm -rf ziphone-3.4e-mac-os-x-cli