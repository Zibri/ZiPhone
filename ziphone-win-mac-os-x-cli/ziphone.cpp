#if defined(WIN32)
#	define WIN32_LEAN_AND_MEAN
#	include <windows.h>
#	include <CoreFoundation.h>
#	define CFSTRINGENCODING kCFStringEncodingASCII
#	define sleep(seconds) Sleep(seconds*1000)
#endif

#if defined(__APPLE__)
#include <CoreFoundation/CoreFoundation.h>
#include <stdlib.h> 
#include <stdio.h> 
#define CFSTRINGENCODING kCFStringEncodingMacRoman
#endif

#include <signal.h>
#include <sys/stat.h>
#include <iostream>
#include "MobileDevice.h"
#include "privateFunctions.h"
#include "md5.h"

using namespace std;

bool done=false;
int Z=0;
int Stage=0;
int RecoverCount=0;
int progress=-1;
char progressStr[64]="";
char errorStr[64]="";
unsigned char md5rd[16]="";
unsigned char md5dfu[16]="";
unsigned char md5igor[16]="";
unsigned char md5victor[16]="";
int lasterr;
bool ExitAfterStage=false;
bool unlock=false;
bool activate=false;
bool jailbreak=false;
bool chimei=false;
bool ierase=false;
bool bl39=false;
bool debug=false;
bool dfu=false;
bool recover=false;
bool normalmode=false;
bool verbose=false;

char imei[127]="setenv imei ";

char ramdisk[128]="zibri.dat";

char igor[128]="igor.dat";

char victor[128]="victor.dat";

char dfudat[128]="dfu.dat";
                           
unsigned char rdmd5[16]= {  0xf3,0x4c,0xad,0xae,0xfe,0x82,0xd1,0x61,0x6e,0x57,0x2b,0xf7,0x76,0xe0,0xe4,0x04 };
unsigned char dfumd5[16]= { 0x3f,0xf3,0xc0,0xb3,0x2d,0xfa,0xd6,0x9a,0xd6,0x22,0x2a,0x59,0x9d,0x88,0x2f,0x20 };
unsigned char igormd5[16]= { 0xea,0x61,0xa1,0x57,0xa8,0x3d,0xde,0x9e,0x45,0xde,0x89,0x99,0xdd,0xbb,0x8e,0x93 };
unsigned char victormd5[16]= { 0x0b,0x75,0x44,0x1c,0x47,0x08,0x3a,0x48,0xcb,0x18,0x39,0xc0,0x0a,0x94,0x55,0xd7 };

CFStringRef StringtoCFString(string input) {
  return CFStringCreateWithCString(NULL, input.c_str(), CFSTRINGENCODING);
}

/* * * ( Function Declarations ) * * */

void RestoreNotificationCallback(am_recovery_device *rdev);
void DeviceNotificationCallback(am_device_notification_callback_info *info);
void DisconnectRecoveryCallback(struct am_recovery_device *rdev);
void ConnectRecoveryCallback(struct am_recovery_device *rdev);
void DfuNotificationCallback(am_recovery_device *rdev);
void MurderStupidHelper();

/* * * ( Error and Progress Reporting ) * * */

void ProgressStep(const char *message) {
  strncpy(progressStr, message, 63);
  cout << progressStr << endl;
  sleep(1); // for the user
}

void ReportDone() {
#if defined(__APPLE__)
  CFRunLoopStop(CFRunLoopGetCurrent());
#endif
  done=true;
}

void ReportError(const char *message) {
  strncpy(errorStr, message, 63);
  cout << "Failed: (" << lasterr << ") " << errorStr << endl;
  ReportDone();
}

/* * * ( File Operations ) * * */

/* * * ( Stages ) * * */

