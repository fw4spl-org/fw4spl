/* ***** BEGIN LICENSE BLOCK *****
 * FW4SPL - Copyright (C) IRCAD, 2009-2018.
 * Distributed under the terms of the GNU Lesser General Public License (LGPL) as
 * published by the Free Software Foundation.
 * ****** END LICENSE BLOCK ****** */

#include "opImageFilter/SThreshold.hpp"

#include <fwCom/Signal.hpp>
#include <fwCom/Signal.hxx>

#include <fwData/Image.hpp>

#include <fwDataTools/helper/Image.hpp>
#include <fwDataTools/helper/ImageGetter.hpp>

#include <fwMedData/ImageSeries.hpp>

#include <fwServices/macros.hpp>

#include <fwTools/Dispatcher.hpp>
#include <fwTools/DynamicTypeKeyTypeMapping.hpp>
#include <fwTools/fwID.hpp>
#include <fwTools/IntrinsicTypes.hpp>

namespace opImageFilter
{

//-----------------------------------------------------------------------------

static const std::string s_IMAGE_INPUT  = "source";
static const std::string s_IMAGE_OUTPUT = "target";

//-----------------------------------------------------------------------------

SThreshold::SThreshold() noexcept :
    m_threshold(50.0)
{
}

//-----------------------------------------------------------------------------

SThreshold::~SThreshold() noexcept
{
}

//-----------------------------------------------------------------------------

void SThreshold::starting()
{
}

//-----------------------------------------------------------------------------

void SThreshold::stopping()
{
}

//-----------------------------------------------------------------------------

void SThreshold::configuring()
{
    const ::fwServices::IService::ConfigType& srvConfig = this->getConfigTree();

    SLM_ASSERT("You must have one <config/> element.", srvConfig.count("config") == 1 );

    const ::fwServices::IService::ConfigType& config = srvConfig.get_child("config");

    SLM_ASSERT("You must have one <threshold/> element.", config.count("threshold") == 1);
    const ::fwServices::IService::ConfigType& thresholdCfg = config.get_child("threshold");
    m_threshold = thresholdCfg.get_value<double>();
}

//-----------------------------------------------------------------------------

/**
 * Functor to apply a threshold filter.
 *
 * The pixel with the value less than the threshold value will be set to 0, else the value is set to the maximum
 * value of the image pixel type.
 *
 * The functor provides a template method operator(param) to apply the filter
 */
struct ThresholdFilter
{
    struct Parameter
    {
        double thresholdValue; ///< threshold value.
        ::fwData::Image::csptr imageIn; ///< image source
        ::fwData::Image::sptr imageOut; ///< image target: contains the result of the filter
    };

    /**
     * @brief Applies the filter
     * @tparam PIXELTYPE image pixel type (uint8, uint16, int8, int16, float, double, ....)
     */
    template<class PIXELTYPE>
    void operator()(Parameter& param)
    {
        const PIXELTYPE thresholdValue = static_cast<PIXELTYPE>(param.thresholdValue);
        ::fwData::Image::csptr imageIn = param.imageIn;
        ::fwData::Image::sptr imageOut = param.imageOut;
        SLM_ASSERT("Sorry, image must be 3D", imageIn->getNumberOfDimensions() == 3 );
        imageOut->copyInformation(imageIn); // Copy image size, type... without copying the buffer
        imageOut->allocate(); // Allocate the image buffer

        ::fwDataTools::helper::ImageGetter imageInHelper(imageIn); // helper used to access the image source buffer
        ::fwDataTools::helper::Image imageOutHelper(imageOut); // helper used to access the image target buffer

        // Get image buffers
        const PIXELTYPE* buffer1 = (PIXELTYPE*)imageInHelper.getBuffer();
        PIXELTYPE* buffer2       = (PIXELTYPE*)imageOutHelper.getBuffer();

        // Get number of pixels
        const size_t NbPixels = imageIn->getSize()[0] * imageIn->getSize()[1] * imageIn->getSize()[2];

        // Fill the target buffer considering the thresholding
        for( size_t i = 0; i < NbPixels; ++i, ++buffer1, ++buffer2 )
        {
            * buffer2 = ( *buffer1 < thresholdValue ) ? 0 : std::numeric_limits<PIXELTYPE>::max();
        }
    }
};

//-----------------------------------------------------------------------------

void SThreshold::updating()
{
    ThresholdFilter::Parameter param; // filter parameters: threshold value, image source, image target

    ::fwData::Object::csptr input                  = this->getInput< ::fwData::Object >(s_IMAGE_INPUT);
    ::fwMedData::ImageSeries::csptr imageSeriesSrc = ::fwMedData::ImageSeries::dynamicConstCast(input);
    ::fwData::Image::csptr imageSrc                = ::fwData::Image::dynamicConstCast(input);
    ::fwData::Object::sptr output;

    // Get source/target image
    if(imageSeriesSrc)
    {
        param.imageIn                                  = imageSeriesSrc->getImage();
        ::fwMedData::ImageSeries::sptr imageSeriesDest = ::fwMedData::ImageSeries::New();

        ::fwData::Object::DeepCopyCacheType cache;
        imageSeriesDest->::fwMedData::Series::cachedDeepCopy(imageSeriesSrc, cache);
        imageSeriesDest->setDicomReference(imageSeriesSrc->getDicomReference());

        ::fwData::Image::sptr imageOut = ::fwData::Image::New();
        imageSeriesDest->setImage(imageOut);
        param.imageOut = imageOut;
        output         = imageSeriesDest;
    }
    else if(imageSrc)
    {
        param.imageIn                  = imageSrc;
        ::fwData::Image::sptr imageOut = ::fwData::Image::New();
        param.imageOut                 = imageOut;
        output                         = imageOut;
    }
    else
    {
        FW_RAISE("Wrong type: source type must be an ImageSeries or an Image");
    }

    param.thresholdValue = m_threshold;

    /*
     * The dispatcher allows to apply the filter on any type of image.
     * It invokes the template functor ThresholdFilter using the image type.
     */
    ::fwTools::DynamicType type = param.imageIn->getPixelType(); // image type

    // Invoke filter functor
    ::fwTools::Dispatcher< ::fwTools::IntrinsicTypes, ThresholdFilter >::invoke( type, param );

    this->setOutput(s_IMAGE_OUTPUT, output);
}

//-----------------------------------------------------------------------------

} // namespace opImageFilter
