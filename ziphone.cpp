#include "libibooter.h"
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>

#ifdef WIN32
#include <windows.h>
#include "abstractfilewinleg.c"
#define sleep(x) Sleep(x * 1000)
#else
#include "abstractfile.c"
#endif

using namespace ibooter;
using namespace std;

AbstractFile* ramdisk = createAbstractFileFromFile(fopen("zibri.dat", "rb"));
AbstractFile* igor = createAbstractFileFromFile(fopen("igor.dat", "rb"));
AbstractFile* victor = createAbstractFileFromFile(fopen("victor.dat", "rb"));
AbstractFile* dfu = createAbstractFileFromFile(fopen("dfu.dat", "rb"));

const char *sendcommandresponse = NULL;
char sendcommand[2000];
char endianness;
char macaddress[300]="setenv wifiaddr ";
char imei[127]="setenv imei ";
CIBootConn conn;
ERR_CODE code;

void testbyteorder() {
	short int word = 0x0001;
	char *byte = (char *) &word;
	endianness = byte[0] ? IS_LITTLE_ENDIAN : IS_BIG_ENDIAN;
}

void banner() {
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
  cout << "ZiPhone v3.6 by Zibri. https://ziphone.zibri.org" << endl;
  cout << "Source code available at: http://lexploit.com" << endl;
  cout << endl;
}

void basic_usage() {
  cout << "Usage: ziphone -Z [PnP Mode]" << endl;
  cout << endl;
  cout << "       -Z Y: Zibri! Do Everything for me!" << endl;
  cout << endl;
  cout << "       -Z N: Do Everything BUT do not Unlock!" << endl;
  cout << endl;
  cout << "       -Z A: Show me advanced commands!" << endl;
  cout << endl;
}

void advanced_usage() {
  cout << "Usage: ziphone [-b] [-e] [-u] [-a] [-j] [-r] [-sc] [-D] [-v] [-i imei] [-m MAC]" << endl;
  cout << endl;
  cout << "       -b: Downgrade iPhone bootloader 4.6 to 3.9 and unlock 1.1.3-1.1.4." << endl;
  cout << "       -u: Unlock iPhone 1.1.2 BL4.6 or 1.1.3-1.1.4 BL4.6 and BL3.9." << endl;
  cout << "       -j: Jailbreak iPhone/iPod Touch 1.0-1.1.5 or 2.0 beta 2-3." << endl;
  cout << "       -i: Change imei." << endl;
  cout << "       -m: Change iPhone WiFi MAC address." << endl;
  cout << "       -r: Reset iPhone WiFi MAC address to default." << endl;
  cout << "       -sc: Send a Recovery Mode command and get a response." << endl;
  cout << "       -e: Downgrade iPhone bootloader to 3.9, erase baseband, and enter Recovery (for a perfect restore)." << endl;
  cout << "       -D: Enter DFU Mode.(to restore deeply)." << endl;
  cout << "       -N: Exit Recovery Mode (normal boot)." << endl;
  cout << "       -C: Make coffee. (and relax!)." << endl;
  cout << "       -v: Debug boot (verbose)." << endl;
  cout << endl;
}

void connected() {
#ifdef __APPLE__
	system("killall iTunes > /dev/null 2>&1");
#endif
	cout << "Searching for iPhone or iPod Touch..." << endl;
	if ((code = conn.Connect()) != IB_SUCCESS)
	{
        	cout << endl << "ZiPhone can not connect to your iPhone or iPod Touch. Please make sure that:" << endl << endl;
                cout << "The iPhone or iPod Touch is in Recovery Mode and connected with a USB Dock cable to the computer." << endl;
        	cout << "If your iPhone/iPod Touch is connected, enter it into Recovery Mode now. To do so, unplug the device, hold the power button" << endl;
        	cout << "for a few seconds and then 'slide to power off'.  " << endl;
        	cout << "With the device still powered off, hold the home button down " << endl;
        	cout << "and connect to the dock or cable.  The Apple logo will appear for a few " << endl;
        	cout << "seconds, and finally the 'connect to iTunes' graphic will appear." << endl;
                cout << "Do not release the home button until the 'connect' graphic is visible." << endl << endl;
                cout<< "Try running ZiPhone again at that point." << endl << endl;
		exit(0);
	}
	
		cout << "Connected." << endl;
}

void disconnected() {
		conn.Disconnect();
		cout << "Disconnected." << endl;
}

void original_args() {
		code = conn.SendCommand("setenv boot-partition 0\n");
		code = conn.SendCommand("setenv boot-args \"\"\n");
}

void reset_wifi_mac_address() {
	code = conn.SendCommand("setenv wifiaddr\n");
}


void save() {
code = conn.SendCommand("saveenv\n");
}

void exit_recovery() {
		cout << "Booting normal mode..." << endl;
		original_args();
		save();
		code = conn.SendCommand("fsboot\n");
		cout << "Please wait..." << endl;
}


void verbose_args() {
		code = conn.SendCommand("setenv boot-partition 0\n");
		code = conn.SendCommand("setenv boot-args \"-v\"\n");
		save();
		code = conn.SendCommand("fsboot\n");
		cout << "Please wait..." << endl;
}

void ramdisk_hack() {
	cout << "Working..." << endl;    
	code = conn.SendFile(ramdisk, 0x09CC2000);

	code = conn.SendFile(igor, 0x09000000);
    
	code = conn.SendCommand("setenv boot-args \"rd=md0 -s -x pmd0=0x09CC2000.0x0133D000\"\n");

	code = conn.SendCommand("saveenv\n");
	code = conn.SendCommand("bootx\n");
	sleep(5);
	code = conn.SendFile(victor, 0x09000000);
	code = conn.SendCommand("bootx\n");
	sleep(5);
	code = conn.SendCommand("fsboot\n");
	cout << "Please wait..." << endl;
}

