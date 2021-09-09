#ifndef IMG_POOL_H
#define IMG_POOL_H
#include <wx/wx.h>
#include <memory>
#include <string>
#include <vector>

#include "Img.h"

/*
Stores img objects. The idea is to store 5 images in memory: 
the current image on image container, an image with a sigma 10% greater, an image with with sigma 20% greatter
an image with a sigma 10% lower and an image 20% lower, taking the current image as reference
The idea ia to offer a more responsive experience to user as it moves the seekbar, and to do this, the next two or previous 2
images must be ready to be show as soon as one of them is required.
If user moves the seekbar, this buffer has to be updated
*/

class ImgPool{
private:
    std::vector<std::shared_ptr<Img>> _images;
    size_t _dataSize { 0 };
    std::shared_ptr<void> _originalImageRawData;
    double currentSigma{ 0 };
public:
    wxImage CurrentImage();
    std::shared_ptr<Img> AskFor(double sigma);

    ImgPool(std::string imagePath);
};

#endif