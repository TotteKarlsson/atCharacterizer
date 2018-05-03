#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include <vector>
#include "atRenderClient.h"
//#include "dslExeFile.h"
#include "dslMathUtils.h"
#include "dslTMemoLogger.h"
#include "TSelectZsForm.h"
#include "TImageForm.h"
#include "atApplicationSupportFunctions.h"
#include "TOverlayedImage.h"
#include "atVolumeCreatorProject.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "dslTIntLabel"
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTIniFileC"
#pragma link "dslTIntegerEdit"
#pragma link "TSSHFrame"
#pragma link "TImageControlsFrame"
#pragma link "TParaConverterFrame"

#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTIniFileC"
#pragma link "dslTIntegerEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTIntLabel"
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
TMainForm *MainForm;

using namespace dsl;
using namespace std;
TImage *CurrImage;
extern string gAppDataLocation;
extern string gLogFileName;

//__fastcall      TRegistryForm(const string& regRoot, const string& formName, TComponent* Owner);
//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TRegistryForm(gApplicationRegistryRoot, "MainForm", Owner),
    mLogLevel(lAny),
    mLogFileReader(joinPath(gAppDataLocation, gLogFileName), logMsg),
    mBottomPanelHeight(205),

    mIsStyleMenuPopulated(false),
	gImageForm(NULL),
    mProjectManager((*ProjectTView)),
    mAppProperties("VolumeCreator", gApplicationRegistryRoot, "")
{
    setupIniFile();
    setupAndReadIniParameters();
  	TMemoLogger::mMemoIsEnabled = true;
	CurrImage = Image1;
}

__fastcall TMainForm::~TMainForm()
{
	delete gImageForm;
}

//#define ThrowWandException(wand) \
//{ \
//  char \
//    *description; \
// \
//  ExceptionType \
//    severity; \
// \
//  description=MagickGetException(wand,&severity); \
//  (void) fprintf(stderr,"%s %s %lu %s\n",GetMagickModule(),description); \
//  description=(char *) MagickRelinquishMemory(description); \
//  exit(-1); \
//}
//
void ThrowWandException(MagickWand* wand)
{
  	char *description;
	ExceptionType severity;

  	description = MagickGetException(wand, &severity);
    Log(lInfo) << "ImageMagic encountered a problem: " <<description <<" in module "<<GetMagickModule();
  	description = (char *) MagickRelinquishMemory(description);
}

