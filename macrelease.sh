#!/bin/bash

if [ -d "libusb-mac" ]; then
    echo "Found directory of libusb-mac"
else 
    echo "You need to be in the root ziphone source directory to run this script!"
    exit 1
fi

rm -rf ziphone-3.6-cli-mac*
cd libusb-mac
rm -rf /usr/local/
rm -rf /usr/local/bin/
rm -rf /usr/local/bin/i386-apple-darwin9.6.0-pkg-config
rm -rf /usr/local/bin/libusb-config
rm -rf /usr/local/bin/pkg-config
rm -rf /usr/local/include/
rm -rf /usr/local/include/libusb-1.0/
rm -rf /usr/local/include/libusb-1.0/libusb.h
rm -rf /usr/local/include/usb.h
rm -rf /usr/local/lib/
rm -rf /usr/local/lib/libusb-0.1.4.dylib
rm -rf /usr/local/lib/libusb-1.0.0.dylib
rm -rf /usr/local/lib/libusb-1.0.a
rm -rf /usr/local/lib/libusb-1.0.dylib
rm -rf /usr/local/lib/libusb-1.0.la
rm -rf /usr/local/lib/libusb.a
rm -rf /usr/local/lib/libusb.dylib
rm -rf /usr/local/lib/libusb.la
rm -rf /usr/local/lib/pkgconfig/
rm -rf /usr/local/lib/pkgconfig/libusb-1.0.pc
rm -rf /usr/local/lib/pkgconfig/libusb.pc
rm -rf /usr/local/share/
rm -rf /usr/local/share/acrm -rf /usr/local/
rm -rf /usr/local/share/acrm -rf /usr/local/pkg.m4
rm -rf /usr/local/share/doc/
rm -rf /usr/local/share/doc/pkg-config/
rm -rf /usr/local/share/doc/pkg-config/pkg-config-guide.html
rm -rf /usr/local/share/man/
rm -rf /usr/local/share/man/man1/
rm -rf /usr/local/share/man/man1/pkg-config.1
tar -jxvf libusb-1.0.22-libusb-compat-0.1.7-pkg-config-0.29.2-intel-32.tar.bz2 -C /usr
cd ../
make -f Makefile.macintel32
./macgui.sh
tar -jcvf ziphone-3.6-gui-mac-intel-32.tar.bz2 ZiPhoneOSX.app
rm -rf ZiPhoneOSX.app
cd libusb-mac
rm -rf /usr/local/
rm -rf /usr/local/bin/
rm -rf /usr/local/bin/i386-apple-darwin9.6.0-pkg-config
rm -rf /usr/local/bin/libusb-config
rm -rf /usr/local/bin/pkg-config
rm -rf /usr/local/include/
rm -rf /usr/local/include/libusb-1.0/
rm -rf /usr/local/include/libusb-1.0/libusb.h
rm -rf /usr/local/include/usb.h
rm -rf /usr/local/lib/
rm -rf /usr/local/lib/libusb-0.1.4.dylib
rm -rf /usr/local/lib/libusb-1.0.0.dylib
rm -rf /usr/local/lib/libusb-1.0.a
rm -rf /usr/local/lib/libusb-1.0.dylib
rm -rf /usr/local/lib/libusb-1.0.la
rm -rf /usr/local/lib/libusb.a
rm -rf /usr/local/lib/libusb.dylib
rm -rf /usr/local/lib/libusb.la
rm -rf /usr/local/lib/pkgconfig/
rm -rf /usr/local/lib/pkgconfig/libusb-1.0.pc
rm -rf /usr/local/lib/pkgconfig/libusb.pc
rm -rf /usr/local/share/
rm -rf /usr/local/share/acrm -rf /usr/local/
rm -rf /usr/local/share/acrm -rf /usr/local/pkg.m4
rm -rf /usr/local/share/doc/
rm -rf /usr/local/share/doc/pkg-config/
rm -rf /usr/local/share/doc/pkg-config/pkg-config-guide.html
rm -rf /usr/local/share/man/
rm -rf /usr/local/share/man/man1/
rm -rf /usr/local/share/man/man1/pkg-config.1
tar -jxvf libusb-1.0.22-libusb-compat-0.1.7-pkg-config-0.29.2-intel-64.tar.bz2 -C /usr
cd ../
make -f Makefile.macintel64
./macgui.sh
tar -jcvf ziphone-3.6-gui-mac-intel-64.tar.bz2 ZiPhoneOSX.app
rm -rf ZiPhoneOSX.app
cd libusb-mac
rm -rf /usr/local/
rm -rf /usr/local/bin/
rm -rf /usr/local/bin/i386-apple-darwin9.6.0-pkg-config
rm -rf /usr/local/bin/libusb-config
rm -rf /usr/local/bin/pkg-config
rm -rf /usr/local/include/
rm -rf /usr/local/include/libusb-1.0/
rm -rf /usr/local/include/libusb-1.0/libusb.h
rm -rf /usr/local/include/usb.h
rm -rf /usr/local/lib/
rm -rf /usr/local/lib/libusb-0.1.4.dylib
rm -rf /usr/local/lib/libusb-1.0.0.dylib
rm -rf /usr/local/lib/libusb-1.0.a
rm -rf /usr/local/lib/libusb-1.0.dylib
rm -rf /usr/local/lib/libusb-1.0.la
rm -rf /usr/local/lib/libusb.a
rm -rf /usr/local/lib/libusb.dylib
rm -rf /usr/local/lib/libusb.la
rm -rf /usr/local/lib/pkgconfig/
rm -rf /usr/local/lib/pkgconfig/libusb-1.0.pc
rm -rf /usr/local/lib/pkgconfig/libusb.pc
rm -rf /usr/local/share/
rm -rf /usr/local/share/acrm -rf /usr/local/
rm -rf /usr/local/share/acrm -rf /usr/local/pkg.m4
rm -rf /usr/local/share/doc/
rm -rf /usr/local/share/doc/pkg-config/
rm -rf /usr/local/share/doc/pkg-config/pkg-config-guide.html
rm -rf /usr/local/share/man/
rm -rf /usr/local/share/man/man1/
rm -rf /usr/local/share/man/man1/pkg-config.1
tar -jxvf libusb-1.0.22-libusb-compat-0.1.7-pkg-config-0.29.2-ppc-32.tar.bz2 -C /usr
cd ../
make -f Makefile.macppc
./macgui.sh
tar -jcvf ziphone-3.6-gui-mac-ppc-32.tar.bz2 ZiPhoneOSX.app
rm -rf ZiPhoneOSX.app
rm -rf /usr/local/
rm -rf /usr/local/bin/
rm -rf /usr/local/bin/i386-apple-darwin9.6.0-pkg-config
rm -rf /usr/local/bin/libusb-config
rm -rf /usr/local/bin/pkg-config
rm -rf /usr/local/include/
rm -rf /usr/local/include/libusb-1.0/
rm -rf /usr/local/include/libusb-1.0/libusb.h
rm -rf /usr/local/include/usb.h
rm -rf /usr/local/lib/
rm -rf /usr/local/lib/libusb-0.1.4.dylib
rm -rf /usr/local/lib/libusb-1.0.0.dylib
rm -rf /usr/local/lib/libusb-1.0.a
rm -rf /usr/local/lib/libusb-1.0.dylib
rm -rf /usr/local/lib/libusb-1.0.la
rm -rf /usr/local/lib/libusb.a
rm -rf /usr/local/lib/libusb.dylib
rm -rf /usr/local/lib/libusb.la
rm -rf /usr/local/lib/pkgconfig/
rm -rf /usr/local/lib/pkgconfig/libusb-1.0.pc
rm -rf /usr/local/lib/pkgconfig/libusb.pc
rm -rf /usr/local/share/
rm -rf /usr/local/share/acrm -rf /usr/local/
rm -rf /usr/local/share/acrm -rf /usr/local/pkg.m4
rm -rf /usr/local/share/doc/
rm -rf /usr/local/share/doc/pkg-config/
rm -rf /usr/local/share/doc/pkg-config/pkg-config-guide.html
rm -rf /usr/local/share/man/
rm -rf /usr/local/share/man/man1/
rm -rf /usr/local/share/man/man1/pkg-config.1
rm -rf ZiPhoneOSX.app
rm -rf ziphone-3.6-cli-mac
echo "Done."