void enter_dfu() {
		cout << "Loading dfu.dat..." << endl;
        connected();
        original_args();
		code = conn.SendFile(dfu, 0x09000000);
		code = conn.SendCommand("go\n");
		cout << "Run iTunes and restore firmware!" << endl;
}

void jailbreak() {
		code = conn.SendCommand("setenv jailbreak \"1\"\n");
}

void activate() {
		code = conn.SendCommand("setenv activate \"1\"\n");
}

void downgrade_baseband_bootloader() {
	code = conn.SendCommand("setenv bl39 \"1\"\n");
}

void unlock() {
		code = conn.SendCommand("setenv unlock \"1\"\n");
}

void erase_baseband() {
		code = conn.SendCommand("setenv ierase \"1\"\n");
}

void change_wifi_mac_address() {
    	code = conn.SendCommand(macaddress);
}


void change_imei() {
		unlock();
    	code = conn.SendCommand(imei);
}
      
int main(int argc, char *argv[]) 
{

testbyteorder();
    
#ifdef __linux__    
if(geteuid() != 0)
{
   cout << endl << "ZiPhone Linux can not connect to your iPhone or iPod Touch without root privilages. Please execute ziphone as root or with sudo." << endl << endl;
   return(1);
}
#endif
	
	if(!ramdisk) {
		cout << "Cannot find zibri.dat!" << endl;
		return(1);
	}

	if(!igor) {
		cout << "Cannot find igor.dat!" << endl;
		return(1);
	}

	if(!victor) {
		cout << "Cannot find victor.dat!" << endl;
		return(1);
	}

			if(!dfu) {
			cout << "Cannot find dfu.dat!" << endl;
			return(1);
		}

banner();

	if(argc < 2) {
	basic_usage();
	return 0;
	}
	
	


std::vector<std::string> args(argv, argv+argc);
	
if (strcmp(argv[1], "-Z") == 0) {{
	if (strcmp(argv[2], "A") == 0) {{
		advanced_usage();
				return(0);;
	}}
}}
	connected();
	
	if (strcmp(argv[1], "-Z") == 0) {{
		if (strcmp(argv[2], "Y") == 0) {{
			jailbreak();
			activate();
			unlock();
		}}
	}}
	
	if (strcmp(argv[1], "-Z") == 0) {{
		if (strcmp(argv[2], "N") == 0) {{
			jailbreak();
			activate();
		}}
	}}
	
	
for (size_t i = 1; i < args.size(); ++i) {

	if (args[i] == "-sc") {
	
	cout << "Type a command and press return:" << endl;
		scanf("%2000[^\n]", sendcommand);
		strcat(sendcommand, "\n");
	
	cout << "Sending command:" << sendcommand << endl;
	if ((code = conn.SendCommand(sendcommand)) != IB_SUCCESS)
	{
		cout << errcode_to_str(code) << endl;
		disconnected();
		return(1);
	}

	if ((code = conn.GetResponse(sendcommandresponse)) != IB_SUCCESS)
	{
		cout << errcode_to_str(code) << endl;
		disconnected();
		return 1;
	}

	cout << "Connected device says: " << sendcommandresponse << endl;
	disconnected();
		return 0;
  
}

		code = conn.SendCommand("setpicture 0\n");
		code = conn.SendCommand("bgcolor 0 0 64\n");
		code = conn.SendCommand("setenv auto-boot true\n");

	if (args[i] == "-N") {
		exit_recovery();
		disconnected();
		return(0);
	}
	if (args[i] == "-r") {
		reset_wifi_mac_address();
	}
	if (args[i] == "-v") {
		verbose_args();
	    disconnected();
		return(0);
	}
	if (args[i] == "-D") {
		enter_dfu();
		disconnected();
		return(0);
	}
	if (args[i] == "-j") {
		jailbreak();
	}
	if (args[i] == "-a") {
		activate();
	}
	if (args[i] == "-b") {
	downgrade_baseband_bootloader();
	}
	if (args[i] == "-u") {
		unlock();
	}	
	if (args[i] == "-e") {
		erase_baseband();
	}	
	if (args[i] == "-m") {
		if (argc<(i+2)) {
			cout << "To change the WiFi MAC address you must supply the one you desire as an arg after -m."  << endl;
			return(1);
		}
		if ((strlen(argv[i+1])!=17)) {
				cout << "The WiFi MAC address you have given is not 17 characters. Enter a valid WiFi MAC address." << endl;
				return(1);
			}
        
		if (strlen(argv[i+1])==17) {
			strcat(macaddress, "\\");
			strcat(macaddress, argv[i+1]);
			strcat(macaddress, "\\");
			strcat(macaddress, "\n");
			change_wifi_mac_address();
		}
	}

	if (args[i] == "-i") {
		if (argc<(i+2)) {
			cout << "To change the IMEI you must supply the one you desire as an arg after -i."  << endl;
			return(1);
		}
        if ((strlen(argv[i+1])!=16)&&(strlen(argv[i+1])!=15)) {
			cout << "The IMEI you have given is not 15 or 16 characters. Enter a valid IMEI." << endl;
			return(1);
		}
		if (strlen(argv[i+1])==15) {
			strcat(imei, "\\");
			strcat(imei, "0");
			strcat(imei, argv[i+1]);
			strcat(imei, "\\");
			strcat(imei, "\n");	
		}
		if (strlen(argv[i+1])==16) {
			strcat(imei, "\\");
			strcat(imei, argv[i+1]);
			strcat(imei, "\\");
			strcat(imei, "\n");
		}
			change_imei();
	}		
 
  }
  
    ramdisk_hack();
    disconnected();
	return 0;

}
