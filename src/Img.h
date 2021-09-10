#ifndef IMG_H
#define IMG_H
#include <wx/wx.h>
#include <wx/file.h>
#include <wx/mstream.h>
#include <future>
#include <memory>
#include <string>
#include<thread>
#include <opencv2/opencv.hpp>

// https://docs.wxwidgets.org/3.0/classwx_file_name.html#a6703bfd4f587b35926d5c2949bc11918    https://docs.wxwidgets.org/3.0/classwx_image.html
// use above to support multiple image formats

class Img
{
private:
    double _sigma;
    std::shared_ptr<cv::Mat> _result { nullptr };
    std::shared_ptr<cv::Mat> _originalImage;
    int _width { 0 };
    int _height { 0 };
    
public:
    Img(std::shared_ptr<cv::Mat> originalImage, double sigma, int width, int height);

    wxImage toWxBitmap(const int parentWidth, const int parentHeight) const;

    double Sigma() const{ return _sigma; }

    void Compute();
};

#endif