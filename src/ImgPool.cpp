#include "ImgPool.h"


ImgPool::ImgPool(std::string imagePath)
{

    _originalImage = std::make_shared<cv::Mat>(cv::imread(imagePath));
    if (_originalImage->data != NULL) /* see https://docs.opencv.org/4.5.2/d4/da8/group__imgcodecs.html#ga288b8b3da0892bd651fce07b3bbd3a56 */
    {
        _images.emplace_back(std::move(std::make_shared<Img>(_originalImage, 0, _originalImage->rows, _originalImage->cols)));
        _images.emplace_back(std::move(std::make_shared<Img>(_originalImage, 1, _originalImage->rows, _originalImage->cols)));
        _images.emplace_back(std::move(std::make_shared<Img>(_originalImage, 2, _originalImage->rows, _originalImage->cols)));
    }
    else{
        std::string errorMessage = "Fail to open the file. Check if the file is missing, has improper permissions, is unsupported or an invalid format: check docs for more details: https://docs.opencv.org/4.5.2/d4/da8/group__imgcodecs.html#ga288b8b3da0892bd651fce07b3bbd3a56";
        wxString error(errorMessage.c_str(), wxConvUTF8);
        wxLogError(error);
    }
}

std::shared_ptr<Img>  ImgPool::AskFor(double sigma)
{
    std::vector<double> sigmas{ sigma - 2, sigma - 1, sigma, sigma + 1, sigma + 2 };

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
            _images.emplace_back(std::move(std::make_shared<Img>(_originalImage, sigma, _originalImage->rows, _originalImage->cols)));
        }
    }

    auto askedIt = find_if(_images.begin(), _images.end(), [&sigma](std::shared_ptr<Img> img){ return img->Sigma() == sigma; });

    std::shared_ptr<Img> asked;

    if(askedIt != _images.end())
    {
        asked = *askedIt;
    }
    else
    {
       asked = *_images.begin(); // if no image has been found, return the original one
    }
    
    return asked;
}
