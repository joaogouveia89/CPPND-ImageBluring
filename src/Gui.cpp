#include "Gui.h"
#include <wx/file.h>
#include <wx/mstream.h>
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
        window, imagePath
    );
}

CustomImagePanel::CustomImagePanel(wxFrame *parent, std::string imagePath) :
 wxPanel(parent, wxID_ANY, wxPoint(20,100), wxSize(680, 300)), _imagePath(imagePath) {}

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
    wxFile file(_imagePath);
    if (file.IsOpened())
    {
        wxFileOffset len = file.Length();
        size_t dataSize = (size_t)len;
        void *data = malloc(dataSize);
         if ( file.Read(data, dataSize) != len )
        {
            wxLogError("Reading bitmap file failed");
        }
        else
        {
            wxMemoryInputStream stream(data, dataSize);
            wxSize sz = this->GetSize();
            _image.LoadFile(stream, wxBITMAP_TYPE_BMP);
            wxImage reescaled = _image.Rescale(sz.GetWidth(), sz.GetHeight(), wxIMAGE_QUALITY_HIGH);
            dc.DrawBitmap(reescaled, 0, 0, false);
        }
    }
    else{
        wxLogError("Could not load image file");
    }
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