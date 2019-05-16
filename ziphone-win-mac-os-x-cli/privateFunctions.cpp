/**
 * privateFunctions.cpp - Provides a mechanism for defining, initing
 *                        and accessing private DLL functions
 */
 
#if defined(WIN32)
	#define WIN_32_LEAN_AND_MEAN
	#include <windows.h>
#endif

#include <iostream>
#include "privateFunctions.h"

#if defined(__APPLE__)
	#include <dlfcn.h>
#endif

using namespace std;

#if defined(WIN32)
typedef int (__cdecl * cmdsend)  (am_recovery_device *, CFStringRef) __attribute__ ((cdecl));
typedef int (__cdecl * rcmdsend) (am_restore_device  *, CFMutableDictionaryRef) __attribute__ ((cdecl));
typedef int (__cdecl * ricmdsend)(am_restore_device  *, unsigned int) __attribute__ ((cdecl));
#else
typedef int (*cmdsend)  (am_recovery_device *, CFStringRef) __attribute__ ((regparm(2)));
typedef int (*rcmdsend) (am_restore_device  *, CFMutableDictionaryRef) __attribute__ ((regparm(2)));
typedef int (*ricmdsend)(am_restore_device  *, unsigned int) __attribute__ ((regparm(2)));
#endif

static cmdsend   priv_sendCommandToDevice;
static cmdsend   priv_sendFileToDevice;
static rcmdsend  priv_performOperation;
static ricmdsend priv_socketForPort;

int initPrivateFunctions() {

//	cout << "Architecture: ";

#if defined(WIN32) 

//	cout << "win32 " << endl;

	//get sendCommandToDevice function pointer from dll
	HMODULE hGetProcIDDLL;
	if(!(hGetProcIDDLL = GetModuleHandle("iTunesMobileDevice.dll"))) {
		cout << "Could not find dll in memory" << endl;
		return EXIT_FAILURE;
	}

	//int __usercall sendCommandToDevice<eax>(AMRecoveryModeDevice *amrecd<esi>,void *cfsCommand) @ +00009290
	priv_sendCommandToDevice = (cmdsend) ((char *) hGetProcIDDLL + 0x00009290);

	//int __usercall sendFileToDevice<eax>(AMRecoveryModeDevice *amrd<ecx>,void *filename) @ +00009410
	priv_sendFileToDevice = (cmdsend) ((char *) hGetProcIDDLL + 0x00009410);

	//int __usercall performOperation<eax>(AMRestoreModeDevice *device<esi>,void *message<ebx>) @ +000129C0
	priv_performOperation = (rcmdsend) ((char *) hGetProcIDDLL + 0x000129C0);

	//socketForPort(am_restore_device *rdev, unsigned int portnum) +00012830
	priv_socketForPort= (ricmdsend) ((char *) hGetProcIDDLL + 0x00012830);

#elif defined(__APPLE__)
//	cout << "apple/";
    // nm /System/Library/PrivateFrameworks/MobileDevice.framework/Versions/A/MobileDevice |
    //      egrep -e "(sendFileToDevice|performOperation|socketForPort|sendCommandToDevice)"
	// INTEL PRE-7.4:
    // 3c39fa4b t __performOperation
    // 3c3a3e3b t __sendCommandToDevice
    // 3c3a4087 t __sendFileToDevice
    // 3c39f36c t __socketForPort
	// PPC PRE-7.4:
    // 3c3a0e14 t __performOperation
    // 3c3a517c t __sendCommandToDevice
    // 3c3a52dc t __sendFileToDevice
    // 3c3a0644 t __socketForPort

#if defined(__POWERPC__)
	cout << "ppc" << endl;

	priv_sendCommandToDevice = (cmdsend)(0x3c3a5bb0);
	priv_sendFileToDevice = (cmdsend)(0x3c3a5d10);
	priv_performOperation = (rcmdsend)(0x3c3a0bc8);
	priv_socketForPort = (ricmdsend)(0x3c3a051c);
#else
	cout << "i386" << endl;
	priv_sendCommandToDevice = (cmdsend)(0x3c3a597f);
	priv_sendFileToDevice = (cmdsend)(0x3c3a5bcb);
	priv_performOperation = (rcmdsend)(0x3c3a0599);
	priv_socketForPort = (ricmdsend)(0x3c39ffa3);
#endif

#endif
	return EXIT_SUCCESS;
}

int sendCommandToDevice(am_recovery_device *rdev, CFStringRef cfs) {
	int retval=0;
#if defined (WIN32)
	asm("movl %3, %%esi\n\tpush %1\n\tcall *%0\n\tmovl %%eax, %2"
		:
		:"m"(priv_sendCommandToDevice),  "m"(cfs), "m"(retval), "m"(rdev)
		:);
#elif defined (__APPLE__)
	retval = priv_sendCommandToDevice(rdev, cfs);
#endif
    return retval;
}

int sendFileToDevice(am_recovery_device *rdev, CFStringRef filename) {
	int retval=0;
#if defined (WIN32)
	asm("movl %3, %%ecx\n\tpush %1\n\tcall *%0\n\tmovl %%eax, %2"
		:
		:"m"(priv_sendFileToDevice),  "m"(filename), "m"(retval), "m"(rdev)
		:);
#elif defined (__APPLE__)
	retval = priv_sendFileToDevice(rdev, filename);
#endif
	return retval;
}

int performOperation(am_restore_device *rdev, CFMutableDictionaryRef message) {
	int retval=0;
#if defined (WIN32)
	asm("movl %3, %%esi\n\tmovl %1, %%ebx\n\tcall *%0\n\tmovl %%eax, %2"
		:
		:"m"(priv_performOperation),  "m"(message), "m"(retval), "m"(rdev)
		:);
#elif defined (__APPLE__)
	retval = priv_performOperation(rdev, message);
#endif
	return retval;
}

int socketForPort(am_restore_device *rdev, unsigned int portnum) {
 	int retval=0;
#if defined(WIN32) || defined(__APPLE__)
 	retval = priv_socketForPort(rdev, portnum);
#endif
    return retval;
}
