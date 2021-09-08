#ifndef IMG_H
#define IMG_H
#include <wx/wx.h>
#include <wx/file.h>
#include <wx/mstream.h>
#include <memory>
#include <string>

class Img
{
private:
    bool isOriginal { false };
    bool isValid { false };
    double sigma { 0 };
    void* _originalData { NULL }; // https://stackoverflow.com/questions/59765957/returning-a-unique-void-pointer-from-a-function
    void* _handledData  { NULL };
    size_t _dataSize { 0 };
    int _parentWidth;
    int _parentHeight;
    // pass to unique_ptr 
    // Mat to raw pointer https://stackoverflow.com/questions/61042167/how-to-convert-cvmat-to-void
    
public:
    Img(std::string path, wxSize parentContainerSize);
    Img(Img& img, double sigma);

    wxImage toWxBitmap() const;
};

#endif