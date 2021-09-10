#include "ImgPool.h"

ImgPool::ImgPool(std::string imagePath)
{

    _originalImage = std::make_shared<cv::Mat>(cv::imread(imagePath));
    if (_originalImage->data != NULL) /* see https://docs.opencv.org/4.5.2/d4/da8/group__imgcodecs.html#ga288b8b3da0892bd651fce07b3bbd3a56 */
    {
        _images.emplace_back(std::move(std::make_shared<Img>(_originalImage, 0, _originalImage->rows, _originalImage->cols)));
        _images.emplace_back(std::move(std::make_shared<Img>(_originalImage, 2000, _originalImage->rows, _originalImage->cols)));
    }
    else{
        std::string errorMessage = "Fail to open the file. Check if the file is missing, has improper permissions, is unsupported or an invalid format: check docs for more details: https://docs.opencv.org/4.5.2/d4/da8/group__imgcodecs.html#ga288b8b3da0892bd651fce07b3bbd3a56";
        wxString error(errorMessage.c_str(), wxConvUTF8);
        wxLogError(error);
    }
}

std::shared_ptr<Img> ImgPool::AskFor(double sigma)
{
    if(sigma == 0){
        return _images.front();
    }else{
        return _images.back();
    }
}