void PairIPhone(am_device *iPhone) {
  if (AMDeviceConnect(iPhone)) {
    ReportError("AMDeviceConnect failed.");
    exit(10);
  }

  if (!AMDeviceIsPaired(iPhone)) {
    cout << "Unable to pair with device." << endl << endl << "You may get this error if you try to run ZiPhone" << endl
        << "with a device that isn't synced with iTunes on this computer." << endl
        << "Please try putting the device into recovery mode manually " << endl << "and try again." << endl << endl
        << "To enter recovery mode, unplug the device, hold the power button" << endl
        << "for a few seconds and then 'slide to power off'.  " << endl
        << "With the device still powered off, hold the home button down " << endl
        << "and connect to the dock or cable.  The Apple logo will appear for a few " << endl
        << "seconds, and finally the 'connect to iTunes' graphic will appear." << endl
        << "Do not release the home button until the 'connect' graphic is visible." << endl << endl
        << "Try running ZiPhone again at that point." << endl << endl;
    ReportError("Pairing Issue.");
    exit(11);
  }

  if (AMDeviceValidatePairing(iPhone)!=0) {
    ReportError("Pairing NOT Valid. Sync with iTunes.");
    exit(12);
  }

  if (AMDeviceStartSession(iPhone)) {
    ReportError("Session NOT Started.");
    exit(13);
  }
}

void Stage0() { // Register callbacks
  initPrivateFunctions();

  ProgressStep("Searching for iPhone or iPod Touch...");
  MurderStupidHelper();
  
  if (!ExitAfterStage) {
    Stage=2;
  }

  am_device_notification *notif;
  AMDeviceNotificationSubscribe(DeviceNotificationCallback, 0, 0, 0, &notif);
  AMRestoreRegisterForDeviceNotifications(DfuNotificationCallback, ConnectRecoveryCallback, NULL, DisconnectRecoveryCallback, 0, 
  NULL);
}

void Stage2(struct am_recovery_device *rdev) { // Booting in recovery mode
	MurderStupidHelper();

  if (dfu) {
    ProgressStep("Loading dfu.dat...");
  } else if (normalmode) {
    ProgressStep("Rebooting in normal mode...");
  } else {
    ProgressStep("Working...");
  }

//  rdev->callback = &RestoreNotificationCallback;
//  rdev->user_info = NULL;

  if (Z==1) {
    unlock=true;
    jailbreak=true;
    activate=true;
    chimei=false;
    ierase=false;
    bl39=true;
    dfu=false;
  }

  else if (Z==2) {
    unlock=true;
    jailbreak=true;
    activate=false;
    chimei=false;
    ierase=false;
    bl39=true;
    dfu=false;
  }

  else if (Z==4) {
    unlock=false;
    jailbreak=true;
    activate=false;
    chimei=false;
    ierase=false;
    bl39=false;
    dfu=false;
  }

  // ******* SAFETY CHECKS *** SOME WILL BE REMOVED AFTER FAILPROOF TESTS *******

  if (ierase) {
    //           unlock=false;
    //           jailbreak=false;
    //           activate=false;
    chimei=false;
  }

  if (bl39) {
    unlock=true;
    //           jailbreak=false;
    //           activate=false;
    //           chimei=false;
    //           ierase=false;
  }

  if (dfu) {
    unlock=false;
    jailbreak=false;
    activate=false;
    chimei=false;
    ierase=false;
    bl39=false;
  }

  if (verbose) {
    vebose=true;
    unlock=false;
    jailbreak=false;
    activate=false;
    chimei=false;
    ierase=false;
    bl39=false;
  }
	
  if (normalmode) {
    unlock=false;
    jailbreak=false;
    activate=false;
    chimei=false;
    ierase=false;
    bl39=false;
    dfu=false;
    verbose=false;
  }

  sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault, "setenv auto-boot true", kCFStringEncodingUTF8));

  sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault, "setpicture 0", kCFStringEncodingUTF8));
 
   sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault, "bgcolor 0 0 64", kCFStringEncodingUTF8));
  
  if (!dfu&&!normalmode) {
    sendFileToDevice(rdev, StringtoCFString(ramdisk));
  } else if (dfu){
    sendFileToDevice(rdev, StringtoCFString(dfudat));
  }
  
  
  if (bl39) {
    sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault, "setenv bl39 1", kCFStringEncodingUTF8));
  }

  if (unlock) {
    sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault, "setenv unlock 1", kCFStringEncodingUTF8));
  }

  if (jailbreak) {
    sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault, "setenv jailbreak 1", kCFStringEncodingUTF8));
  }

  if (activate) {
    sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault, "setenv activate 1", kCFStringEncodingUTF8));
  }

  if (ierase) {
    sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault, "setenv ierase 1", kCFStringEncodingUTF8));
  }

  if (chimei) {
    sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault, imei, kCFStringEncodingUTF8));
  }

  if (!dfu && !normalmode) {
    sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault,
        "setenv boot-args rd=md0 -s -x pmd0=0x09CC2000.0x0133D000", kCFStringEncodingUTF8));
  }

  if (normalmode) {
    sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault,
        "setenv boot-args -d", kCFStringEncodingUTF8));
	
	sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault,
		"setenv boot-parition 0", kCFStringEncodingUTF8));
  }

  if (verbose) {
    sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault, "setenv boot-args -v", kCFStringEncodingUTF8));
	 
	
    sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault,
		"setenv boot-parition 0", kCFStringEncodingUTF8))
  }

    sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault, "saveenv", kCFStringEncodingUTF8));

  if (!dfu) {
  	sendFileToDevice(rdev, StringtoCFString(victor));
    sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault, "bootx", kCFStringEncodingUTF8));
	sleep(5);
	sendFileToDevice(rdev, StringtoCFString(igor));
    sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault, "bootx", kCFStringEncodingUTF8));
	sleep(5);
    sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault, "fsboot", kCFStringEncodingUTF8));
  } else if (dfu) {
	sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault,
		"setenv boot-partition 0", kCFStringEncodingUTF8));
  	sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault,
		"setenv boot-args -d", kCFStringEncodingUTF8));
  	sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault,
		"saveenv", kCFStringEncodingUTF8));
    sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault, "go", kCFStringEncodingUTF8));
  } else {
    sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault, "bootx", kCFStringEncodingUTF8));
    sleep(5);
    sendFileToDevice(rdev, StringtoCFString(victor));
    sendCommandToDevice(rdev, CFStringCreateWithCString(kCFAllocatorDefault, "bootx", kCFStringEncodingUTF8));
  }

  if (!unlock&&(activate||jailbreak)) {
    ProgressStep("Please wait 45\".");
  }

  if (unlock && (!bl39)) {
    ProgressStep("Please wait 2\'30\".");
  }

  if (bl39) {
    ProgressStep("Please wait 4'00\".");
  }

  Stage=9;

  if (ExitAfterStage) {
    exit(0);
  }
}

