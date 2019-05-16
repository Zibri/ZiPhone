▒███████▒ ██▓ ██▓███   ██░ ██  ▒█████   ███▄    █ ▓█████ 
▒ ▒ ▒ ▄▀░▓██▒▓██░  ██▒▓██░ ██▒▒██▒  ██▒ ██ ▀█   █ ▓█   ▀ 
░ ▒ ▄▀▒░ ▒██▒▓██░ ██▓▒▒██▀▀██░▒██░  ██▒▓██  ▀█ ██▒▒███   
  ▄▀▒   ░░██░▒██▄█▓▒ ▒░▓█ ░██ ▒██   ██░▓██▒  ▐▌██▒▒▓█  ▄ 
▒███████▒░██░▒██▒ ░  ░░▓█▒░██▓░ ████▓▒░▒██░   ▓██░░▒████▒
░▒▒ ▓░▒░▒░▓  ▒▓▒░ ░  ░ ▒ ░░▒░▒░ ▒░▒░▒░ ░ ▒░   ▒ ▒ ░░ ▒░ ░
░░▒ ▒ ░ ▒ ▒ ░░▒ ░      ▒ ░▒░ ░  ░ ▒ ▒░ ░ ░░   ░ ▒░ ░ ░  ░
░ ░ ░ ░ ░ ▒ ░░░        ░  ░░ ░░ ░ ░ ▒     ░   ░ ░    ░   
  ░ ░     ░            ░  ░  ░    ░ ░           ░    ░  ░
░                                                        
Ziphone version 3.4 (14th of May 2019)
=================================================================================== 
ZiPhone Windows is back.
ZiPhone Mac OS X has a new kill iTunes method that works correctly, replacing the 
older one that could sometimes fail and cause ZiPhone to hang.
ZiPhone installs reboot into the proper place, Apple removed /usr/sbin/reboot in 
iPhone 1.1.4 and some other versions.
The new open source Installer.app v3.13 beta is installed as part of the jailbreak for 
1.0-1.1.5.
The Z icon has been fixed and works on 1.1.3+.
Rewrite of ZiPhone Linux is compatible with all distributions that have lib-usb version 
1.0 or newer.
Improved ramdisk and Mac GUI. 
Localization fixed for Mac GUI.
ziphone -b now flashes 1.1.4 baseband, since there would otherwise be no
baseband.
Ziphone version 3.3 (31st of March 2019)
===================================================================================  

Really fixed all SpringBoard patching issues. 
Added AFC2 for firmware 1.0-1.1.5 jailbreaks.
Improved efficiency of prof.sh.
ZiPhone now stashes apps, ringtones, and fonts for more root partition space.
ZiPhone only activates youtube for 1.1-1.1.5 firmwares (and not on 1.0.x since the 
activation certs were never compatible). Completely useless in 2019, but whatever :)

Ziphone version 3.2c (14th of March 2019)
===================================================================================
New linux version of ZiPhone.
The Mac GUI is back.
Building from source has never been easier. 

To run the ZiPhone linux binary make sure the package libusb is installed. Then cd 
into the ZiPhone directory and execute ./ziphone.

Further changes in v3.2c include better compatibility with 2.0 beta 2. All features 
for iPhone users will now work on 2.0 beta 2 (except unlock, that only works on 1.1.4 
iPhone firmware). The method ZiPhone uses to enter DFU mode was patched by apple in 
2.0 beta 2. So ./ziphone -D won't work on 2.0 beta 2. On 2.0 beta 2, you have to enter 
Recovery Mode manually. Do not have ZiPhone do it for you. It will cause ZiPhone not 
to work successfully. Instead, enter Recovery Mode manually. First unplug the device, 
then turn it off. Connect the device again, and it will start turning on. Immediately 
press and hold the home button, until the Connect To iTunes graphic appears. Then run 
ZiPhone.

Lastly, ./ziphone -j has been updated. It now jailbreaks everything, not just iPhones. 
./ziphone -j will jailbreak iPhone or iPod 1.0-1.1.5 and 2.0 beta 2.

Ziphone version 3.2b (28th of Febuary 2019)
===================================================================================
!!! ZiPhone now officially supports a bare bones jailbreak with hactivation for 
firmware 2.0 beta 2! Back in 2008, only Zibri had accomplished a firmware 2.0 beta 3 
ramdisk hack jailbreak. People said his hack was stolen code from the iPhone Dev Team 
repository, and then they said it didn't work on the firmware 1.2 and 2.0 1-3 betas! 
Although a version of ZiPhone using it was never released back in 2008, this new 
version 3.2b in 2019 can now jailbreak and hactivate firmware 2.0 beta 2.

To jailbreak an iPhone or iPod Touch on firmware 2.0 beta 2, use "ziphone -Z I". 
The command "ziphone -Z I" will now:
-Jailbreak an iPod Touch on firmware 1.1-1.1.5 and 2.0 beta 2.
-Jailbreak an iPhone on firmware 2.0 beta 2.

The jailbreak allows you to connect to AFC2 with iPHUC. It will also hactivate so you 
can use the beta. Code sign is not patched by ZiPhone.


Ziphone version 3.2 (25th of Febuary 2019)
===================================================================================
Another update by lex. 
Firmware 1.1-1.1.1 3rd party app support has been added. 
Proper MD5 checksum.

