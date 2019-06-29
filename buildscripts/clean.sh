#!/bin/sh

cd ../
rm -rf ZiPhone
rm -f zibri.dat
find . -name '.DS_Store' -type f -delete
rm -rf ziphone-3.5-linux-cli.zip ziphone-3.5-linux-cli ziphone-3.5-mac-os-x-cli.zip ziphone-3.5-mac-os-x-cli ziphone-3.5-mac-os-x-gui.zip ziphone-3.5-mac-os-x-gui ziphone-3.5-windows-cli.zip
echo "Nice and clean."