/* * * ( Callback functions ) * * */

void RestoreNotificationCallback(am_recovery_device *rdev) {
  cout << "iTunes is restoring your iPhone or iPod Touch..." << endl;
  ReportDone();
}

void DfuNotificationCallback(am_recovery_device *rdev) {
  cout << "iPhone or iPod in DFU Mode. Run iTunes and restore firmware!" << endl;
  ReportDone();
}

void DeviceNotificationCallback(am_device_notification_callback_info *info) {
  //cout << "DeviceNotificationCallback" << endl;

  if (info->msg==ADNCI_MSG_CONNECTED) {
    if (Stage!=9) {
      cout << "Entering recovery mode." << endl;

      PairIPhone(info->dev);
      AMDeviceEnterRecovery(info->dev);
    } else {
      ReportDone();
    }
  }
}

void DisconnectRecoveryCallback(struct am_recovery_device *rdev) {
  //	cout << "DisconnectRecoveryCallback" << endl;
  // this is a stub, but it looks like it gives a Bus error if you don't use it.
}

void ConnectRecoveryCallback(struct am_recovery_device *rdev) {
  if ((!recover) && (Stage==2)) {
    Stage2(rdev);
  } else {
    ReportDone();
  }
}

void MurderStupidHelper() {
#if defined(__APPLE__)
system("/usr/bin/killall iTunes > /dev/null 2>&1");
system("/usr/bin/killall iTunesHelper > /dev/null 2>&1");
#endif
} 

/* * * ( Main ) * * */

