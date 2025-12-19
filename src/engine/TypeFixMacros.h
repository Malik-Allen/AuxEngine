// MIT License, Copyright (c) 2025 Malik Allen

#ifndef AUXENGINE_TYPE_FIX_MACROS_H
#define AUXENGINE_TYPE_FIX_MACROS_H

// 'byte': ambiguous symbol error occurs because recent standard introduced::std::byte and ::byte types which will clash with byte type defined in rpcndr.h :
// 
// <cstddef>
// enum class byte : unsigned char {};
// 
// <rpcndr.h>
// typedef unsigned char byte;
// 
// But that is not the only problem with windows headers, they also introduce min and max macros(required by gdiplus) that clash with <limits> content.
// https://stackoverflow.com/questions/45957830/gdipluspath-throws-ambiguous-byte-for-cstddef-and-rpcndr-h

// global compilation flag configuring windows sdk headers
// preventing inclusion of min and max macros clashing with <limits>
#define NOMINMAX 1

//  override byte to prevent clashes with <cstddef>
#define byte win_byte_override

#include <Windows.h> // gdi plus requires Windows.h
// ...includes for other windows header that may use byte...

//  Define min max macros required by GDI+ headers.
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#else
#error max macro is already defined
#endif
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#else
#error min macro is already defined
#endif

#include <gdiplus.h>

//  Undefine min max macros so they won't collide with <limits> header content.
#undef min
#undef max

//  Undefine byte macros so it won't collide with <cstddef> header content.
#undef byte


#endif // !AUXENGINE_TYPE_FIX_MACROS_H