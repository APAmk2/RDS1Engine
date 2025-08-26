#pragma once

//
// Operating system
// RDS1_WINDOWS
// RDS1_LINUX
// RDS1_MACOSX
//
// CPU
// RDS1_X86 - TODO
// RDS1_X64
//
// Compiler
// RDS1_GCC
// RDS1_MSVC
//

// Detect operating system
#if defined ( _WIN32 ) || defined ( _WIN64 )
# define RDS1_WINDOWS
#elif defined ( __linux__ )
# define RDS1_LINUX
#elif defined ( __APPLE__ )
# define RDS1_MACOSX
#else
# error "Unknown operating system."
#endif

// Detect compiler
#if defined ( __GNUC__ )
# define RDS1_GCC
#elif defined ( _MSC_VER ) && !defined ( __MWERKS__ )
# define RDS1_MSVC
#else
# error "Unknown compiler."
#endif

// Detect CPU
#if ( defined ( RDS1_MSVC ) && defined ( _M_IX86 ) ) || ( defined ( RDS1_GCC ) && !defined ( __LP64__ ) )
# define RDS1_X86
# error "X86 CPU not supported for now."
#elif ( defined ( RDS1_MSVC ) && defined ( _M_X64 ) ) || ( defined ( RDS1_GCC ) && defined ( __LP64__ ) )
# define RDS1_X64
#else
# error "Unknown CPU."
#endif

// TLS
#if defined ( RDS1_MSVC )
# define THREAD    __declspec( thread )
#elif defined ( RDS1_GCC )
# define THREAD    __thread
#endif

// Function name
#if defined ( RDS1_MSVC )
# define _FUNC_    __FUNCTION__
#elif defined ( RDS1_GCC )
# define _FUNC_    __PRETTY_FUNCTION__
#endif

// Disable deprecated notification in GCC
#if defined ( RDS1_GCC )
# undef __DEPRECATED
#endif