/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWCORE_HIRESCLOCK_HPP__
#define __FWCORE_HIRESCLOCK_HPP__

#include "fwCore/config.hpp"

namespace fwCore
{


/**
 * @brief This namespace provides several function that returns a hi
 * resolution EPOCH time.
 *
 * @warning EPOCH time has not the same reference on each operating
 * system.
 */
namespace HiResClock
{

/**
 * @brief Type returned by HiResClock Functions
 */
typedef double HiResClockType;


/**
 * @return EPOCH time in microseconds
 */
FWCORE_API HiResClockType getTimeInMicroSec();

/**
 * @return EPOCH time in milliseconds
 */
FWCORE_API HiResClockType getTimeInMilliSec();

/**
 * @return EPOCH time in seconds
 */
FWCORE_API HiResClockType getTimeInSec();


} //namespace HiResClock

} //namespace fwCore

#endif // __FWCORE_HIRESCLOCK_HPP__
