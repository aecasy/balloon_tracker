#ifndef TEST_POSITION_CONTROL__VISIBILITY_CONTROL_H_
#define TEST_POSITION_CONTROL__VISIBILITY_CONTROL_H_
#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define TEST_POSITION_CONTROL_EXPORT __attribute__ ((dllexport))
    #define TEST_POSITION_CONTROL_IMPORT __attribute__ ((dllimport))
  #else
    #define TEST_POSITION_CONTROL_EXPORT __declspec(dllexport)
    #define TEST_POSITION_CONTROL_IMPORT __declspec(dllimport)
  #endif
  #ifdef TEST_POSITION_CONTROL_BUILDING_LIBRARY
    #define TEST_POSITION_CONTROL_PUBLIC TEST_POSITION_CONTROL_EXPORT
  #else
    #define TEST_POSITION_CONTROL_PUBLIC TEST_POSITION_CONTROL_IMPORT
  #endif
  #define TEST_POSITION_CONTROL_PUBLIC_TYPE TEST_POSITION_CONTROL_PUBLIC
  #define TEST_POSITION_CONTROL_LOCAL
#else
  #define TEST_POSITION_CONTROL_EXPORT __attribute__ ((visibility("default")))
  #define TEST_POSITION_CONTROL_IMPORT
  #if __GNUC__ >= 4
    #define TEST_POSITION_CONTROL_PUBLIC __attribute__ ((visibility("default")))
    #define TEST_POSITION_CONTROL_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define TEST_POSITION_CONTROL_PUBLIC
    #define TEST_POSITION_CONTROL_LOCAL
  #endif
  #define TEST_POSITION_CONTROL_PUBLIC_TYPE
#endif
#endif  // TEST_POSITION_CONTROL__VISIBILITY_CONTROL_H_
// Generated 30-Dec-2025 16:21:20
// Copyright 2019-2020 The MathWorks, Inc.
