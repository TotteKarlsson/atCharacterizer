#include <vcl.h>
#pragma hdrstop
#include "TMagnifyForm.h"
#include <sstream>
#include "TMainForm.h"
#include "dslLogger.h"
#include <utility>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

using namespace std;
using namespace dsl;
TMagnifyForm *MagnifyForm;
//---------------------------------------------------------------------------
__fastcall TMagnifyForm::TMagnifyForm(TMainForm* mf)
	: TRegistryForm(gApplicationRegistryRoot, "MagnificationForm", mf),
    mMainForm(mf),
    mIsMagnifying(false),
    mZoomFactor(1.5)
{
	Timer1->Enabled = true;
    this->ControlStyle << csOpaque;

    //Alwasy start with default size
    this->Width = 300;
    this->Height = 170;
}

//---------------------------------------------------------------------------
__fastcall TMagnifyForm::~TMagnifyForm()
{}

bool TMagnifyForm::loadImage(const string& fName)
{
    try
    {
    	Image1->Picture->LoadFromFile(fName.c_str());
	    Log(lInfo) << "Opened file: " << fName.c_str();
	    return true;
    }
    catch(...)
    {
	    return false;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMagnifyForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
	   	Timer1->Enabled = false;
        Hide();
    }
    //forward keys to main form
    mMainForm->OnKeyDown(Sender, Key, Shift);
}

//---------------------------------------------------------------------------
void __fastcall TMagnifyForm::Image1MouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
  	Timer1->Enabled = true;
	int sc_DragMove = 0xF012;
    ReleaseCapture();
    Perform(WM_SYSCOMMAND, sc_DragMove, 0);
    mIsMagnifying = true;
}

//---------------------------------------------------------------------------
void __fastcall TMagnifyForm::FormShow(TObject *Sender)
{
    //Scale image
    Image1->Width = mZoomFactor * Image1->Picture->Width;
    Image1->Height= mZoomFactor * Image1->Picture->Height;
    render();
}

//---------------------------------------------------------------------------
void __fastcall TMagnifyForm::Image1MouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
}

//---------------------------------------------------------------------------
void TMagnifyForm::render()
{
    //Apply scaling
	Image1->Stretch = 	mMainForm->Image1->Stretch;
    Image1->Width 	= mMainForm->Image1->Width * mZoomFactor;
    Image1->Height 	= mMainForm->Image1->Height * mZoomFactor;

    TPoint p1;
    p1 = mMainForm->Image1->ClientToScreen(TPoint(0,0));
    TPoint p2 = this->ScreenToClient(p1);
    //For a zoom factor of one, doing this works
    //Image1->Left = p2.X;
    //Image1->Top = p2.Y;

    //Get A, expressed in this forms frame
    TPoint magFrameOrigin(this->Width/2, this->Height/2);

    //Express in screen coords
	magFrameOrigin = ClientToScreen(magFrameOrigin);

    //Express in  user Image fram
    magFrameOrigin = mMainForm->Image1->ScreenToClient(magFrameOrigin);

    TPoint p3(magFrameOrigin);

    //We move the image control in order to show proper part of image
    Image1->Left = p2.X + (-1) * (mZoomFactor -1) * p3.X;
    Image1->Top = p2.Y  + (-1) * (mZoomFactor -1) * p3.Y;
}

//---------------------------------------------------------------------------
void __fastcall TMagnifyForm::Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y)
{
    mIsMagnifying = false;
    Log(lInfo) << "Mouse is up";
}

//---------------------------------------------------------------------------
void __fastcall TMagnifyForm::Timer1Timer(TObject *Sender)
{
    //Check if left mouse is down
    if((GetKeyState(VK_LBUTTON) & 0x100) != 0)
    {
        render();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMagnifyForm::MagMenuClick(TObject *Sender)
{
    TMenuItem* i = dynamic_cast<TMenuItem*>(Sender);

    //Uncheck any item
    for(int i = 0; i < 4; i++)
    {
    	PopupMenu1->Items->operator [](i)->Checked = false;
    }

    if(!i)
    {
        return;
    }

    if(i == OneP5X)
    {
    	mZoomFactor = 1.5;
    }
    else if(i == TwoX)
    {
		mZoomFactor = 2;
    }
    else if(i == ThreeX)
    {
		mZoomFactor = 3;
    }
    else if(i == FourX)
    {
		mZoomFactor = 4;
    }

    i->Checked = true;
    render();
}

//---------------------------------------------------------------------------
void __fastcall TMagnifyForm::FormSizeClick(TObject *Sender)
{
    TMenuItem* i = dynamic_cast<TMenuItem*>(Sender);
    if(!i)
    {
        return;
    }

    //Uncheck any item
    for(int i = 4; i < PopupMenu1->Items->Count; i++)
    {
    	PopupMenu1->Items->operator [](i)->Checked = false;
    }

    //Size of form
    if(i == SmallSquare)
    {
        this->Width = 150;
        this->Height = 150;
    }
    else if(i == BigSquare)
    {
        this->Width = 450;
        this->Height = 450;
    }
    else if(i == DefaultFormSize)
    {
        this->Width = 300;
        this->Height = 170;
    }

    i->Checked = true;
    render();
}

//---------------------------------------------------------------------------
void __fastcall TMagnifyForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    Timer1->Enabled = false;
}

//---------------------------------------------------------------------------
void __fastcall TMagnifyForm::HideFormExecute(TObject *Sender)
{
    Hide();
}


