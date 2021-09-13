#include "Gui.h"
#include <iostream>

IMPLEMENT_APP(ImageBlurringApp);

bool ImageBlurringApp::OnInit() {
    // create window with name and show it
    MainFrame *main = new MainFrame();
    main->Show(true);

    return true;
}

MainFrame::MainFrame(): wxFrame(
            NULL,
            wxID_ANY, APP_NAME,
            wxDefaultPosition,
            wxSize(WINDOW_WIDTH, WINDOW_HEIGHT)) {
    ShowLoadingImageFrame();
    this->Centre();
}

void MainFrame::ShowLoadingImageFrame() {
    if (_loadImageFrame == nullptr) {
        _loadImageFrame = std::make_unique<LoadImageFrame>(this);
    }
    _blurImageFrame = nullptr;
    _loadImageFrame->Show();
}

void MainFrame::ShowBlurImageFrame(std::string imagePath) {
    if (_blurImageFrame == nullptr) {
        _blurImageFrame = std::make_unique<BlurImageFrame>(this, imagePath);
    }
    if (_loadImageFrame != nullptr) {
        _loadImageFrame->Hide();
    }
    _blurImageFrame->Show();
}


LoadImageFrame::LoadImageFrame(MainFrame* window):
         wxPanel(window,
                 wxID_ANY,
                 wxDefaultPosition,
                 wxSize(WINDOW_WIDTH,
                 WINDOW_HEIGHT)),
                 _mainFrame(window) {
    _loadImageBt = std::make_unique<wxButton>(
                    this,
                    BUTTON_LOAD_IMAGE,
                    LOAD_IMAGE_LABEL,
                    wxPoint(WINDOW_WIDTH/2 - 50, WINDOW_HEIGHT/2 - 50));
}

void LoadImageFrame::OnLoadImageClick(wxCommandEvent& event) {
    wxFileDialog* _imageBrowseDialog = new
        wxFileDialog(
            this, "Choose an image to open", wxEmptyString, wxEmptyString,
            "Image files (*.bmp, *.jpg, *.jpeg, *.png)|*.bmp;*.jpg;*.jpeg;*.png;)",
            wxFD_OPEN, wxDefaultPosition);

    // Creates a "open file" dialog with 4 file types
    if (_imageBrowseDialog->ShowModal() == wxID_OK) {
        auto CurrentDocPath = std::string(_imageBrowseDialog->GetPath());
        _mainFrame->ShowBlurImageFrame(CurrentDocPath);
    }

    // Clean up after ourselves
    _imageBrowseDialog->Destroy();

    delete _imageBrowseDialog;
}

BlurImageFrame::BlurImageFrame(
                MainFrame* window,
                std::string imagePath): wxPanel(
                                            window,
                                            wxID_ANY,
                                            wxDefaultPosition,
                                            wxSize(WINDOW_WIDTH,
                                            WINDOW_HEIGHT)),
                                            _imagePath(imagePath) {
    wxSize imageContainerSize(680, 300);

    _imagePool = std::make_unique<ImgPool>(_imagePath);

    _blurSlider = std::make_unique<wxSlider>(
        this,
        SLIDER_SIGMA,
        0,
        0,
        20,
        wxDefaultPosition,
        wxSize(WINDOW_WIDTH, wxDefaultSize.GetHeight()));

    _blurSlider->SetPageSize(10);

    _imagePanel = std::make_unique<CustomImagePanel>(
        this, _imagePool->AskFor(0), imageContainerSize);
}

void BlurImageFrame::OnSigmaChanged(wxScrollEvent& event) {
    std::lock_guard<std::mutex> lck(mtx);
    std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
   
    std::chrono::duration<float> duration = now - lastSigmaChangedTime;
    if (duration.count() < SIGMA_CHANGE_DEBOUNCE_TIME) return;
    lastSigmaChangedTime = now;

    int currentPosition = event.GetPosition();
    if (currentPosition != lastSelectedSigma && _blurSlider->GetValue() == currentPosition){
        lastSelectedSigma = currentPosition;
        
        _imagePanel->ReplaceImage(_imagePool->AskFor(currentPosition));
    }
}

CustomImagePanel::CustomImagePanel(wxPanel *parent, std::shared_ptr<Img> currentImage, wxSize containerSize) :
 wxPanel(parent, wxID_ANY, wxPoint(20,120), containerSize), _currentImage(currentImage) {}

void CustomImagePanel::paintEvent(wxPaintEvent &evt) {
    wxPaintDC dc(this);
    render(dc);
}

void CustomImagePanel::paintNow() {
    wxClientDC dc(this);
    render(dc);
}

void CustomImagePanel::render(wxDC &dc) {
    dc.DrawBitmap(_currentImage->toWxBitmap(this->GetSize().GetWidth(), this->GetSize().GetHeight()), 0, 0, false);
}

void CustomImagePanel::ReplaceImage(std::shared_ptr<Img> img) {
    _currentImage = img;
    this->Refresh();
}

BEGIN_EVENT_TABLE(CustomImagePanel, wxPanel)
EVT_PAINT(CustomImagePanel::paintEvent) // catch paint events
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(LoadImageFrame, wxPanel)
EVT_BUTTON (BUTTON_LOAD_IMAGE, LoadImageFrame::OnLoadImageClick )
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(BlurImageFrame, wxPanel)
EVT_COMMAND_SCROLL(SLIDER_SIGMA, BlurImageFrame::OnSigmaChanged) // catch scroll events on SLIDER_SIGMA
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(MainPanelDialog, wxPanel)
EVT_PAINT(MainPanelDialog::paintEvent) // catch paint events
END_EVENT_TABLE()


MainPanelDialog::MainPanelDialog(wxWindow *parent, wxWindowID id) {}


void MainPanelDialog::paintEvent(wxPaintEvent &evt) {
    wxPaintDC dc(this);
    render(dc);
}


void MainPanelDialog::paintNow() {
    wxClientDC dc(this);
    render(dc);
}

void MainPanelDialog::render(wxDC &dc) {
    dc.DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}
