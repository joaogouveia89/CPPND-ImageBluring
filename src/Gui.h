#ifndef GUI_H
#define GUI_H

#include <wx/wx.h>
#include <memory>
#include <string>
#include "Img.h"

class MainFrame; // forward declaration
class CustomImagePanel; // forward declaration

static constexpr int WINDOW_WIDTH = 720;
static constexpr int WINDOW_HEIGHT= 480;
static constexpr char APP_NAME[] = "Image Bluring";

static constexpr char LOAD_IMAGE_LABEL[] = "Load image";

class MainPanelDialog : public wxWindow
{
private:
    // control elements
    wxBoxSizer *_dialogSizer;
    wxBitmap _image;

public:
    // constructor / destructor
    MainPanelDialog(wxWindow *parent, wxWindowID id);

    // events
    void paintEvent(wxPaintEvent &evt);
    void paintNow();
    void render(wxDC &dc);

    DECLARE_EVENT_TABLE()
};

class LoadImageFrame : public wxPanel
{
private:
    // control elements
    std::unique_ptr<wxButton*> _loadImageBt;
    MainFrame* _mainFrame;

    void OnLoadImageClick( wxCommandEvent& event );

public:
    // constructor / desctructor
    LoadImageFrame(MainFrame* window);

    DECLARE_EVENT_TABLE()
};

class BlurImageFrame : public wxPanel
{
private:
    std::string _imagePath;
    std::unique_ptr<wxSlider> _blurSlider;
    std::unique_ptr<CustomImagePanel> _imagePanel;


public:
    // constructor / desctructor
    BlurImageFrame(MainFrame* window, std::string imagePath);
};

// frame containing all control elements
class MainFrame : public wxFrame
{
private:
    // control elements
    std::unique_ptr<LoadImageFrame> _loadImageFrame { nullptr };
    std::unique_ptr<BlurImageFrame> _blurImageFrame { nullptr };
public:
    // constructor / desctructor
    void ShowLoadingImageFrame();
    void ShowBlurImageFrame(std::string imagePath);

    MainFrame();
};

class CustomImagePanel : public wxPanel
{
private:
    // control elements
    std::shared_ptr<Img> _currentImage;

public:
    // constructor / desctructor
    CustomImagePanel(wxFrame *parent, std::shared_ptr<Img>, wxSize containerSize);

    // events
    void paintEvent(wxPaintEvent &evt);
    void paintNow();
    void render(wxDC &dc);

    DECLARE_EVENT_TABLE()
};



class ImageBlurringApp : public wxApp
{
public:
    // events
    virtual bool OnInit();
};

 enum
 {
    BUTTON_LOAD_IMAGE = wxID_HIGHEST + 1,
 };



// cv::Mat img = cv::imread(params.ImagePath());

// cv::Mat blurred;

// std::cout << "sigma = " << params.Sigma() << "\n";
// cv::GaussianBlur(img, blurred, cv::Size(61, 61), params.Sigma());

// cv::namedWindow("Gaussed window", cv::WINDOW_NORMAL);
// cv::resizeWindow("Gaussed window", 800, 400);

// cv::namedWindow("Original window", cv::WINDOW_NORMAL);
// cv::resizeWindow("Original window", 800, 400);

// cv::imshow("Original window", img);
// cv::imshow("Gaussed window", blurred);

// int k = cv::waitKey(0); // Wait for a keystroke in the window
#endif