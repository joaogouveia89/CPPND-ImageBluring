#ifndef IMG_H
#define IMG_H
#include <wx/wx.h>
#include <wx/file.h>
#include <wx/mstream.h>
#include <memory>
#include <string>

// https://docs.wxwidgets.org/3.0/classwx_file_name.html#a6703bfd4f587b35926d5c2949bc11918    https://docs.wxwidgets.org/3.0/classwx_image.html
// use above to support multiple image formats

class Img
{
private:
    double _sigma;
    std::shared_ptr<void> _buffer;
    size_t _dataSize;
    // pass to unique_ptr 
    // Mat to raw pointer https://stackoverflow.com/questions/61042167/how-to-convert-cvmat-to-void
    
public:
    Img(std::shared_ptr<void> rawData, size_t dataSize, double sigma);

    wxImage toWxBitmap(const int parentWidth, const int parentHeight) const;
};

#endif