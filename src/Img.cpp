#include "Img.h"
#include <sstream>


Img::Img(std::shared_ptr<void> rawData, size_t dataSize, double sigma) : _buffer(rawData), _dataSize(dataSize), _sigma(sigma){}

wxImage Img::toWxBitmap(const int width, const int height) const{
    wxMemoryInputStream stream(_buffer.get(), _dataSize);
    wxImage unhandled;
    unhandled.LoadFile(stream, wxBITMAP_TYPE_BMP);
    return unhandled.Rescale(width, height, wxIMAGE_QUALITY_HIGH);
}