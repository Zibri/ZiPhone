#!/bin/sh

echo "Building Linux CLI..."
cd ../
rm -rf ZiPhone
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
echo "Built in directory ../ZiPhone."