//---------------------------------------------------------------------------
TCanvas* TMainForm::getCanvas()
{
	return PaintBox1->Canvas;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormMouseDown(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
	if(Button == TMouseButton::mbRight)
    {
        return;
    }


	if(Button == TMouseButton::mbMiddle)
    {
    	//Open popup
       	Screen->Cursor = crSize;
    	//Open popup
		mTopLeftSelCorner = Mouse->CursorPos;
		mTopLeftSelCorner = this->Image1->ScreenToClient(mTopLeftSelCorner);

		//Convert to world image coords (minus offset)
//	    mTopLeftSelCorner = controlToImage(mTopLeftSelCorner, mScaleE->getValue(), stretchFactor);
//        Image1->Align = alNone;
        return;
    }

    Drawing = true;
    getCanvas()->MoveTo(X , Y);
    Origin = Point(X, Y);
    MovePt = Origin;

    //For selection
	mTopLeftSelCorner = Mouse->CursorPos;
	mTopLeftSelCorner = this->Image1->ScreenToClient(mTopLeftSelCorner);

	//Convert to world image coords (minus offset)
//    mTopLeftSelCorner = controlToImage(mTopLeftSelCorner, mScaleE->getValue(), stretchFactor);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y)
{
	TPoint p = this->Image1->ScreenToClient(Mouse->CursorPos);
	mXC->setValue(p.X);
	mYC->setValue(p.Y);

	//Convert to world image coords (minus offset)
	if(GetAsyncKeyState(VK_MBUTTON) < 0)
    {
    	//Move the picture
//        Image1->Top = Image1->Top + 1;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormMouseUp(TObject *Sender, TMouseButton Button,
          TShiftState Shift, int X, int Y)
{
//    double stretchFactor = getImageStretchFactor();
//	if(Button == TMouseButton::mbMiddle)
//    {
//	  	Screen->Cursor = crDefault;
//    	TPoint p2;
//		p2 = Mouse->CursorPos;
//		p2 = this->Image1->ScreenToClient(p2);
//	    p2 = controlToImage(p2, mScaleE->getValue(), stretchFactor);
//
//		//Convert to world image coords (minus offset)
//		XCoord->setValue(XCoord->getValue() + (mTopLeftSelCorner.X - p2.X));
//		YCoord->setValue(YCoord->getValue() + (mTopLeftSelCorner.Y - p2.Y));
//
//		mCurrentRB = RenderBox(XCoord->getValue(), YCoord->getValue(), Width->getValue(), Height->getValue(), mScaleE->getValue());
//       	ClickZ(Sender);
//    }
//
//	if(!Drawing ||  (Button == TMouseButton::mbRight))
//    {
//    	return;
//    }
//
//	Drawing = false;
//
//    //For selection
//	mBottomRightSelCorner = this->Image1->ScreenToClient(Mouse->CursorPos);
//
//	//Convert to world image coords (minus offset)
//    mBottomRightSelCorner = controlToImage(mBottomRightSelCorner, mScaleE->getValue(), stretchFactor);
//
//	//Check if selection indicate a 'reset'
//	if(mBottomRightSelCorner.X - mTopLeftSelCorner.X <= 0 || mBottomRightSelCorner.Y - mTopLeftSelCorner.Y <= 0)
//    {
//    	resetButtonClick(NULL);
//		return;
//    }
//
//	XCoord->setValue(XCoord->getValue() + mTopLeftSelCorner.X);
//	YCoord->setValue(YCoord->getValue() + mTopLeftSelCorner.Y);
//
//    Width->setValue(mBottomRightSelCorner.X - mTopLeftSelCorner.X);
//    Height->setValue(mBottomRightSelCorner.Y - mTopLeftSelCorner.Y);
//
//    updateScale();
//
//    //Add to render history
//    mCurrentRB = RenderBox(XCoord->getValue(), YCoord->getValue(), Width->getValue(), Height->getValue(), mScaleE->getValue());
//    mROIHistory.insert(mCurrentRB);
//
//    //Undo any flipping
//    FlipImageRightCB->Checked = false;
//    FlipImageLeftCB->Checked = false;
//	ClickZ(NULL);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
	if(Drawing)
  	{
		DrawShape(Origin, MovePt, pmNotXor);
		MovePt = Point(X, Y);
		DrawShape(Origin, MovePt, pmNotXor);
  	}

  	Image1MouseMove(Sender, Shift, X, Y);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::DrawShape(TPoint TopLeft, TPoint BottomRight, TPenMode AMode)
{
  	getCanvas()->Pen->Mode = AMode;
	getCanvas()->Rectangle(TopLeft.x, TopLeft.y, BottomRight.x, BottomRight.y);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormShow(TObject *Sender)
{
    if(mIsStyleMenuPopulated == false)
    {
        populateStyleMenu(ThemesMenu, ThemesMenuClick);
        mIsStyleMenuPopulated = true;
	}
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenaClone1Click(TObject *Sender)
{
	if(!gImageForm)
    {
    	gImageForm = new TImageForm(gApplicationRegistryRoot, "", this);
    }

	gImageForm->Show();
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::AddOverlayedImage1Click(TObject *Sender)
{
	TOverlayedImage* f = new TOverlayedImage(NULL);
    f->Show();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjectTViewEditing(TObject *Sender, TTreeNode *Node,
          bool &AllowEdit)
{
	AllowEdit = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjectTViewEdited(TObject *Sender, TTreeNode *Node,
          UnicodeString &S)
{
	//Update underlying object with new valuse..
    VolumeCreatorProject* vcp = (VolumeCreatorProject*) Node->Data;
    if(vcp)
    {
    	vcp->setProjectName(stdstr(S));
        vcp->setModified();
		SaveProjectA->Update();
    }
}

void __fastcall TMainForm::EditViewNodeExecute(TObject *Sender)
{
	TTreeNode* item = ProjectTView->Selected;
    if(item)
    {
    	item->EditText();
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ProjectTViewClick(TObject *Sender)
{
	//Get current node from the treeview
	TTreeNode* item = ProjectTView->Selected;
	mProjectManager.selectItem(item);

}