Ziphone version 3.1 (20th of Febuary 2019)
===================================================================================
This new version is an update by lex, that is supported by the original creator of 
Ziphone, Zibri. Added Bootloader version detection. ZiPhone will only flash BL3.9 
if you have an iPhone with BL4.6. Updated firmware 1.1.4 secpack to firmware 2.0 
secpack. ZiPhone can now erase/downgrade/unlock any iPhone that has previously been 
on iPhone OS 2.0-3.1.3. Added iPod Touch firmware 1.1.2 support, also enabled 3rd
party applications on iPhone/iPod Touch firmware 1.1.2. Updated Installer.app to 
include Community Sources v2.0 (whitera1n.com/apptapp/repo.xml and 
simplysmp.net/installer/repo.xml). Installer will install when ran directly from 
Recovery Mode.

The installation of BSD Subsystem/SSH from v3.0 is not included in this release. 
Install BSD Subsystem and SSH from Installer.app after jailbreaking if you wish. 
The plugin system works if you manually place "Blutcher.zip" into either 
/var/root/Media/Blutcher.zip or /var/mobile/Media/Blutcher.zip on the iPhone/iPod 
Touch filesystem, and then run ZiPhone jailbreak. ZiPhone v3.1 can not yet install 
Blutcher.zip without it already being present on the iPhone/iPod Touch filesystem.

Ziphone version 3.0 (30th of March 2008)
===================================================================================
Added automatic installation of BSD subsystem, SSH and Installer (now working 
immediately after ziphone)
Added PLUGIN system.
Please read PLUGIN_HOWTO.txt to know how to manage plugins.
Cleaned up code and ziphone main functions.
Added (surprise)
Oral sex is not yet implemented. :)

Ziphone version 2.9 (unreleased)
===================================================================================
Added WiFi FIX workaround.
People with a healthy baseband but corrupted seczone will have their wifi back.
But it's not permanent. 

Ziphone version 2.8 (unreleased)
===================================================================================
Removed FIX NVRAM. Now automatic.

Ziphone version 2.7 (unreleased)
===================================================================================
Debug version (a few minor bugs were found and killed)
Cleaned up code and ziphone main functions.

Ziphone version 2.6d (14th Mar 2008) 14:16 CET
===================================================================================
Added FIX NVRAM option. (-Z F) to solve some people problems.

Ziphone version 2.6 (14th Mar 2008) 02:07 CET
===================================================================================
Added iPod Touch compatibility for firmware 1.1.4 ONLY.
(restore to 1.1.4 then run ziphone -Z I)

Ziphone version 2.5c (2nd Mar 2008) 17:56 CET
===================================================================================
Corrected a bug in 2.5b that prevented bootloader downgrade.

Ziphone version 2.5b (1st Mar 2008) 10:39 CET
===================================================================================
Corrected a bug in 2.5 that prevented baseband erasing.


Ziphone version 2.5 (29th Feb 2008) 05:08 CET
===================================================================================

Version 2.5 Supports Firmware version 1.1.4.

If you use 2.5 on previous iPhone firmware versions, 
you will have the new baseband (unlocked of course) and old OS.

For 1.1.3 use version 2.4 OR 2.5 (still in testing for 1.1.3)

Ziphone version 2.4 (17th Feb 2008) 23:28 CET
===================================================================================

Starting with version 2.4, Ziphone provides a simple all-in-one interface or a separate
advanced interface for experts or for people who needs more control over the jailbreak
process.  Users with AT&T or other "legitimate" iPhone carrier SIMs may wish to use the
advanced interface in order to retain their own real activation tokens.

The two all-in one modes are:
  ziphone -Z Y
    Jailbreak, activate, and unlock any version
    
  ziphone -Z N
    Jailbreak and activate, but don't unlock
    
To see the advanced commands (same as in older versions), run:
  ziphone -Z A
  
For customers of official iPhone cell carriers, it may be preferable to run:
  ziphone -j
    Just jailbreak, don't touch activation tokens or unlock.  You still still need
    to connect the phone to iTunes to activate.
    
  ziphone -j -u
    Jailbreak and also unlock 1.1.4 firmware.
    
Note that after running a jailbreak on a "fresh" phone, you will need to manually install
the "BSD Subsystem" package from Installer before many other programs will work.  This package
is NOT included in Ziphone due to size restrictions of the jailbreaking ramdisk.

===================================================================================

No 'dev-team' was directly involved with this work.  
This program is based on the work of everyone who
believed in free software. (Thanks for the toolchain!)

Thanks to geohot for his latest work.
Thanks to Tissy for moral support.
Thanks to iphone-elite.org for support.
Thanks to Viper and Tifel and ortner for being so nice always.
Thanks to pendor for preliminary work on OSX
Thanks to iRev (a.k.a. REVEREND) for the OS X version
Thanks to ilaria of ilarialab (http://ilaria.netsons.org) for the great artwork
Thanks to mzaouara for the ascii art (he didn't use some generator he's an ascii artist !)
Thanks to PsxGunDown to review this readme. 

Namaste,
Zibri.

===================================================================================

Additionally, ZiPhone Linux would not be possible without Planetbeing's work on his Xpwn utility, and Geohot's work on iBooter.
-Lex. 

Legal notice:
ZiPhone does NOT change the iPhone internal IMEI.
It changes the baseband to THINK the imei is another one.
No changes are made inside the SECZONE.

To restore the original IMEI, just issue:

ziphone -u (to keep it unlocked)

or the full restore procedure below.

And ANY phone can be restored to a BRAND NEW state, by using this procedure:

ziphone -e

then

ziphone -D

then restore to 1.0.1 or newer. If your on 2.0 beta 2, ziphone -D won't work. You need to enter DFU mode manually,
or use Recovery Mode.
