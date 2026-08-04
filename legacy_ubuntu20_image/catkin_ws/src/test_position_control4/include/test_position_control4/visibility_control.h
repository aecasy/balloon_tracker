#ifndef TEST_POSITION_CONTROL4__VISIBILITY_CONTROL_H_
#define TEST_POSITION_CONTROL4__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define TEST_POSITION_CONTROL4_EXPORT __attribute__ ((dllexport))
    #define TEST_POSITION_CONTROL4_IMPORT __attribute__ ((dllimport))
  #else
    #define TEST_POSITION_CONTROL4_EXPORT __declspec(dllexport)
    #define TEST_POSITION_CONTROL4_IMPORT __declspec(dllimport)
  #endif
  #ifdef TEST_POSITION_CONTROL4_BUILDING_LIBRARY
    #define TEST_POSITION_CONTROL4_PUBLIC TEST_POSITION_CONTROL4_EXPORT
  #else
    #define TEST_POSITION_CONTROL4_PUBLIC TEST_POSITION_CONTROL4_IMPORT
  #endif
  #define TEST_POSITION_CONTROL4_PUBLIC_TYPE TEST_POSITION_CONTROL4_PUBLIC
  #define TEST_POSITION_CONTROL4_LOCAL
#else
  #define TEST_POSITION_CONTROL4_EXPORT __attribute__ ((visibility("default")))
  #define TEST_POSITION_CONTROL4_IMPORT
  #if __GNUC__ >= 4
    #define TEST_POSITION_CONTROL4_PUBLIC __attribute__ ((visibility("default")))
    #define TEST_POSITION_CONTROL4_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define TEST_POSITION_CONTROL4_PUBLIC
    #define TEST_POSITION_CONTROL4_LOCAL
  #endif
  #define TEST_POSITION_CONTROL4_PUBLIC_TYPE
#endif
#endif  // TEST_POSITION_CONTROL4__VISIBILITY_CONTROL_H_
// Generated 15-Jan-2026 17:47:16
// Copyright 2019-2020 The MathWorks, Inc.
