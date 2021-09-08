#include "Img.h"
#include <sstream>

Img::Img(std::string path, wxSize parentContainerSize)
{
    std::cout << "Img Regular Ctr"<< std::endl;
    std::stringstream errorStream;
    errorStream << "Fail on construct image object ";
    errorStream << this;

    wxFile file(path);
    if (file.IsOpened())
    {
        wxFileOffset len = file.Length();
        _dataSize = (size_t)len;
        _originalData = std::make_shared<void*>(malloc(_dataSize)); 
        std::cout << "_originalData ok"<< std::endl;
         if ( file.Read(_originalData.get(), _dataSize) != len )
        {
            std::cout << "Could not read the file"<< std::endl;
            errorStream << ": Could not read the file";
            wxString error(errorStream.str().c_str(), wxConvUTF8);
            wxLogError(error);
        }
        else
        {
            isOriginal = true;
            isValid = true;
            std::cout << "missing parent things"<< std::endl;
            _parentWidth = parentContainerSize.GetWidth();
            _parentHeight = parentContainerSize.GetHeight();
            std::cout << "all ok"<< std::endl;
        }
    }
    else{
        errorStream << ": Could not open the file";
        wxString error(errorStream.str().c_str(), wxConvUTF8);
        wxLogError(error);
    }
    std::cout << "Finished Img Regular Ctr"<< std::endl;
}

Img::Img(Img& img, double sigma )
{
  
}

Img::~Img()
{
    std::cout << "Img Destructor"<< std::endl;
}


Img::Img(const Img &source){
     std::cout << "Img::COPYING content " << std::endl;
}

Img& Img::operator=(const Img &source){
    std::cout << "Img::ASSIGNING content" << std::endl;
    return *this;
}

Img::Img(Img &&source){
    std::cout << "Img::MOVING (c’tor)" << std::endl;
}

Img &Img::operator=(Img &&source){
    std::cout << "Img::MOVING (assign) " << std::endl;
    return *this;
}


wxImage Img::toWxBitmap() const{
    wxMemoryInputStream stream(_handledData == nullptr ? _originalData.get() : _handledData.get(), _dataSize);
    wxImage unhandled;
    unhandled.LoadFile(stream, wxBITMAP_TYPE_BMP);
    return unhandled.Rescale(_parentWidth, _parentHeight, wxIMAGE_QUALITY_HIGH);
}