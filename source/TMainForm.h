#ifndef TMainFormH
#define TMainFormH
#include "dslApplicationProperties.h"
#include "dslIniFileProperties.h"
#include "dslLogFileReader.h"
#include "dslLogLevel.h"
#include "dslRegistryProperties.h"
#include "dslTFloatLabeledEdit.h"
#include "dslTIniFileC.h"
#include "dslTIntegerEdit.h"
#include "dslTIntegerLabeledEdit.h"
#include "dslTIntLabel.h"
#include "dslTPropertyCheckBox.h"
#include "dslTRegistryForm.h"
#include "dslTSTDStringEdit.h"
#include "dslTSTDStringLabeledEdit.h"
#include "MagickWand/MagickWand.h"
#include <System.Actions.hpp>
#include <System.Classes.hpp>
#include <System.ImageList.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.CheckLst.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ExtDlgs.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Imaging.pngimage.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include "TArrayBotBtn.h"

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
	TPanel *mBottomPanel;
	TPaintBox *PaintBox1;
	TIniFileC *mIniFileC;
	TPanel *Panel2;
	TButton *mCLearMemo;
	TSplitter *Splitter2;
	TButton *mCloseBottomPanelBtn;
	TButton *mShowBottomPanelBtn;
	TPanel *mLogPanel;
	TMainMenu *MainMenu1;
	TMenuItem *File1;
	TMenuItem *Help1;
	TMenuItem *About1;
	TPopupMenu *ImagePopup;
	TMenuItem *Exit1;
	TMenuItem *Options1;
	TMenuItem *ThemesMenu;
	TStatusBar *StatusBar1;
	TMenuItem *OpenaClone1;
	THeaderControl *HeaderControl1;
	TPanel *Panel1;
	TMenuItem *Open1;
	TActionList *MenuActions;
	TFileOpen *FileOpen1;
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
	TMenuItem *N1;
	TMenuItem *N2;
	TMenuItem *Reopen;
	TMenuItem *N3;
	TPanel *ProjFilePathPanel;
	TPanel *MainPanel;
	TAction *EditViewNode;
	TButton *mBrowseForCacheFolder;
	TSTDStringEdit *mImageFolderE;
	TBrowseForFolder *BrowseForFolder1;
	TCheckListBox *filesCLB;
	TGroupBox *GroupBox1;
	TButton *CheckFolderBtn;
	TSTDStringEdit *UserE;
	TPanel *ActionbuttonsPanel;
	TArrayBotButton *YesBtn;
	TArrayBotButton *MaybeBtn;
	TArrayBotButton *NoBtn;
	TSplitter *Splitter1;
	TActionList *ActionList1;
	TAction *YesA;
	TAction *NoA;
	TAction *MaybeA;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall mShutDownTimerTimer(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
	void __fastcall mCLearMemoClick(TObject *Sender);
	void __fastcall mCloseBottomPanelBtnClick(TObject *Sender);
	void __fastcall mShowBottomPanelBtnClick(TObject *Sender);
	void __fastcall About1Click(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall Exit1Click(TObject *Sender);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall ThemesMenuClick(TObject *Sender);
	void __fastcall OpenaClone1Click(TObject *Sender);
	void __fastcall BrowseForFolder1Accept(TObject *Sender);
	void __fastcall BrowseForFolder1BeforeExecute(TObject *Sender);
	void __fastcall CheckFolderBtnClick(TObject *Sender);
	void __fastcall filesCLBClick(TObject *Sender);
	void __fastcall CharacterizeAction(TObject *Sender);

	private:	// User declarations
        void __fastcall                                 logMsg();
		LogFileReader                                   mLogFileReader;
		bool          									mIsStyleMenuPopulated;

        ApplicationProperties                           mAppProperties;
        IniFileProperties	      	                    mGeneralProperties;
        dsl::Property<int>	                            mBottomPanelHeight;
		dsl::Property<dsl::LogLevel>	                mLogLevel;
        IniFile                                         mCharacterizationFile;
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

        //Remote jobs
	    TImageForm*										gImageForm;

        void                                            onOpenFolder();
        void                                            onCloseFolder();

	public:
		__fastcall 					 					TMainForm(TComponent* Owner);
		__fastcall 					 					~TMainForm();
};

extern PACKAGE TMainForm *MainForm;
#endif
