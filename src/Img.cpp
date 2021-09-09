#include "Img.h"
#include <sstream>

Img::Img(std::string path, wxSize parentContainerSize)
{
    std::stringstream errorStream;
    errorStream << "Fail on construct image object ";
    errorStream << this;

    wxFile file(path);
    if (file.IsOpened())
    {
        wxFileOffset len = file.Length();
        _dataSize = (size_t)len;
        _originalData = std::shared_ptr<void>{ malloc(len), free }; // _originalData is a `std::shared_ptr<void>
         if ( file.Read(_originalData.get(), _dataSize) != len )
        {
            errorStream << ": Could not read the file";
            wxString error(errorStream.str().c_str(), wxConvUTF8);
            wxLogError(error);
        }
        else
        {
            isOriginal = true;
            isValid = true;
            _parentWidth = parentContainerSize.GetWidth();
            _parentHeight = parentContainerSize.GetHeight();
        }
    }
    else{
        errorStream << ": Could not open the file";
        wxString error(errorStream.str().c_str(), wxConvUTF8);
        wxLogError(error);
    }
}

Img::Img(Img& img, double sigma )
{
  //TODO: To be implemented
}

Img::~Img()
{
    //TODO: To be implemented
    std::cout << "Img Destructor"<< std::endl;
}


Img::Img(const Img &source){
    //TODO: To be implemented
     std::cout << "Img::COPYING content " << std::endl;
}

Img& Img::operator=(const Img &source){
    //TODO: To be implemented
    std::cout << "Img::ASSIGNING content" << std::endl;
    return *this;
}

Img::Img(Img &&source){
    //TODO: To be implemented
    std::cout << "Img::MOVING (c’tor)" << std::endl;
}

Img &Img::operator=(Img &&source){
    //TODO: To be implemented
    std::cout << "Img::MOVING (assign) " << std::endl;
    return *this;
}


wxImage Img::toWxBitmap() const{
    wxMemoryInputStream stream(_handledData == nullptr ? _originalData.get() : _handledData.get(), _dataSize);
    wxImage unhandled;
    unhandled.LoadFile(stream, wxBITMAP_TYPE_BMP);
    return unhandled.Rescale(_parentWidth, _parentHeight, wxIMAGE_QUALITY_HIGH);
}