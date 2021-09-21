#ifndef IMG_H
#define IMG_H
#include <wx/wx.h>
#include <future>
#include <memory>
#include <string>
#include<thread>
#include<vector>
#include <opencv2/opencv.hpp>

// https://docs.wxwidgets.org/3.0/classwx_file_name.html#a6703bfd4f587b35926d5c2949bc11918    https://docs.wxwidgets.org/3.0/classwx_image.html
// use above to support multiple image formats

class Img
{
private:
    double _sigma { 0 };
    std::shared_ptr<cv::Mat> _result { nullptr };
    int _filterRatio { 0 };

    bool computingDone { false };
    
public:
    Img(std::shared_ptr<std::vector<cv::Mat>> originalImageParts, double sigma, int filterRatio);
    Img(cv::Mat originalImage);

    wxImage toWxBitmap(const int parentWidth, const int parentHeight) const;

    double Sigma() const{ return _sigma; }

    void Compute(std::shared_ptr<std::vector<cv::Mat>> originalImageParts);

    bool isComputingDone() const { return computingDone; }
};

#endif