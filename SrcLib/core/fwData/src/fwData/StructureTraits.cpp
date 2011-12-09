/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2011.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <fwCore/base.hpp>
#include <fwTools/ClassRegistrar.hpp>

#include <fwTools/Factory.hpp>

#include "fwData/StructureTraits.hpp"

REGISTER_BINDING_BYCLASSNAME( ::fwTools::Object, ::fwData::StructureTraits, ::fwData::StructureTraits );

namespace fwData
{
//------------------------------------------------------------------------------

StructureTraits::StructureTraits ()
{
    m_color = ::fwData::Color::New();
}


//------------------------------------------------------------------------------

StructureTraits::~StructureTraits ()
{
}

//------------------------------------------------------------------------------

} // namespace fwData

