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

std::shared_ptr<Img> ImgPool::AskFor(double sigma)
{
    if((sigma - 2) >= 0 && std::find_if(_images.begin(), _images.end(), [&sigma](std::shared_ptr<Img> img) { return img->Sigma() == (sigma - 2); } ) == _images.end())
    {
        _images.emplace_back(std::move(std::make_shared<Img>(_originalImage, sigma - 2, _originalImage->rows, _originalImage->cols)));
    }

    if((sigma - 1) >= 0 && std::find_if(_images.begin(), _images.end(), [&sigma](std::shared_ptr<Img> img) { return img->Sigma() == (sigma - 1); }) == _images.end())
    {
        _images.emplace_back(std::move(std::make_shared<Img>(_originalImage, sigma - 1, _originalImage->rows, _originalImage->cols)));
    }

    if(std::find_if(_images.begin(), _images.end(), [&sigma](std::shared_ptr<Img> img) { return img->Sigma() == (sigma + 1); }) == _images.end())
    {
        _images.emplace_back(std::move(std::make_shared<Img>(_originalImage, sigma + 1, _originalImage->rows, _originalImage->cols)));
    }

    if(std::find_if(_images.begin(), _images.end(), [&sigma](std::shared_ptr<Img> img) { return img->Sigma() == (sigma + 2); }) == _images.end())
    {
        _images.emplace_back(std::move(std::make_shared<Img>(_originalImage, sigma + 2, _originalImage->rows, _originalImage->cols)));
    }
    

    auto askedIt = find_if(_images.begin(), _images.end(), [&sigma](std::shared_ptr<Img> img){ return img->Sigma() == sigma; });

    std::shared_ptr<Img> asked;

    if(askedIt != _images.end())
    {
        asked = *askedIt;
    }
    else
    {
       asked = *_images.begin();
    }
    
    return asked;
}


bool ImgPool::HasBeenCalculated(double sigma)
{
    return find_if(_images.begin(), _images.end(), [&sigma](std::shared_ptr<Img> img){ return img->Sigma() == sigma; }) != _images.end();
}

