#ifndef IMG_POOL_H
#define IMG_POOL_H
#include <wx/wx.h>
#include <memory>
#include <string>
#include <vector>
#include <math.h>
#include <opencv2/opencv.hpp>

#include "Img.h"

/*
Stores img objects. The idea is to store some objects to give a better responsive experience to user: 
*/

class ImgPool{
private:
    std::vector<std::shared_ptr<Img>> _images;
    std::shared_ptr<std::vector<cv::Mat>> _originalImageParts;
    int _inputWidth { 0 };
    int _inputHeight { 0 };
    int advanceRatio { 0 };
    int filterRatio { 0 };

    void CalculateAdvanceRatio();

public:
    std::shared_ptr<Img>  AskFor(double sigma);

    ImgPool(std::string imagePath);
};

#endif