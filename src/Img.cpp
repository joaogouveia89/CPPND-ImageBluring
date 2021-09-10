#include "Img.h"

Img::Img(std::shared_ptr<cv::Mat> originalImage, double sigma, int width, int height) :
 _originalImage(originalImage), _sigma(sigma), _width(width), _height(height){
     if(sigma != 0) /* if sigma is zero, the object corresponds to original image, so no computing is necessary */
     {
         Compute();
     }
 }

wxImage Img::toWxBitmap(const int width, const int height) const{
    cv::Mat toReturn = _result == nullptr ? (*_originalImage.get()) : (*_result.get());
    cv::cvtColor(toReturn, toReturn, cv::ColorConversionCodes::COLOR_BGR2RGB);
    wxImage unhandled(toReturn.cols, toReturn.rows, toReturn.data, true);
    return unhandled.Rescale(width, height, wxIMAGE_QUALITY_HIGH);
}

void Img::Compute()
{
    std::cout << "STARTED\n";
    int filterRatio = 122*_width/_height;

    std::future<void> ftr = std::async(std::launch::async, cv::GaussianBlur, *_originalImage, *_result, cv::Size(filterRatio, filterRatio), _sigma, _sigma, cv::BORDER_DEFAULT);
    ftr.wait();
    
    std::cout << "FINISHED\n";

}