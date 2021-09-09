#include "Img.h"

Img::Img(std::shared_ptr<void> originalRawData, size_t dataSize, double sigma, int width, int height) :
 _buffer(originalRawData), _dataSize(dataSize), _sigma(sigma), _width(width), _height(height){
    if(sigma != 0)
    {
        _computedResult = std::async(std::launch::deferred, &Img::Compute, this);
    }
}

wxImage Img::toWxBitmap(const int width, const int height) const{
    wxMemoryInputStream stream(_buffer.get(), _dataSize);
    wxImage unhandled;
    unhandled.LoadFile(stream, wxBITMAP_TYPE_BMP);
    return unhandled.Rescale(width, height, wxIMAGE_QUALITY_HIGH);
}

void Img::Compute()
{
    int filterRatio = 122*_width/_height;
    cv::Mat img = cv::Mat(_width, _height, CV_16U, (uchar*)_buffer.get());

    cv::Mat blurred;

    cv::GaussianBlur(img, blurred, cv::Size(filterRatio, filterRatio), _sigma);

    _buffer = std::shared_ptr<void>{ blurred.data , free }; 

    //clean buffer and iterate over Mat to set its bytes to it.
    // see https://stackoverflow.com/questions/12692224/store-a-cvmat-in-a-byte-array-for-data-transfer-to-a-server

    // thanks to https://stackoverflow.com/questions/12692224/store-a-cvmat-in-a-byte-array-for-data-transfer-to-a-server

    
}