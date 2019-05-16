#include "libibooter.h"
#include "abstractfile.c"
#include <unistd.h>
#include <iostream>
#include <vector>
#include <string>
using namespace ibooter;
using namespace std;

char endianness;

void TestByteOrder()
{
	short int word = 0x0001;
	char *byte = (char *) &word;
	endianness = byte[0] ? IS_LITTLE_ENDIAN : IS_BIG_ENDIAN;
}

int main(int argc, char *argv[]) 
{
	const char *pResponse = NULL;
	CIBootConn conn;
	ERR_CODE code;
	//AbstractFile* ramdisk;
	//AbstractFile* igor;
	//AbstractFile* victor;
	//AbstractFile* dfu;

	int i;

	TestByteOrder();

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

        cout << "ZiPhone v3.4 by Zibri. https://ziphone.zibri.org" << endl;
        cout << "Source code available at: http://whitera1n.com" << endl  << endl;

	if(argc < 2) {
  		cout << "Usage: ./ziphone [-b] [-e] [-u] [-a] [-j] [-v] [-D]" << endl;
  		cout << endl;
  		cout << "       -b: Downgrade bootloader 4.6 to 3.9." << endl;
  		cout << "       -u: Unlock iPhone 1.1.4." << endl;
  		cout << "       -a: Activate iPhone." << endl;
  		cout << "       -j: Jailbreak iPhone OR iPod 1.0-1.1.5 and 2.0 beta 2." << endl;
  		cout << "       -e: Downgrade bootloader to 3.9 and erase baseband (for a perfect restore)." << endl;
  		cout << "       -D: Enter DFU Mode on 1.0-1.1.5 (to restore deeply)." << endl;
  		cout << "       -N: Exit Recovery Mode (normal boot)." << endl;  
		cout << "       -v: Debug boot (verbose)." << endl; 
  		cout << endl;
		return 1;
	}



	cout << "Searching for iPhone or iPod Touch..." << endl;
	if ((code = conn.Connect()) != IB_SUCCESS)
	{
        	cout << endl << "ZiPhone can not connect to your iPhone or iPod Touch. Please make sure that:" << endl << endl;
                cout << "Your running ZiPhone as root." << endl;
                cout << "Libusb is installed." << endl;
                cout << "The iPhone or iPod Touch is in Recovery Mode and connected with a USB Dock cable to the computer." << endl;
        	cout << "If your iPhone/iPod Touch is connected, enter it into Recovery Mode now. To do so, unplug the device, hold the power button" << endl;
        	cout << "for a few seconds and then 'slide to power off'.  " << endl;
        	cout << "With the device still powered off, hold the home button down " << endl;
        	cout << "and connect to the dock or cable.  The Apple logo will appear for a few " << endl;
        	cout << "seconds, and finally the 'connect to iTunes' graphic will appear." << endl;
                cout << "Do not release the home button until the 'connect' graphic is visible." << endl << endl;
                cout<< "Try running ZiPhone again at that point." << endl << endl;
		return 1;
	}

	code = conn.SendCommand("setenv auto-boot true\n");
\
	std::vector<std::string> args(argv, argv+argc);
	for (size_t i = 1; i < args.size(); ++i) {
		if (args[i] == "-N") {
		cout << "Booting normal mode..." << endl;
		code = conn.SendCommand("setpicture 0\n");
		code = conn.SendCommand("bgcolor 0 0 64\n");
		code = conn.SendCommand("setenv boot-partition 0\n");
		code = conn.SendCommand("setenv boot-args \"\"\n");
		code = conn.SendCommand("saveenv\n");
		code = conn.SendCommand("fsboot\n");
		cout << "Please wait..." << endl;
		conn.Disconnect();
		return 0;
		}
	}
	
	
	std::vector<std::string> args2(argv, argv+argc);
	for (size_t i = 1; i < args.size(); ++i) {
		if (args2[i] == "-v") {
		cout << "Booting verbose..." << endl;
		code = conn.SendCommand("setpicture 0\n");
		code = conn.SendCommand("bgcolor 0 0 64\n");
		code = conn.SendCommand("setenv boot-partition 0\n");
		code = conn.SendCommand("setenv boot-args \"-v\"\n");
		code = conn.SendCommand("saveenv\n");
		code = conn.SendCommand("fsboot\n");
		return 0;
		}
	}

	std::vector<std::string> args3(argv, argv+argc);
	for (size_t i = 1; i < args.size(); ++i) {
		if (args3[i] == "-D") {
		cout << "Opening dfu.dat..." << endl;
		AbstractFile* dfu = createAbstractFileFromFile(fopen("dfu.dat", "rb"));
			if(!dfu) {
			cout << "Cannot find dfu.dat!" << endl;
			exit(1);
		}

		cout << "Loading dfu.dat..." << endl;
		code = conn.SendCommand("setpicture 0\n");
		code = conn.SendCommand("bgcolor 0 0 64\n");
		code = conn.SendCommand("setenv boot-partition 0\n");
		code = conn.SendCommand("setenv boot-args \"\"\n");
		code = conn.SendFile(dfu, 0x09000000);
		code = conn.SendCommand("go\n");
		cout << "Run iTunes and restore firmware?!" << endl;
		return 0;
		}
	}

	cout << "Opening zibri.dat..." << endl;
	AbstractFile* ramdisk = createAbstractFileFromFile(fopen("zibri.dat", "rb"));
	if(!ramdisk) {
		cout << "Cannot find zibri.dat!" << endl;
		exit(1);
	}

	cout << "Loading zibri.dat..." << endl;
	code = conn.SendFile(ramdisk, 0x09000000);

	cout << "Opening igor.dat..." << endl;
	AbstractFile* igor = createAbstractFileFromFile(fopen("igor.dat", "rb"));
	if(!igor) {
		cout << "Cannot find igor.dat!" << endl;
		exit(1);
	}

	cout << "Loading igor.dat..." << endl;
	code = conn.SendFile(igor, 0x09000000);

	cout << "Opening victor.dat..." << endl;
	AbstractFile* victor = createAbstractFileFromFile(fopen("victor.dat", "rb"));
	if(!victor) {
		cout << "Cannot find victor.dat!" << endl;
		exit(1);
	}

	cout << "Working..." << endl;
	code = conn.SendCommand("setpicture 0\n");
	code = conn.SendCommand("bgcolor 0 0 64\n");
 	
	std::vector<std::string> args4(argv, argv+argc);
	for (size_t i = 1; i < args.size(); ++i) {
		if (args4[i] == "-j") {
		code = conn.SendCommand("setenv jailbreak \"1\"\n");
		}
	}

	std::vector<std::string> args5(argv, argv+argc);
	for (size_t i = 1; i < args.size(); ++i) {
		if (args5[i] == "-a") {
		code = conn.SendCommand("setenv activate \"1\"\n");
		}
	}

	std::vector<std::string> args6(argv, argv+argc);
	for (size_t i = 1; i < args.size(); ++i) {
		if (args6[i] == "-b") {
		code = conn.SendCommand("setenv bl39 \"1\"\n");
		}
	}

	std::vector<std::string> args7(argv, argv+argc);
	for (size_t i = 1; i < args.size(); ++i) {
		if (args7[i] == "-u") {
		code = conn.SendCommand("setenv unlock \"1\"\n");
		}
	}

	std::vector<std::string> args8(argv, argv+argc);
	for (size_t i = 1; i < args.size(); ++i) {
		if (args8[i] == "-e") {
		code = conn.SendCommand("setenv ierase \"1\"\n");
		}
	}

	code = conn.SendCommand("setenv boot-args \"rd=md0 -s -x pmd0=0x09CC2000.0x0133D000\"\n");

	code = conn.SendCommand("saveenv\n");
	code = conn.SendCommand("bootx\n");
	sleep(5);
	code = conn.SendFile(victor, 0x09000000);
	code = conn.SendCommand("bootx\n");
	sleep(5);
	code = conn.SendCommand("fsboot\n");
	cout << "Please wait..." << endl;

	return 0;
}
