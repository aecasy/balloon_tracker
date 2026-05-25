#ifndef FJGADHFAS__VISIBILITY_CONTROL_H_
#define FJGADHFAS__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define FJGADHFAS_EXPORT __attribute__ ((dllexport))
    #define FJGADHFAS_IMPORT __attribute__ ((dllimport))
  #else
    #define FJGADHFAS_EXPORT __declspec(dllexport)
    #define FJGADHFAS_IMPORT __declspec(dllimport)
  #endif
  #ifdef FJGADHFAS_BUILDING_LIBRARY
    #define FJGADHFAS_PUBLIC FJGADHFAS_EXPORT
  #else
    #define FJGADHFAS_PUBLIC FJGADHFAS_IMPORT
  #endif
  #define FJGADHFAS_PUBLIC_TYPE FJGADHFAS_PUBLIC
  #define FJGADHFAS_LOCAL
#else
  #define FJGADHFAS_EXPORT __attribute__ ((visibility("default")))
  #define FJGADHFAS_IMPORT
  #if __GNUC__ >= 4
    #define FJGADHFAS_PUBLIC __attribute__ ((visibility("default")))
    #define FJGADHFAS_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define FJGADHFAS_PUBLIC
    #define FJGADHFAS_LOCAL
  #endif
  #define FJGADHFAS_PUBLIC_TYPE
#endif
#endif  // FJGADHFAS__VISIBILITY_CONTROL_H_
// Generated 15-Jan-2026 18:04:55
// Copyright 2019-2020 The MathWorks, Inc.
