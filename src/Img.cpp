#include "Img.h"

Img::Img(std::shared_ptr<std::vector<cv::Mat>> originalImageParts, double sigma, int filterRatio) :
_sigma(sigma), _filterRatio(filterRatio){
     if(sigma > 0) /* if sigma is zero, the object corresponds to original image, so no computing is necessary */
     {
         Compute(originalImageParts);
     }else{
         throw "If you want to set the sigma = 0 image, use the Img::Img(cv::Mat originalImage) constructor!";
     }
 }

Img::Img(cv::Mat originalImage){
    _result = std::make_shared<cv::Mat>(originalImage);
    computingDone = true;
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

void Img::Compute(std::shared_ptr<std::vector<cv::Mat>> originalImageParts)
{
    std::future<cv::Mat> resultR = std::async([](cv::Mat* original, Img* img) {
        cv::Mat blurred;
        cv::GaussianBlur(*original, blurred,  cv::Size(img->_filterRatio, img->_filterRatio), img->Sigma());
        return blurred;
    }, &(originalImageParts.get()->at(0)), this);

    std::future<cv::Mat> resultG = std::async([](cv::Mat* original, Img* img) {
        cv::Mat blurred;
        cv::GaussianBlur(*original, blurred,  cv::Size(img->_filterRatio, img->_filterRatio), img->Sigma());
        return blurred;
    }, &(originalImageParts.get()->at(1)), this);

    std::future<cv::Mat> resultB = std::async([](cv::Mat* original, Img* img) {
        cv::Mat blurred;
        cv::GaussianBlur(*original, blurred,  cv::Size(img->_filterRatio, img->_filterRatio), img->Sigma());
        return blurred;
    }, &(originalImageParts.get()->at(2)), this);

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