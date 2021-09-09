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
        std::cout << "_originalImageRawData = " << sizeof(_originalImageRawData.get()) << "\n";
        std::cout << "len = " << len << "\n";
         if ( file.Read(_originalImageRawData.get(), _dataSize) != len )
        {
            errorStream << ": Could not read the input file";
            wxString error(errorStream.str().c_str(), wxConvUTF8);
            wxLogError(error);
        }
        else
        {
            /* TODO: Find a way to get the width and height of bitmap platform independant,
            without constructing wximage object.
            This data is necessary to construct the Mat object in Compute function
            */
            wxMemoryInputStream stream(_originalImageRawData.get(), _dataSize);
            wxImage originalImage;
            originalImage.LoadFile(stream, wxBITMAP_TYPE_BMP);
            _inputWidth = originalImage.GetWidth();
            _inputHeight = originalImage.GetHeight();
            _images.emplace_back(std::move(std::make_shared<Img>(_originalImageRawData, _dataSize, 0, _inputWidth, _inputHeight)));
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