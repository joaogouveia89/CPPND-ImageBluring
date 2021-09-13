#include "Img.h"

Img::Img(cv::Mat* originalImage, double sigma, int width, int height) :
_sigma(sigma), _width(width), _height(height){
     if(sigma != 0) /* if sigma is zero, the object corresponds to original image, so no computing is necessary */
     {
         Compute(originalImage);
     }
     else{
         computingDone = true;
         _result = std::make_shared<cv::Mat>(*originalImage);
     }
 }

wxImage Img::toWxBitmap(const int width, const int height) const{
    cv::Mat toReturnPrev = *_result.get();
    cv::Mat toReturn;
    if(computingDone){
        cv::cvtColor(toReturnPrev, toReturn, cv::ColorConversionCodes::COLOR_BGR2RGB);
    }
    wxImage unhandled(toReturn.cols, toReturn.rows, toReturn.data, true);
    return unhandled.Rescale(width, height, wxIMAGE_QUALITY_HIGH);
}

void Img::Compute(cv::Mat* originalImage)
{
    int filterRatio = 122*_width/_height;
    std::future<void> result = std::async([&filterRatio](cv::Mat* original, Img* img) {
        cv::Mat blurred;
        cv::GaussianBlur(*original, blurred,  cv::Size(filterRatio, filterRatio), img->Sigma());
         img->_result = std::make_shared<cv::Mat>(blurred);
         img->computingDone = true;
    }, originalImage, this);
}