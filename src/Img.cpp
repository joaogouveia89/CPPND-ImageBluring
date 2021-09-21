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
    std::vector<cv::Mat> rgbChannels(3);
    split(*originalImage, rgbChannels);
    std::future<cv::Mat> resultR = std::async([&filterRatio](cv::Mat original, Img* img) {
        cv::Mat blurred;
        cv::GaussianBlur(original, blurred,  cv::Size(filterRatio, filterRatio), img->Sigma());
        return blurred;
    }, std::move(rgbChannels[0]), this);

    std::future<cv::Mat> resultG = std::async([&filterRatio](cv::Mat original, Img* img) {
        cv::Mat blurred;
        cv::GaussianBlur(original, blurred,  cv::Size(filterRatio, filterRatio), img->Sigma());
        return blurred;
    }, std::move(rgbChannels[1]), this);

    std::future<cv::Mat> resultB = std::async([&filterRatio](cv::Mat original, Img* img) {
        cv::Mat blurred;
        cv::GaussianBlur(original, blurred,  cv::Size(filterRatio, filterRatio), img->Sigma());
        return blurred;
    }, std::move(rgbChannels[2]), this);

    std::future<void> mergeTask = std::async([](std::future<cv::Mat> ftrR, std::future<cv::Mat> ftrG, std::future<cv::Mat> ftrB, Img* img){
        std::vector<cv::Mat> channels;
        cv::Mat result;
        ftrR.wait();
        ftrG.wait();
        ftrB.wait();

        channels.emplace_back(ftrR.get());
        channels.emplace_back(ftrG.get());
        channels.emplace_back(ftrB.get());
        cv::merge(channels, result);

        img->_result = std::make_shared<cv::Mat>(result);

        img->computingDone = true;
    }, std::move(resultR), std::move(resultG), std::move(resultB), this);
}