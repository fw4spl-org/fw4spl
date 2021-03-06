/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWDATACAMP_UT_DATACAMPHELPER_HPP__
#define __FWDATACAMP_UT_DATACAMPHELPER_HPP__

#include <fwData/Object.hpp>

namespace DataCampHelper
{
typedef std::vector<std::string> PropertiesNameType;

void visitProperties(const std::string& className, const PropertiesNameType& vecProp);

void compareSimplePropertyValue(::fwData::Object::sptr obj,
                                const std::string& propertyPath,
                                const std::string& value);

void compareObjectPropertyValue(::fwData::Object::sptr obj,
                                const std::string& propertyPath,
                                ::fwData::Object::sptr value);
}

#endif // __FWDATACAMP_UT_DATACAMPHELPER_HPP__
