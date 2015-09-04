// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file WriterSkel.h 
 * @brief Writer server skeleton header wrapper code
 * @date Sat Sep 06 20:54:48 2014 
 *
 */

#ifndef _WRITERSKEL_H
#define _WRITERSKEL_H



#include <rtm/config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#if   defined ORB_IS_TAO
#  include "WriterC.h"
#  include "WriterS.h"
#elif defined ORB_IS_OMNIORB
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#    undef USE_stub_in_nt_dll
#  endif
#  include "Writer.hh"
#elif defined ORB_IS_MICO
#  include "Writer.h"
#elif defined ORB_IS_ORBIT2
#  include "/Writer-cpp-stubs.h"
#  include "/Writer-cpp-skels.h"
#elif defined ORB_IS_RTORB
#  include "Writer.h"
#else
#  error "NO ORB defined"
#endif

#endif // _WRITERSKEL_H
