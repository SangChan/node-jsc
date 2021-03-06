// Copyright 2012 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This module contains the platform-specific code. This make the rest of the
// code less dependent on operating system, compilers and runtime libraries.
// This module does specifically not deal with differences between different
// processor architecture.
// The platform classes have the same definition for all platforms. The
// implementation for a particular platform is put in platform_<os>.cc.
// The build system then uses the implementation for the target platform.
//
// This design has been chosen because it is simple and fast. Alternatively,
// the platform dependent classes could have been implemented using abstract
// superclasses with virtual methods and having specializations for each
// platform. This design was rejected because it was more complicated and
// slower. It would require factory methods for selecting the right
// implementation and the overhead of virtual methods for performance
// sensitive like mutex locking/unlocking.

#ifndef V8_BASE_PLATFORM_PLATFORM_H_
#define V8_BASE_PLATFORM_PLATFORM_H_

#include "wtf/Assertions.h"

#ifndef PRINTF_FORMAT
#define PRINTF_FORMAT WTF_ATTRIBUTE_PRINTF
#endif

namespace v8 {
namespace base {

class OS {
public:
	static PRINTF_FORMAT(3, 4) int SNPrintF(char* str, int length,
											const char* format, ...)
	{
		va_list args;
		va_start(args, format);
		int result = VSNPrintF(str, length, format, args);
		va_end(args);
		return result;
	}

	static PRINTF_FORMAT(3, 0) int VSNPrintF(char* str, int length,
                                             const char* format, va_list args)
	{
#ifdef WIN32
		int n = _vsnprintf_s(str, length, _TRUNCATE, format, args);
#else
		int n = vsnprintf(str, length, format, args);
#endif
		if (n < 0 || n >= length) {
			// If the length is zero, the assignment fails.
			if (length > 0) {
				str[length - 1] = '\0';
			}
			return -1;
		}
		else {
			return n;
		}
	}

};

}  // namespace base
}  // namespace v8

#endif  // V8_BASE_PLATFORM_PLATFORM_H_