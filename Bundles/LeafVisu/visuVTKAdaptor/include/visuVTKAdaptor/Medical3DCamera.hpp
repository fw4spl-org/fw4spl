/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2017.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __VISUVTKADAPTOR_MEDICAL3DCAMERA_HPP__
#define __VISUVTKADAPTOR_MEDICAL3DCAMERA_HPP__

#include "visuVTKAdaptor/config.hpp"

#include <fwCom/Slot.hpp>
#include <fwCom/Slots.hpp>

#include <fwDataTools/helper/MedicalImageAdaptor.hpp>

#include <fwRenderVTK/IAdaptor.hpp>

class vtkCamera;

namespace visuVTKAdaptor
{

/**
 * @brief Update camera scene according to defined axes (axial, sagittal, frontal).
 *
 * The scene can be updated using adaptor slots setAxial, setFrontal, setSagittal.
 */
class VISUVTKADAPTOR_CLASS_API Medical3DCamera : public ::fwDataTools::helper::MedicalImageAdaptor,
                                                 public ::fwRenderVTK::IAdaptor
{
public:

    fwCoreServiceClassDefinitionsMacro( (Medical3DCamera)(::fwRenderVTK::IAdaptor) );

    VISUVTKADAPTOR_API Medical3DCamera() noexcept;

    VISUVTKADAPTOR_API virtual ~Medical3DCamera() noexcept;

    typedef ::fwCom::Slot< void () > SetCameraSlotType;

protected:

    /**
     * @brief Configure the adaptor
     *
     * Example :
       @code{.xml}
       <adaptor id="medicalCamera" class="::visuVTKAdaptor::Medical3DCamera" objectId="object">
        <config renderer="default" sliceIndex="axial" resetAtStart="yes" />
       </adaptor>

       ...

       <connect>
        <signal>guiActionAxialView/triggered</signal>
        <slot>medicalCamera/setAxial</slot> <!-- Connect to adaptor's axial view slot -->
       </connect>

       @endcode
     *
     * - renderer : mandatory, renderer used by the adaptor
     * - sliceIndex : not mandatory, defines view orientation. Available values are axial, frontal, sagittal;
     *   default value set to axial.
     * - resetAtStart : update view when adaptor is started if set to yes, default value is no.
     *
     */
    VISUVTKADAPTOR_API void doConfigure();

    /**
     * @name Overrides
     * @{ */
    VISUVTKADAPTOR_API void doStart();
    VISUVTKADAPTOR_API void doStop();
    VISUVTKADAPTOR_API void doSwap();
    VISUVTKADAPTOR_API void doUpdate();
    /**  @} */

private:
    void updateView();
    void resetSagittalView();
    void resetFrontalView();
    void resetAxialView();

    void setSagittalView();
    void setFrontalView();
    void setAxialView();

    vtkCamera* m_camera;
    static std::map< std::string, ::fwDataTools::helper::MedicalImageAdaptor::Orientation > m_orientationConversion;

    /// Set axial view slot.
    SetCameraSlotType::sptr m_slotSetAxial;

    /// Set sagittal view slot.
    SetCameraSlotType::sptr m_slotSetSagittal;

    /// Set frontal view slot.
    SetCameraSlotType::sptr m_slotSetFrontal;

    /// Update view when adaptor is started if true
    bool m_resetAtStart;
};

} //namespace visuVTKAdaptor

#endif // __VISUVTKADAPTOR_MEDICAL3DCAMERA_HPP__
