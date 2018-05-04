#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include <vector>
#include "dslMathUtils.h"
#include "dslTMemoLogger.h"
#include "TImageForm.h"
#include "atApplicationSupportFunctions.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTFloatLabeledEdit"
#pragma link "dslTIniFileC"
#pragma link "dslTIntegerEdit"
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTIntLabel"
#pragma link "dslTPropertyCheckBox"
#pragma link "dslTSTDStringEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
//---------------------------------------------------------------------------

TMainForm *MainForm;

using namespace dsl;
using namespace std;
TImage *CurrImage;
extern string gAppDataLocation;
extern string gLogFileName;
extern string gAppName;

//---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
	: TRegistryForm(gApplicationRegistryRoot, "MainForm", Owner),
    mLogLevel(lAny),
    mLogFileReader(joinPath(gAppDataLocation, gLogFileName), logMsg),
    mBottomPanelHeight(205),

    mIsStyleMenuPopulated(false),
	gImageForm(NULL),
    mAppProperties(gAppName, gApplicationRegistryRoot, "")
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

	filesCLBClick(Sender);
}

void __fastcall TMainForm::BrowseForFolder1Accept(TObject *Sender)
{
	//Extract Folder
    if(!BrowseForFolder1->Folder.Length())
    {
        return;
    }

    mImageFolderE->setValue(stdstr(BrowseForFolder1->Folder));
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::BrowseForFolder1BeforeExecute(TObject *Sender)
{
	BrowseForFolder1->Folder = vclstr( mImageFolderE->getValue());
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CheckFolderBtnClick(TObject *Sender)
{
	if(CheckFolderBtn->Caption == "Close Folder")
    {
        onCloseFolder();
    }
    else
    {
        onOpenFolder();
    }
}

void  TMainForm::onOpenFolder()
{
	mCharacterizationFile.clear();

    //Check for characterization file. If not exist, create a new one.
    string characterizationFileName(joinPath(mImageFolderE->getValue(), UserE->getValue() + "_Classifications.txt"));
    if(!fileExists(characterizationFileName))
    {
        Log(lInfo) << "Creating characterization file: " << characterizationFileName;
        createFile(characterizationFileName);
    }

    Log(lInfo) << "Loading characterization file: " << characterizationFileName;
    if(!mCharacterizationFile.load(characterizationFileName))
    {
        Log(lError) << "Failed loading characterization file: " << characterizationFileName;
    }

    //Check current folder for files and populate list box
	StringList files = getFilesInDir(mImageFolderE->getValue(), "png", false);

    //Create ini file section
    IniSection* sec = mCharacterizationFile.getSection(mImageFolderE->getValue(), true); //Autocreate section
    if(!sec)
    {

    }

    //Make sure the section has the same number of keys as images
    if(sec->keyCount() != files.count())
    {
        for(int i = 0; i < files.count(); i++)
        {
        	//Populate keys
	        IniKey* aKey = sec->getKey(getFileNameNoPathNoExtension(files[i]), true);
            if(!aKey)
            {
                Log(lError) << "Failed creating key: " << getFileNameNoPathNoExtension(files[i]);
            }
            if(!aKey->mValue.size())
            {
				aKey->mValue = "-";
            }
        }
    }

    //Populate list box from the keys..
	filesCLB->Clear();
    for(size_t i = 0; i < sec->keyCount(); i++)
    {
        IniKey* key = sec->getKey(i);
        if(key)
        {
            string item(key->mKey);
            item = item + " " + key->mValue;
        	filesCLB->Items->AddObject(vclstr(item), (TObject*) key );
        }
    }

    CheckFolderBtn->Caption = "Close Folder";
    enableDisablePanel(ProjFilePathPanel, false);
    enableDisablePanel(ActionbuttonsPanel, true);
}

void   TMainForm::onCloseFolder()
{
    mCharacterizationFile.save();
    UserE->Enabled = true;
    filesCLB->Clear();
    CheckFolderBtn->Caption = "Open Folder";
    enableDisablePanel(ProjFilePathPanel, true);
    enableDisablePanel(ActionbuttonsPanel, false);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::filesCLBClick(TObject *Sender)
{
    //Extract filename and show image
    int index = filesCLB->ItemIndex;

    IniKey* key = (IniKey*) filesCLB->Items->Objects[index];
    if(!key)
    {
        Log(lError) << "No Such file: " <<key->mKey;
        return;
    }
    string fName(joinPath(mImageFolderE->getValue(), key->mKey + ".png"));

    Image1->Picture->LoadFromFile(fName.c_str());
    Log(lInfo) << "Opened file: " << fName.c_str();

    if(gImageForm)
    {
        gImageForm->load(fName);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CharacterizeAction(TObject *Sender)
{
	int idx = filesCLB->ItemIndex;
    //Extract key
    IniKey* key = (IniKey*) filesCLB->Items->Objects[idx];
    if(!key)
    {
        Log(lError) << "Bad key..";
    }

    Log(lInfo) << "Updating synaptogram: " << key->mKey;

    TAction* a = dynamic_cast<TAction*>(Sender);
    if(a == YesA)
    {
        Log(lInfo) <<  "Yes action";
        //Add.change value
        key->mValue = "Yes";
    }
    else if(a == NoA)
    {
        Log(lInfo) <<  "No action";
        key->mValue = "No";
    }
    else if(a = MaybeA)
    {
        Log(lInfo) <<  "Maybe action";
        key->mValue = "Pass";
    }

    //Update item in listbox
	filesCLB->Items->Strings[idx] = string(key->mKey + " " + key->mValue).c_str();

    //Auto advance..
    if(idx < filesCLB->Count)
    {
		filesCLB->ItemIndex = filesCLB->ItemIndex + 1;
        filesCLBClick(NULL);
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_ESCAPE)
    {
        Close();
    }
    char ch = Key;

    switch(ch)
    {
        case 's':
        case 'S':     		SendMessage(YesBtn->Handle, BM_CLICK, 0, 0);      break;

        case 'd':
        case 'D':           SendMessage(MaybeBtn->Handle, BM_CLICK, 0, 0);     break;

        case 'F':
        case 'f':           SendMessage(NoBtn->Handle, BM_CLICK, 0, 0);      break;
    }

    filesCLB->SetFocus();
}