bool temp_file_exists(const char *filename) {
  int count=0;
  FILE *pFile=fopen(filename, "rb");
  FILE *pFile2=fopen("dfu.dat", "rb");
  FILE *pFile3=fopen("igor.dat", "rb");
  FILE *pFile4=fopen("victor.dat", "rb");
  if (pFile && pFile2 && pFile3 && pFile4) {
    fclose(pFile);
    fclose(pFile2);
    fclose(pFile3);
	fclose(pFile4);
    md5_file(ramdisk, md5rd);
    md5_file(dfudat, md5dfu);
    md5_file(igor, md5igor);
	md5_file(victor, md5victor);
    if (debug) {
      printf(  
          "rd: 0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x\n",
          md5rd[0], md5rd[1], md5rd[2], md5rd[3], md5rd[4], md5rd[5], md5rd[6], md5rd[7], md5rd[8], md5rd[9], md5rd[10], md5rd[11],
          md5rd[12], md5rd[13], md5rd[14], md5rd[15]);
      printf(
          "dfu:0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x\n",
          md5dfu[0], md5dfu[1], md5dfu[2], md5dfu[3], md5dfu[4], md5dfu[5], md5dfu[6], md5dfu[7], md5dfu[8], md5dfu[9], md5dfu[10],
          md5dfu[11], md5dfu[12], md5dfu[13], md5dfu[14], md5dfu[15]);
      printf(
          "igor:0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x\n",
          md5igor[0], md5igor[1], md5igor[2], md5igor[3], md5igor[4], md5igor[5], md5igor[6], md5igor[7], md5igor[8], md5igor[9], md5igor[10],
          md5igor[11], md5igor[12], md5igor[13], md5igor[14], md5igor[15]);
      printf(
          "victor:0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x,0x%2.2x\n",
          md5victor[0], md5victor[1], md5victor[2], md5victor[3], md5victor[4], md5victor[5], md5victor[6], md5victor[7], md5victor[8], md5victor[9], md5victor[10],
          md5victor[11], md5victor[12], md5victor[13], md5victor[14], md5victor[15]);
      return true;
    }
    for (count = 0; count < 16; count++) {
      if ((md5rd[count] != rdmd5[count]) || (md5dfu[count] != dfumd5[count]) || (md5victor[count] != victormd5[count]) || (md5igor[count] != igormd5[count])) {

        cout << "Redownload ZiPhone !" << endl;
        cout << "Go get the full archive at http://whitera1n.com/ziphone!" << endl;

        return false;
        break;
      }
return true;
    }
  }

  cout << filename << " could not be opened for reading." << endl;
  ReportDone();
  return false;
}

void Banner() {
  cout << endl << "  ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ" << endl;
  cout << "  ZZZZZZZZ                ZZZZZZZZZZZZ" << endl;           
  cout << "  ZZZZZZ                ZZZZZZZZZZZZ" << endl; 
  cout << "  ZZ                  ZZZZZZZZZZZZ" << endl; 
  cout << "  ZZ               ZZZZZZZZZZZZZ" << endl; 
  cout << " 	     ZZZZZZZZZZZZ " << endl;
  cout << "  	  ZZZZZZZZZZZZ              ZZ" << endl;
  cout << "       ZZZZZZZZZZZZ               ZZZZ" << endl;
  cout << "    ZZZZZZZZZZZZ                ZZZZZZ" << endl;
  cout << "  ZZZZZZZZZZZ                 ZZZZZZZZ" << endl;
  cout << "ZZZZZZZZZZZZ              ZZZZZZZZZZZZ" << endl; 
  cout << "ZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZZ" << endl << endl;
  cout << "ZiPhone v3.4a by Zibri. https://ziphone.zibri.org" << endl;
  cout << "Source code available at: http://whitera1n.com" << endl;
  cout << endl;
}

void MakeCoffee() {
  Banner();
  if (temp_file_exists(ramdisk) && temp_file_exists(dfudat)) {
    cout << "Making coffee..." << endl;
    sleep(2);
    cout << "Boiling..." << endl;
    sleep(2);
    cout << "Pouring..." << endl;
    sleep(2);
    cout << "Serving..." << endl;
    sleep(2);
    cout << "Now go to Italy to Zibri's house to drink it :)" << endl;
    exit(0);
  } else {
    cout << "We're out of coffee..." << endl;
    sleep(2);
    cout << "Sorry!" << endl;
    exit(9);
  }
}

