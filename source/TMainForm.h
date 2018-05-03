#ifndef TMainFormH
#define TMainFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include "dslTFloatLabeledEdit.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.CheckLst.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdHTTP.hpp>
#include <IdTCPClient.hpp>
#include <IdTCPConnection.hpp>
#include "dslLogFileReader.h"
#include "dslLogLevel.h"
#include <Vcl.ComCtrls.hpp>
#include "dslTIntLabel.h"
#include "dslTPropertyCheckBox.h"
#include "dslIniFileProperties.h"
#include "dslRegistryProperties.h"
#include "dslTIniFileC.h"
#include "dslApplicationProperties.h"
#include "atFetchImagesThread.h"
#include <Vcl.Menus.hpp>
#include "dslTIntegerEdit.h"
#include "TSSHFrame.h"
#include "TImageControlsFrame.h"
#include "MagickWand/MagickWand.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.ImgList.hpp>
#include "atProjectManager.h"
#include <System.ImageList.hpp>
#include "dslTRegistryForm.h"
#include "dslTFloatLabeledEdit.h"
#include "dslTIniFileC.h"
#include "dslTIntegerEdit.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTIntLabel.h"
#include "dslTPropertyCheckBox.h"
#include "dslTSTDStringLabeledEdit.h"
#include "dslTSTDStringEdit.h"
class TImageForm;
//using dsl::Process;
//---------------------------------------------------------------------------
using dsl::IniFileProperties;
using dsl::TRegistryProperties;
extern string gApplicationRegistryRoot;
void brightnessContrast(TImage *imageSelected);
string createProcessedImageFileName(const string& fname);

class VolumeCreatorProject;

class TMainForm : public TRegistryForm
{
__published:	// IDE-managed Components
	TImage *Image1;
	TMemo *infoMemo;
	TTimer *mShutDownTimer;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TSplitter *Splitter1;
	TPanel *mBottomPanel;
	TPaintBox *PaintBox1;
	TIniFileC *mIniFileC;
	TPanel *Panel2;
	TButton *mCLearMemo;
	TSplitter *Splitter2;
	TButton *mCloseBottomPanelBtn;
	TButton *mShowBottomPanelBtn;
	TPanel *mLogPanel;
	TPanel *Panel5;
	TIntLabel *mXC;
	TIntLabel *mYC;
	TGroupBox *GroupBox8;
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Help1;
	TMenuItem *About1;
	TPopupMenu *ImagePopup;
	TMenuItem *ParseNDVIZURL1;
	TMenuItem *Exit1;
	TMenuItem *Options1;
	TMenuItem *ThemesMenu;
	TStatusBar *StatusBar1;
	TMenuItem *OpenaClone1;
	THeaderControl *HeaderControl1;
	TPanel *Panel1;
	TMenuItem *AddOverlayedImage1;
	TMenuItem *Open1;
	TActionList *MenuActions;
	TFileOpen *FileOpen1;
	TToolBar *ToolBar1;
	TToolButton *ToolButton1;
	TMenuItem *New1;
	TAction *NewProjectA;
	TSaveDialog *SaveDialog1;
	TAction *SaveProjectA;
	TMenuItem *Save1;
	TAction *SaveProjectAsA;
	TMenuItem *SaveAs1;
	TAction *CloseProjectA;
	TMenuItem *Close1;
	TImageList *ImageList1;
	TToolButton *ToolButton2;
	TToolButton *ToolButton3;
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *Reopen;
	TMenuItem *N3;
	TPanel *ProjFilePathPanel;
	TAction *AddRenderProject;
	TPanel *MainPanel;
	TAction *EditViewNode;
	TButton *mBrowseForCacheFolder;
	TSTDStringEdit *mImageFolderE;
	TBrowseForFolder *BrowseForFolder1;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall mShutDownTimerTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall FormMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall FormMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall mCLearMemoClick(TObject *Sender);
	void __fastcall mCloseBottomPanelBtnClick(TObject *Sender);
	void __fastcall mShowBottomPanelBtnClick(TObject *Sender);
	void __fastcall About1Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ThemesMenuClick(TObject *Sender);
	void __fastcall OpenaClone1Click(TObject *Sender);
	void __fastcall AddOverlayedImage1Click(TObject *Sender);
	void __fastcall BrowseForFolder1Accept(TObject *Sender);

	private:	// User declarations
       	void __fastcall 								DrawShape(TPoint TopLeft, TPoint BottomRight, TPenMode AMode);
        void __fastcall                                 logMsg();
		LogFileReader                                   mLogFileReader;
		bool          									mIsStyleMenuPopulated;
        ApplicationProperties                           mAppProperties;
        IniFileProperties	      	                    mGeneralProperties;
        dsl::Property<int>	                            mBottomPanelHeight;
		dsl::Property<dsl::LogLevel>	                mLogLevel;

        bool                                            setupAndReadIniParameters();
        void                                            setupIniFile();

        //Drawing stuff
        TBrushStyle 									BrushStyle;
        TPenStyle 										PenStyle;
        int 											PenWide;
        bool 											Drawing;
        TPoint 											Origin;
        TPoint 											MovePt;
        TPoint											mTopLeftSelCorner;
        TPoint											mBottomRightSelCorner;

        //Render areas history
      	TCanvas*										getCanvas();

        //Remote jobs
	    TImageForm*										gImageForm;
        string 											mCurrentImageFile;

	public:
		__fastcall 					 					TMainForm(TComponent* Owner);
		__fastcall 					 					~TMainForm();
};

extern PACKAGE TMainForm *MainForm;
#endif
