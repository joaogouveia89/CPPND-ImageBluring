#include "Gui.h"
#include <iostream>

IMPLEMENT_APP(ImageBlurringApp);

bool ImageBlurringApp::OnInit()
{
    // create window with name and show it
    MainFrame *main = new MainFrame();
    main->Show(true);

    return true;
}

MainFrame::MainFrame(): wxFrame(NULL, wxID_ANY, APP_NAME, wxDefaultPosition, wxSize(WINDOW_WIDTH, WINDOW_HEIGHT))
{ 
    ShowLoadingImageFrame();
    this->Centre();
}

void MainFrame::ShowLoadingImageFrame()
{
    if(_loadImageFrame == nullptr)
    {
        _loadImageFrame = std::make_unique<LoadImageFrame>(this);
    }
    _blurImageFrame = nullptr;
    
    _loadImageFrame->Show();
}

void MainFrame::ShowBlurImageFrame(std::string imagePath)
{
    if(_blurImageFrame == nullptr)
    {
        _blurImageFrame = std::make_unique<BlurImageFrame>(this, imagePath);
    }
    if(_loadImageFrame != nullptr)
    {
        _loadImageFrame->Hide();
    }
    _blurImageFrame->Show();
}


LoadImageFrame::LoadImageFrame(MainFrame* window): wxPanel(window), _mainFrame(window)
{
    _loadImageBt = std::make_unique<wxButton*>(new wxButton(this, BUTTON_LOAD_IMAGE, LOAD_IMAGE_LABEL , wxPoint(WINDOW_WIDTH/2 - 50, WINDOW_HEIGHT/2 - 50)));
}


void LoadImageFrame::OnLoadImageClick( wxCommandEvent& event )
{
    wxFileDialog* _imageBrowseDialog = new
        wxFileDialog(
            this, "Choose an bitmap to open", wxEmptyString, wxEmptyString, 
            "Bitmap files (*.bmp)|*.bmp;)",
            wxFD_OPEN, wxDefaultPosition
        );

    // Creates a "open file" dialog with 4 file types
	if (_imageBrowseDialog->ShowModal() == wxID_OK) // if the user click "Open" instead of "Cancel"
	{
		auto CurrentDocPath = std::string(_imageBrowseDialog->GetPath());
        _mainFrame->ShowBlurImageFrame(CurrentDocPath);
	}

	// Clean up after ourselves
	_imageBrowseDialog->Destroy();

    delete _imageBrowseDialog;
}

BlurImageFrame::BlurImageFrame(MainFrame* window, std::string imagePath): wxPanel(window), _imagePath(imagePath)
{
    wxSize imageContainerSize(680, 300);

    std::shared_ptr<Img> img = std::make_shared<Img>(_imagePath, imageContainerSize);

    _blurSlider = std::make_unique<wxSlider>(
        window,
        wxID_ANY,
        0,
        0,
        100,
        wxDefaultPosition,
        wxSize(WINDOW_WIDTH, wxDefaultSize.GetHeight())
    );

    _imagePanel = std::make_unique<CustomImagePanel>(
        window, std::move(img), imageContainerSize
    );
}

CustomImagePanel::CustomImagePanel(wxFrame *parent, std::shared_ptr<Img> currentImage, wxSize containerSize) :
 wxPanel(parent, wxID_ANY, wxPoint(20,100), containerSize), _currentImage(currentImage) {}

void CustomImagePanel::paintEvent(wxPaintEvent &evt)
{
    wxPaintDC dc(this);
    render(dc);
}

void CustomImagePanel::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

void CustomImagePanel::render(wxDC &dc)
{
    dc.DrawBitmap(_currentImage->Bitmap(), 0, 0, false);
}

BEGIN_EVENT_TABLE(CustomImagePanel, wxPanel)
EVT_PAINT(CustomImagePanel::paintEvent) // catch paint events
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(LoadImageFrame, wxPanel)
EVT_BUTTON (BUTTON_LOAD_IMAGE, LoadImageFrame::OnLoadImageClick )
END_EVENT_TABLE()

BEGIN_EVENT_TABLE(MainPanelDialog, wxPanel)
EVT_PAINT(MainPanelDialog::paintEvent) // catch paint events
END_EVENT_TABLE()

MainPanelDialog::MainPanelDialog(wxWindow *parent, wxWindowID id){}


void MainPanelDialog::paintEvent(wxPaintEvent &evt)
{
    wxPaintDC dc(this);
    render(dc);
}


void MainPanelDialog::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

void MainPanelDialog::render(wxDC &dc)
{
    dc.DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
}