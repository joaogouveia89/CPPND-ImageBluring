#include "Img.h"

Img::Img(std::string path, wxSize parentContainerSize)
{
    wxFile file(path);
    if (file.IsOpened())
    {
        wxFileOffset len = file.Length();
        size_t dataSize = (size_t)len;
        data = malloc(dataSize); //used a raw pointer here as it will be deallocated by the end of this constructor
         if ( file.Read(data, dataSize) != len )
        {
            wxLogError("Reading bitmap file failed");
        }
        else
        {
            _stream = std::make_unique<wxMemoryInputStream>(data, dataSize);
            wxImage rawImage;
            rawImage.LoadFile(*_stream.get(), wxBITMAP_TYPE_BMP);
            _bitmap = rawImage.Rescale(parentContainerSize.GetWidth(), parentContainerSize.GetHeight(), wxIMAGE_QUALITY_HIGH);
            _originalBitmap = _bitmap;
        }
        isOriginal = true;
    }
    else{
        wxLogError("Could not load image file");
    }
}

Img::Img(Img& img, double sigma )
{
    this->data = img.data;
    this->sigma = sigma;
    this->_originalBitmap = img._originalBitmap;
}