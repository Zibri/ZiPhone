#!/bin/bash

echo "Generating offset file..."
cd ../
dd if=/dev/zero bs=$((0xCC2000)) count=1 of=Offset
echo "Adding offset to zibri.dat..."
cat Offset zibri.dmg > zibri.dat
echo "Cleaning up..."
rm -f Offset
echo "Done. Change MD5 in ziphone.cpp (if neccesary) to:"
md5sum zibri.dat