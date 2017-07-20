/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2017.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __VISUVTKADAPTOR_LABELEDPOINTLIST_HPP__
#define __VISUVTKADAPTOR_LABELEDPOINTLIST_HPP__

#include "visuVTKAdaptor/config.hpp"

#include <fwData/Color.hpp>

#include <fwRenderVTK/IAdaptor.hpp>

class vtkCommand;

namespace visuVTKAdaptor
{
/**
 * @brief Adaptor to display a labeled point list
 *
 * @code{.xml}
      <adaptor id="..." class="::visuVTKAdaptor::LabeledPointList" objectId="self">
        <config renderer="default" picker="..." color="#FFFFFF" radius="10" interaction="on"/>
      </adaptor>
     @endcode
 * @subsection Configuration Configuration
 * - \b renderer : defines the renderer to show the labeled point list.
 * - \b picker : defines the picker of the labeled point list.
 * - \b color(#FFFFFF) : color of the points.
 * - \b radius(double) : points radius.
 * - \b interaction (optional, default: on): if "on" interactions are enabled
 */
class VISUVTKADAPTOR_CLASS_API LabeledPointList : public ::fwRenderVTK::IAdaptor
{

public:

    fwCoreServiceClassDefinitionsMacro( (LabeledPointList)(::fwRenderVTK::IAdaptor) );

    VISUVTKADAPTOR_API LabeledPointList() noexcept;

    VISUVTKADAPTOR_API virtual ~LabeledPointList() noexcept;

    /**
     * @brief Returns proposals to connect service slots to associated object signals,
     * this method is used for obj/srv auto connection
     *
     * Connect PointList::s_MODIFIED_SIG to this::s_UPDATE_SLOT
     * Connect PointList::s_POINT_ADDED_SIG to this::s_UPDATE_SLOT
     * Connect PointList::s_POINT_REMOVED_SIG to this::s_UPDATE_SLOT
     */
    VISUVTKADAPTOR_API virtual KeyConnectionsType getObjSrvConnections() const;

protected:

    VISUVTKADAPTOR_API void doStart();
    VISUVTKADAPTOR_API void doStop();

    VISUVTKADAPTOR_API void doConfigure();
    VISUVTKADAPTOR_API void doSwap();
    VISUVTKADAPTOR_API void doUpdate();

    std::list< ::fwRenderVTK::IAdaptor::sptr > m_subServices;

    vtkCommand* m_rightButtonCommand;

    /// Points color
    ::fwData::Color::sptr m_ptColor;

    /// Points radius
    double m_radius;

    /// If true, the interactions are enabled
    bool m_interaction;
};

} //namespace visuVTKAdaptor

#endif // __VISUVTKADAPTOR_LABELEDPOINTLIST_HPP__
