/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2015.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "BooleanTest.hpp"

#include <fwAtoms/Boolean.hpp>

#include <limits>



CPPUNIT_TEST_SUITE_REGISTRATION( ::fwAtoms::ut::BooleanTest );

namespace fwAtoms
{
namespace ut
{

void BooleanTest::setUp()
{
    // Set up context before running a test.
}

//-----------------------------------------------------------------------------

void BooleanTest::tearDown()
{
    // Clean up after the test run.
}


void BooleanTest::conversion()
{
    const bool VALUES[] = {true, false};

    ::fwAtoms::Boolean::sptr meta;

    for ( bool BOOL : VALUES )
    {
        std::string res = BOOL ? "true" : "false";

        meta = ::fwAtoms::Boolean::New(BOOL);

        CPPUNIT_ASSERT_EQUAL(res, meta->getString());
    }
}


}  // namespace ut
}  // namespace fwAtoms

