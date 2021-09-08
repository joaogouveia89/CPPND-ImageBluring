#ifndef IMG_H
#define IMG_H
#include <wx/wx.h>
#include <wx/file.h>
#include <wx/mstream.h>
#include <memory>
#include <string>

// thanks to https://stackoverflow.com/questions/59765957/returning-a-unique-void-pointer-from-a-function
struct ptr_deleter {
    void operator()(void *data) const noexcept {
        if(data != nullptr)
            std::free(data);
    }
};

class Img
{
private:
    bool isOriginal { false };
    bool isValid { false };
    double sigma { 0 };
    std::shared_ptr<void> _originalData; 
    std::unique_ptr<void, ptr_deleter> _handledData { nullptr };
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