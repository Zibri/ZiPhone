#!/bin/sh

echo "Building Linux GUI..."
cd ../
cd ziphone-linux-gui
gcc zgui.c -o zgui $(pkg-config --cflags --libs gtk+-3.0)
echo "Building Linux CLI..."
cd ../
rm -rf ZiPhone ziphone-3.5a-linux-cli.zip ziphone-3.5a-linux-cli
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
cp ziphone-linux-gui/zgui ZiPhone/ZiPhone/
rm -f ziphone-linux-gui/zgui
mv ZiPhone ziphone-3.5a-linux-gui
zip -r ziphone-3.5a-linux-gui.zip ziphone-3.5a-linux-gui
rm -rf ziphone-3.5a-linux-gui


