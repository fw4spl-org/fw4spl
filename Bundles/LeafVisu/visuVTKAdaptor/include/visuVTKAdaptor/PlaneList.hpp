/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2017.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __VISUVTKADAPTOR_PLANELIST_HPP__
#define __VISUVTKADAPTOR_PLANELIST_HPP__

#ifndef ANDROID

#include "visuVTKAdaptor/config.hpp"
#include "visuVTKAdaptor/MeshFactory.hpp"

#include <fwCom/helper/SigSlotConnection.hpp>

#include <fwData/Plane.hpp>

#include <fwRenderVTK/IAdaptor.hpp>

class vtkCommand;

namespace visuVTKAdaptor
{

class VISUVTKADAPTOR_CLASS_API PlaneList : public ::fwRenderVTK::IAdaptor
{

public:

    fwCoreServiceClassDefinitionsMacro( (PlaneList)(::fwRenderVTK::IAdaptor) );

    VISUVTKADAPTOR_API PlaneList() noexcept;

    VISUVTKADAPTOR_API virtual ~PlaneList() noexcept;

    //------------------------------------------------------------------------------

    void setPlaneCollectionId(::fwRenderVTK::SRender::VtkObjectIdType id)
    {
        m_planeCollectionId = id;
    }

    //------------------------------------------------------------------------------

    ::fwRenderVTK::SRender::VtkObjectIdType getPlaneCollectionId() const
    {
        return m_planeCollectionId;
    }

protected:

    /// Type of signal emitted when plane selection changed
    typedef  ::fwCom::Signal< void (::fwData::Plane::sptr) > SelectedignalType;

    VISUVTKADAPTOR_API void doStart();
    VISUVTKADAPTOR_API void doStop();

    VISUVTKADAPTOR_API void doConfigure();
    VISUVTKADAPTOR_API void doSwap();
    VISUVTKADAPTOR_API void doUpdate();

    /// Slot: Update plane selection
    void updateSelection(::fwData::Plane::sptr plane);

    vtkCommand* m_rightButtonCommand;
    ::fwRenderVTK::SRender::VtkObjectIdType m_planeCollectionId;

    /// Store connections to planes adaptors.
    ::fwCom::helper::SigSlotConnection m_planeConnections;

private:
    /**
     * @name Slots
     * @{
     */
    /// Update planes (call doStop-soStart())
    void updatePlanes();

    /// Show/hide planes
    void showPlanes(bool visible);
    /**
     * @}
     */
};

} //namespace visuVTKAdaptor

#endif // ANDROID

#endif // __VISUVTKADAPTOR_PLANELIST_HPP__
