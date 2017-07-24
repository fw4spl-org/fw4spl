/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2017.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#ifndef __FWRENDERQT_IADAPTOR_HPP__
#define __FWRENDERQT_IADAPTOR_HPP__

#include "fwRenderQt/config.hpp"
#include "fwRenderQt/data/Axis.hpp"
#include "fwRenderQt/data/Event.hpp"
#include "fwRenderQt/SRender.hpp"

#include <fwServices/IService.hpp>

namespace fwRenderQt
{

/**
 * @brief Root class for all scene2d adaptors.
 */
class FWRENDERQT_CLASS_API IAdaptor : public ::fwServices::IService
{

public:

    /// Point2D coordinate <X, Y>
    typedef std::pair< double, double > Point2DType;

    /// <width, height>
    typedef std::pair<float, float> ViewSizeRatio;

    /// <width, height>
    typedef std::pair<float, float> ViewportSizeRatio;

    /// <width, height>
    typedef std::pair<float, float> Scene2DRatio;

    fwCoreServiceClassDefinitionsMacro( (IAdaptor)(::fwServices::IService) );

    /// Set the zValue.
    FWRENDERQT_API void setZValue(float _zValue);

    /// Get the zValue.
    FWRENDERQT_API float getZValue() const;

    /// Get the render that manages the IAdaptor.
    FWRENDERQT_API SPTR(::fwRenderQt::SRender) getScene2DRender() const;

    /// Interact with the mouse events catched on the IAdaptor
    /// (virtual function, its behavior is only defined in the specific adaptors).
    FWRENDERQT_API virtual void processInteraction(::fwRenderQt::data::Event& _event );

protected:

    /// Constructor, set the zValue to 0.
    FWRENDERQT_API IAdaptor() noexcept;

    /// Basic destructor, do nothing.
    FWRENDERQT_API virtual ~IAdaptor() noexcept;

    /// ToDo IM
    FWRENDERQT_API virtual void info(std::ostream& _sstream );

    /// Not implemented in IAdaptor but in its subclasses
    FWRENDERQT_API void configuring();

    /// Call doStart() function.
    FWRENDERQT_API void starting();

    /// Call DoUpdate() function.
    FWRENDERQT_API void updating();

    /// Start and stop the IAdaptor.
    FWRENDERQT_API void swapping();

    /// Call doStop() function and reset the axis.
    FWRENDERQT_API void stopping();

    /// Pure virtual -> implemented in the subclasses
    FWRENDERQT_API virtual void doStart() = 0;

    /// Pure virtual -> implemented in the subclasses
    FWRENDERQT_API virtual void doUpdate() = 0;

    /// Pure virtual -> implemented in the subclasses
    FWRENDERQT_API virtual void doSwap() = 0;

    /// Pure virtual -> implemented in the subclasses
    FWRENDERQT_API virtual void doStop() = 0;

    /// Get a pair of doubles (a point), two axis, and convert the pair of doubles values from adaptor
    /// coordinates to scene coordinates
    FWRENDERQT_API Point2DType mapAdaptorToScene(const Point2DType& _xy,
                                                 const ::fwRenderQt::data::Axis::sptr& _xAxis,
                                                 const ::fwRenderQt::data::Axis::sptr& _yAxis) const;

    /// Get a pair of doubles (a point), two axis, and convert the pair of doubles values from scene
    /// coordinates to adaptor coordinates
    FWRENDERQT_API Point2DType mapSceneToAdaptor(const Point2DType& _xy,
                                                 const ::fwRenderQt::data::Axis::sptr& _xAxis,
                                                 const ::fwRenderQt::data::Axis::sptr& _yAxis) const;

    /// Return the ratio between view's initial size and its current size
    FWRENDERQT_API ViewSizeRatio getViewSizeRatio() const;

    /// Return the ratio between viewport's initial size and its current size
    FWRENDERQT_API ViewportSizeRatio getViewportSizeRatio() const;

    /// Initialize the source values used for computing view's size ratio.
    FWRENDERQT_API void initializeViewSize();

    /// Initialize the source values used for computing viewport's size ratio.
    FWRENDERQT_API void initializeViewportSize();

    FWRENDERQT_API Scene2DRatio getRatio() const;

    /// The x Axis.
    ::fwRenderQt::data::Axis::sptr m_xAxis;

    /// The y Axis.
    ::fwRenderQt::data::Axis::sptr m_yAxis;

    /// The adaptor zValue (depth within the scene).
    /// The adaptor with the highest zValue is displayed on top of all adaptors.
    float m_zValue;

    /// Opacity of the adaptor. Default value set to 1 (opaque).
    float m_opacity;

    /// Initial size of the widget (view). The goal of keeping a reference on the initial size is to
    /// avoid unwanted scaling onto some objects (such as transfer function points, histogram cursor,
    /// etc) when a resize event is caught.
    ViewSizeRatio m_viewInitialSize;

    /// Initial size of the viewport. The goal of keeping a reference on the initial size of the
    /// viewport is the same as preceding.
    ViewportSizeRatio m_viewportInitialSize;

    typedef std::vector< ::fwRenderQt::IAdaptor::wptr > ManagedAdaptorVector;

    /// Return all managed adaptor
    const ManagedAdaptorVector& getRegisteredServices() const
    {
        return m_managedAdaptors;
    }

    /// Register new adaptor
    FWRENDERQT_API void registerService( ::fwRenderQt::IAdaptor::sptr srv );

    /// Unregister all adaptors
    FWRENDERQT_API void unregisterServices();

    template< class DATATYPE >
    SPTR(DATATYPE) getSafeInOut(const std::string& key) const;

private:

    /// Register automatic connection on object
    ::fwCom::helper::SigSlotConnection m_connections;

    /// All managed adaptors
    ManagedAdaptorVector m_managedAdaptors;
};

//------------------------------------------------------------------------------

template< class DATATYPE >
SPTR(DATATYPE) IAdaptor::getSafeInOut(const std::string& key) const
{
    if( ::fwServices::IService::isVersion2() )
    {
        return this->getScene2DRender()->getInOut<DATATYPE>(key);
    }
    else
    {
        return std::dynamic_pointer_cast<DATATYPE>( ::fwTools::fwID::getObject(key) );
    }
}

//------------------------------------------------------------------------------

} // namespace fwRenderQt

#endif // __FWRENDERQT_IADAPTOR_HPP__

