#include "Img.h"

Img::Img(std::shared_ptr<cv::Mat> originalImage, double sigma, int width, int height) :
 _originalImage(originalImage), _sigma(sigma), _width(width), _height(height){
     if(sigma != 0) /* if sigma is zero, the object corresponds to original image, so no computing is necessary */
     {
         Compute();
     }
 }

wxImage Img::toWxBitmap(const int width, const int height) const{
    cv::Mat toReturnPrev = _result == nullptr ? (*_originalImage.get()) : (*_result.get());
    cv::Mat toReturn;
    cv::cvtColor(toReturnPrev, toReturn, cv::ColorConversionCodes::COLOR_BGR2RGB);
    wxImage unhandled(toReturn.cols, toReturn.rows, toReturn.data, true);
    return unhandled.Rescale(width, height, wxIMAGE_QUALITY_HIGH);
}

void Img::Compute()
{
    int filterRatio = 122*_width/_height;
    std::future<cv::Mat> result = std::async([&filterRatio](std::shared_ptr<cv::Mat> original, double sigma) {
        cv::Mat blurred;
        cv::GaussianBlur(*original, blurred,  cv::Size(filterRatio, filterRatio), sigma);
        return blurred;
    }, _originalImage, Sigma());
    
    _result = std::make_shared<cv::Mat>(result.get());
}