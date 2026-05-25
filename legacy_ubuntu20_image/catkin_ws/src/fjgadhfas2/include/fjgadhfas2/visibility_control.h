#ifndef FJGADHFAS2__VISIBILITY_CONTROL_H_
#define FJGADHFAS2__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define FJGADHFAS2_EXPORT __attribute__ ((dllexport))
    #define FJGADHFAS2_IMPORT __attribute__ ((dllimport))
  #else
    #define FJGADHFAS2_EXPORT __declspec(dllexport)
    #define FJGADHFAS2_IMPORT __declspec(dllimport)
  #endif
  #ifdef FJGADHFAS2_BUILDING_LIBRARY
    #define FJGADHFAS2_PUBLIC FJGADHFAS2_EXPORT
  #else
    #define FJGADHFAS2_PUBLIC FJGADHFAS2_IMPORT
  #endif
  #define FJGADHFAS2_PUBLIC_TYPE FJGADHFAS2_PUBLIC
  #define FJGADHFAS2_LOCAL
#else
  #define FJGADHFAS2_EXPORT __attribute__ ((visibility("default")))
  #define FJGADHFAS2_IMPORT
  #if __GNUC__ >= 4
    #define FJGADHFAS2_PUBLIC __attribute__ ((visibility("default")))
    #define FJGADHFAS2_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define FJGADHFAS2_PUBLIC
    #define FJGADHFAS2_LOCAL
  #endif
  #define FJGADHFAS2_PUBLIC_TYPE
#endif
#endif  // FJGADHFAS2__VISIBILITY_CONTROL_H_
// Generated 15-Jan-2026 18:30:47
// Copyright 2019-2020 The MathWorks, Inc.
