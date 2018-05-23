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
#include "atTClassifierFrame.h"
#include "TFloatingButtonsForm.h"
#include "forms/TMagnifyForm.h"
#include <utility>
class TImageForm;
using std::pair;

//---------------------------------------------------------------------------
using dsl::ApplicationProperties;
using dsl::IniFileProperties;
using dsl::TRegistryProperties;
using dsl::IniSection;
extern string gApplicationRegistryRoot;
void brightnessContrast(TImage *imageSelected);
string createProcessedImageFileName(const string& fname);

class VolumeCreatorProject;

class TMainForm : public TRegistryForm
{
    friend TFloatingButtonsForm;
    friend TMagnifyForm;
__published:	// IDE-managed Components
	TImage *Image1;
	TMemo *infoMemo;
	TTimer *mShutDownTimer;
	TPanel *mBottomPanel;
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
	TSTDStringEdit *ImageFolderE;
	TGroupBox *ImageFilesGB;
	TPanel *ClassifierPanel;
	TSplitter *Splitter1;
	TActionList *ActionList1;
	TAction *YesA;
	TAction *NoA;
	TAction *MaybeA;
	TListBox *ImageFilesLB;
	TPopupMenu *listPopup;
	TAction *sortByValueA;
	TPanel *TopPanel;
	TButton *OpenCloseProjectBtn;
	TPanel *TopBackPanel;
	TButton *Button2;
	TAction *sortByFileNameA;
	TMenuItem *SortbyValue1;
	TMenuItem *sortByFileNameA1;
	TSTDStringEdit *UserE;
	TButton *Button1;
	TAction *ToggleButtonFrameDockedA;
	TMenuItem *Floatingbuttons1;
	TButton *Button3;
	TAction *ToggleMagnifyingGlassA;
	TAction *ToggleStretchingA;
	TMenuItem *oggleStretchingA1;
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
	void __fastcall ImageFilesLBClick(TObject *Sender);
	void __fastcall sortByValueAExecute(TObject *Sender);
	void __fastcall FileOpen1Accept(TObject *Sender);
	void __fastcall CloseProjectAExecute(TObject *Sender);
	void __fastcall NewProjectAExecute(TObject *Sender);
	void __fastcall SaveProjectAExecute(TObject *Sender);
	void __fastcall sortByFileNameAExecute(TObject *Sender);
	void __fastcall SaveProjectAsAExecute(TObject *Sender);
	void __fastcall FileOpen1Cancel(TObject *Sender);
	void __fastcall ToggleButtonFrameDockedAExecute(TObject *Sender);
	void __fastcall ClassifierPanelResize(TObject *Sender);
	void __fastcall ToggleMagnifyingGlassAExecute(TObject *Sender);
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall ToggleStretchingAExecute(TObject *Sender);
	void __fastcall ToggleStretchingAUpdate(TObject *Sender);
	void __fastcall ToggleMagnifyingGlassAUpdate(TObject *Sender);

	private:
        void __fastcall                                 logMsg();
		LogFileReader                                   mLogFileReader;
		bool          									mIsStyleMenuPopulated;

        ApplicationProperties                           mAppProperties;

        dsl::Property<int>	                            mBottomPanelHeight;
		dsl::Property<dsl::LogLevel>	                mLogLevel;


        TClassifierFrame*                               mCF;
                                                        //This file contains all the data for
                                                        //any particular "project"
        //IniFile                                         mClassifierFile;
        ClassifierBase                                  mClassifier;
		bool 											populateImagesLB(IniFile& values);


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

        bool                                            openProject(const string& fName);
        void                                            onCloseFolder();
        bool                                            isProjectOpen();
        auto_ptr<TFloatingButtonsForm>                  mFloatingButtonsForm;
	    auto_ptr<TMagnifyForm> 							mMagnifyForm;
        TPoint                                          mImageMouseCoord;
        TPoint                                          getImageMouseCoord();
        pair<double, double>                            getImageScaling();
		int 										    getImageWidth();
		int 											getImageHeight();

	public:
		__fastcall 					 					TMainForm(TComponent* Owner);
		__fastcall 					 					~TMainForm();
};

extern PACKAGE TMainForm *MainForm;
#endif
