#!/bin/sh

cd ../
rm -rf ZiPhone
rm -f zibri.dat
find . -name '.DS_Store' -type f -delete
rm -rf ziphone-3.4e-linux-cli.zip ziphone-3.4e-mac-os-x-cli.zip ziphone-3.4e-mac-os-x-gui.zip ziphone-3.4e-windows-cli.zip
echo "Nice and clean."