#!/bin/sh

echo "Building Linux CLI..."
cd ../
rm -rf ZiPhone ziphone-3.4f-linux-cli.zip ziphone-3.4f-linux-cli
mkdir ZiPhone
mkdir ZiPhone/ZiPhone
cd ziphone-linux-cli
make
cp build/ziphone ../ZiPhone/ZiPhone/ziphone
make clean
cd ../
cp dfu.dat  ZiPhone/ZiPhone/
cp zibri.dat ZiPhone/ZiPhone/
cp igor.dat  ZiPhone/ZiPhone/
cp victor.dat  ZiPhone/ZiPhone/
cp -r docs ZiPhone/docs
mv ZiPhone ziphone-3.4f-linux-cli
zip -r ziphone-3.4f-linux-cli.zip ziphone-3.4f-linux-cli
rm -rf ziphone-3.4f-linux-cli