void UsageNormal() {
  Banner();
  cout << "Usage: ziphone -Z [PnP Mode]" << endl;
  cout << endl;
  cout << "       -Z Y: Zibri! Do Everything for me!" << endl;
  cout << endl;
  cout << "       -Z N: Do Everything BUT do not Unlock!" << endl;
  cout << endl;
  cout << "       -Z A: Show me advanced commands!" << endl;
  cout << endl;
}

void UsageAdvanced() {
  Banner();
  cout << "Usage: ziphone [-b] [-e] [-u] [-a] [-j] [-R] [-D] [-v] [-i imei]" << endl;
  cout << endl;
  cout << "       -b: Downgrade iPhone bootloader 4.6 to 3.9." << endl;
  cout << "       -u: Unlock iPhone 1.1.4." << endl;
  cout << "       -a: Activate iPhone." << endl;
  cout << "       -j: Jailbreak iPhone OR iPod 1.0-1.1.5 and 2.0 beta 2." << endl;
  cout << "       -i: Change imei." << endl;
  cout << "       -e: Downgrade bootloader to 3.9 and erase baseband (for a perfect restore)." << endl;
  cout << "       -D: Enter DFU Mode.(to restore deeply)." << endl;
  cout << "       -R: Enter Recovery Mode. (no real need now)." << endl;
  cout << "       -N: Exit Recovery Mode (normal boot)." << endl;
  cout << "       -C: Make coffee. (and relax!)." << endl;
  cout << "       -v: Debug boot (verbose)." << endl;
  cout << endl;
}

bool parse_args(int argc, char *argv[]) {

  for (int i=1; i<argc; i++) {
    if (argv[i][0]=='-') {
      if (argv[i][1]=='u')
        unlock=true;
      else if (argv[i][1]=='e')
        ierase=true;
      else if (argv[i][1]=='D') {
        if (!(temp_file_exists(dfudat))) {
          Banner();
          ProgressStep("Missing dfu.dat!");
          ProgressStep("Aborted!");
          exit(9);
        } else {
          dfu=true;
        }
      } else if (argv[i][1]=='N') {
        normalmode=true;
      } else if (argv[i][1]=='R') {
        recover=true;
      } else if (argv[i][1]=='v') {
        return false;
      } else if (argv[i][1]=='b') {
        bl39=true;
      } else if (argv[i][1]=='a') {
        activate=true;
      } else if (argv[i][1]=='j') {
        jailbreak=true;
      } else if (argv[i][1]=='C') {
        MakeCoffee();
      } else if (argv[i][1]=='i') {
        if (argc<(i+2)) {
          return false;
        }
        if ((strlen(argv[i+1])!=16)&&(strlen(argv[i+1])!=15)) {
          return false;
        }
        chimei=true;
        if (strlen(argv[i+1])==16) {
          strcat(imei, argv[i+1]);
        } else if (strlen(argv[i+1])==15) {
          strcat(imei, "0");
          strcat(imei, argv[i+1]);
        }
        unlock=true;
      } else if (argv[i][1]=='Z') {
        if (argc!=3) {
          Banner();
          UsageNormal();
          exit(9);
        } else {
          if (argv[i+1][0]=='Y') {
            Z=1;
            return true;
          } else if (argv[i+1][0]=='N') {
            Z=2;
            return true;
          } else if (argv[i+1][0]=='F') {
            Z=4;
            return true;
          } else if (argv[i+1][0]=='A') {
            UsageAdvanced();
            exit(0);
          }
          else {
            return false;
               }
        }
      } else {
        return false;
      }
    }
  }

  return true;
}

int main(int argc, char *argv[]) {

  if ((argc<=1)||(parse_args(argc, argv)==false)) {
    UsageNormal();
    exit(9);
  }

  if (!ExitAfterStage) {
    Banner();
  }

  if ((Stage==0) && (!recover) &&(!dfu) &&(!normalmode)) {
    cout << "Loading " << ramdisk << "." << endl;

    if (!(temp_file_exists(ramdisk))) {
      return 9;
    }
  }

  Stage0();
#if defined(__APPLE__)
  CFRunLoopRun();
#else
  while(!done) {
    sleep(1);
  }
  cout << "Done!" << endl;
#endif
  ReportDone();
  sleep(1);
  return 0;
}
