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
        _originalData = malloc(_dataSize); 
         if ( file.Read(_originalData, _dataSize) != len )
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
  
}

wxImage Img::toWxBitmap() const{
    wxMemoryInputStream stream(_handledData == NULL ? _originalData : _handledData, _dataSize);
    wxImage unhandled;
    unhandled.LoadFile(stream, wxBITMAP_TYPE_BMP);
    return unhandled.Rescale(_parentWidth, _parentHeight, wxIMAGE_QUALITY_HIGH);
}