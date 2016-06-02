/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2016.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include <fwServices/macros.hpp>

#include <fwTools/fwID.hpp>

#include "fwServices/SConfigController.hpp"

namespace fwServices
{

//------------------------------------------------------------------------------

fwServicesRegisterMacro( ::fwServices::IController, ::fwServices::SConfigController, ::fwData::Object );

//------------------------------------------------------------------------------

SConfigController::SConfigController() throw()
{
    m_configLauncher = ::fwServices::helper::ConfigLauncher::New();
}

//------------------------------------------------------------------------------

SConfigController::~SConfigController() throw()
{
}

//------------------------------------------------------------------------------

void SConfigController::starting() throw(::fwTools::Failed)
{
    m_configLauncher->startConfig(this->getSptr());
}

//------------------------------------------------------------------------------

void SConfigController::stopping() throw(::fwTools::Failed)
{
    m_configLauncher->stopConfig();
}

//------------------------------------------------------------------------------

void SConfigController::swapping() throw(::fwTools::Failed)
{
    m_configLauncher->stopConfig();
    m_configLauncher->startConfig(this->getSptr());
}

//------------------------------------------------------------------------------

void SConfigController::configuring() throw(fwTools::Failed)
{
    m_configLauncher->parseConfig(this->getConfigTree());
}

//------------------------------------------------------------------------------

void SConfigController::updating() throw(::fwTools::Failed)
{
}

//------------------------------------------------------------------------------

void SConfigController::info( std::ostream &_sstream )
{
}

//------------------------------------------------------------------------------

}

