#include "ImgPool.h"

#include<sstream>
ImgPool::ImgPool(std::string imagePath)
{
    std::stringstream errorStream;
    errorStream << "Fail on construct image pool object ";
    errorStream << this;

    wxFile file(imagePath);
    if (file.IsOpened())
    {
        wxFileOffset len = file.Length();
        _dataSize = (size_t)len;
        _originalImageRawData = std::shared_ptr<void>{ malloc(len), free }; // _originalData is a `std::shared_ptr<void>
         if ( file.Read(_originalImageRawData.get(), _dataSize) != len )
        {
            errorStream << ": Could not read the input file";
            wxString error(errorStream.str().c_str(), wxConvUTF8);
            wxLogError(error);
        }
        else
        {
            _images.emplace_back(std::move(std::make_shared<Img>(_originalImageRawData, _dataSize, 0)));
        }
    }
    else{
        errorStream << ": Could not open the input file";
        wxString error(errorStream.str().c_str(), wxConvUTF8);
        wxLogError(error);
    }
}

std::shared_ptr<Img> ImgPool::AskFor(double sigma)
{
    return _images.front();
}