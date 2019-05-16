/*

Copyright (C) 2007  iPhoneDev Team ( http://iphone.fiveforty.net/wiki/ )

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>

*/

/**
 * privateFunctions.h - Provides a mechanism for defining, initing
 *                      and accessing private DLL functions
 */

#if !defined(PRIVATEFUNCTIONS_H)
#define PRIVATEFUNCTIONS_H

#include "MobileDevice.h"

#if defined(WIN32)
//	void wCFShow(CFTypeRef tested);
#endif

//void GhettoCFStringPrint(CFStringRef str);
//void hexdump(void *memloc, int len);
//void describe255(CFTypeRef tested);
//inline bool is_base64(unsigned char c);
//string base64_decode(string const& encoded_string);
/////////////////////////////////////////////////////

int initPrivateFunctions();
int sendCommandToDevice(am_recovery_device *rdev, CFStringRef cfs);
int sendFileToDevice(am_recovery_device *rdev, CFStringRef filename);
int performOperation(am_restore_device *rdev, CFMutableDictionaryRef message);
int socketForPort(am_restore_device *rdev, unsigned int portnum);

#endif // PRIVATEFUNCTIONS_H
