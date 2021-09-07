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
    std::unique_ptr<wxMemoryInputStream> _stream;
    wxImage _bitmap;
    wxImage _originalBitmap;
    double sigma { 0 };
    void* data { NULL }; // https://stackoverflow.com/questions/59765957/returning-a-unique-void-pointer-from-a-function
    // pass to unique_ptr 
    // Mat to raw pointer https://stackoverflow.com/questions/61042167/how-to-convert-cvmat-to-void
    
public:
    Img(std::string path, wxSize parentContainerSize);
    Img(Img& img, double sigma);

    wxImage Bitmap() const { return _bitmap; }
};

#endif