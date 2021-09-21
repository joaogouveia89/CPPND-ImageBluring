#include "ImgPool.h"


ImgPool::ImgPool(std::string imagePath)
{

    cv::Mat originalImage = cv::imread(imagePath);
    if (originalImage.data != NULL) /* see https://docs.opencv.org/4.5.2/d4/da8/group__imgcodecs.html#ga288b8b3da0892bd651fce07b3bbd3a56 */
    {
        _inputWidth = originalImage.rows;
        _inputHeight = originalImage.cols;
        std::vector<cv::Mat> rgbChannels(3);

        filterRatio = 122*_inputWidth/_inputHeight;

        CalculateAdvanceRatio();
        split(originalImage, rgbChannels);
        _images.emplace_back(std::move(std::make_shared<Img>(originalImage)));
        _originalImageParts = std::make_shared<std::vector<cv::Mat>>(rgbChannels);

        for(int i = 1; i < advanceRatio; ++i){
            _images.emplace_back(std::move(std::make_shared<Img>(_originalImageParts, i, filterRatio)));
        }
    }
    else{
        std::string errorMessage = "Fail to open the file. Check if the file is missing, has improper permissions, is unsupported or an invalid format: check docs for more details: https://docs.opencv.org/4.5.2/d4/da8/group__imgcodecs.html#ga288b8b3da0892bd651fce07b3bbd3a56";
        wxString error(errorMessage.c_str(), wxConvUTF8);
        wxLogError(error);
    }
}

void ImgPool::CalculateAdvanceRatio(){
    //purely experimental with these values
    int factor = ceil((_inputWidth * _inputHeight) /(double) 100000);
    advanceRatio = ceil(1.8 + 0.023 * factor + 0.000012 * factor * factor);
    if(advanceRatio < 0) advanceRatio = 2;
    else if(advanceRatio > 20) advanceRatio = 10;
}

std::shared_ptr<Img> ImgPool::AskFor(double sigma)
{
    std::vector<double> sigmas;
    for(int i = 0; i < advanceRatio; ++i){
        if(i == 0){
            sigmas.emplace_back(sigma);
        }else{
            sigmas.emplace_back(sigma - i);
            sigmas.emplace_back(sigma + i);
        }
    }
    for(auto img : _images)
    {
        auto sigmaPosition = find(sigmas.begin(), sigmas.end(), img->Sigma());
        if(sigmaPosition != sigmas.end())
        {
            sigmas.erase(sigmaPosition);
        }
    }
    for(auto sigma : sigmas)
    {
        if(sigma >= 0)
        {
            _images.emplace_back(std::move(std::make_shared<Img>(_originalImageParts, sigma, filterRatio)));
        }
    }
    auto askedIt = find_if(_images.begin(), _images.end(), [&sigma](std::shared_ptr<Img> img){ return img->Sigma() == sigma; });
    std::shared_ptr<Img> asked;

    if(askedIt != _images.end() && (*askedIt)->isComputingDone())
    {
        asked = *askedIt;
    }
    else
    {
       asked = *_images.begin(); // if no image has been found, return the original one
    }
    
    return asked;
}
