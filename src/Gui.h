#ifndef GUI_H
#define GUI_H

#include <wx/wx.h>
#include <memory>
#include <string>
#include <vector>
#include "ImgPool.h"

class MainFrame; // forward declaration
class CustomImagePanel; // forward declaration

static constexpr int WINDOW_WIDTH = 720;
static constexpr int WINDOW_HEIGHT= 480;
static constexpr char APP_NAME[] = "Image Bluring";
static constexpr double SIGMA_CHANGE_DEBOUNCE_TIME = 0.2;

static constexpr char LOAD_IMAGE_LABEL[] = "Load image";

class MainPanelDialog : public wxWindow
{
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
    std::unique_ptr<wxButton> _loadImageBt;
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
    std::unique_ptr<ImgPool> _imagePool;
    std::unique_ptr<wxSlider> _blurSlider;
    std::unique_ptr<CustomImagePanel> _imagePanel;
    int lastSelectedSigma { 0 };

    void OnSigmaChanged(wxScrollEvent& event);
public:
    // constructor / desctructor
    BlurImageFrame(MainFrame* window, std::string imagePath);

    DECLARE_EVENT_TABLE()
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
    CustomImagePanel(wxPanel *parent, std::shared_ptr<Img>, wxSize containerSize);

    // events
    void paintEvent(wxPaintEvent &evt);
    void paintNow();
    void render(wxDC &dc);

    void ReplaceImage(std::shared_ptr<Img> img);

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
    SLIDER_SIGMA = wxID_HIGHEST + 1,
 };
#endif