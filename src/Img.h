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
    bool isOriginal { false };
    bool isValid { false };
    double sigma { 0 };
    std::shared_ptr<void> _originalData; 
    size_t _dataSize { 0 };
    int _parentWidth;
    int _parentHeight;
    // pass to unique_ptr 
    // Mat to raw pointer https://stackoverflow.com/questions/61042167/how-to-convert-cvmat-to-void
    
public:
    Img(std::string path, wxSize parentContainerSize);
    // Rule of Five
    ~Img(); // 1: destructor
    Img(const Img &source); // 2: copy constructor
    Img &operator=(const Img &source); // 3: copy assignement operator
    Img(Img &&source); // 4: move constructor
    Img &operator=(Img &&source); // 5: move assignment operator

    Img(Img& img, double sigma);

    wxImage toWxBitmap() const;
};

#endif