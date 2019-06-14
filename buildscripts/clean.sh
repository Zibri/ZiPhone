#!/bin/sh

cd ../
rm -rf ZiPhone
rm -f zibri.dat
find . -name '.DS_Store' -type f -delete
rm -rf ziphone-3.4f-linux-cli.zip ziphone-3.4f-mac-os-x-cli.zip ziphone-3.4f-mac-os-x-gui.zip ziphone-3.4f-windows-cli.zip
echo "Nice and clean."