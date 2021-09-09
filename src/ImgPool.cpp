#include "ImgPool.h"

ImgPool::ImgPool(std::string imagePath, wxSize parentContainerSize)
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