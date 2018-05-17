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
#include "forms/TNewProjectForm.h"
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
	:
    TRegistryForm(gApplicationRegistryRoot, "MainForm", Owner),
    mAppProperties(gAppName, gApplicationRegistryRoot, ""),
    mLogLevel(lAny),
    mLogFileReader(joinPath(gAppDataLocation, gLogFileName), logMsg),
    mBottomPanelHeight(205),
    mIsStyleMenuPopulated(false),
	gImageForm(NULL)
{
    setupAndReadIniParameters();
  	TMemoLogger::mMemoIsEnabled = true;
	CurrImage = Image1;
}

__fastcall TMainForm::~TMainForm()
{
	delete gImageForm;
    delete mCF;
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

bool TMainForm::isProjectOpen()
{
    return ClassifierPanel->Enabled;
}

bool TMainForm::openProject(const string& fName)
{
    IniFile& values = mClassifier.getProjectValues();
    //Start with an empty project, and popualte from file
	values.clear();

    //Populate "ini file"
    Log(lInfo) << "Loading project from file: " << fName;
    if(!values.load(fName))
    {
        Log(lError) << "Failed loading project file: " << fName;
    }

    //Get SETTINGS section
    IniSection* settings = values.getSection("SETTINGS", true); //Autocreate section
    if(!settings)
    {
        Log(lError) << "Failed creating \"SETTINGS\" section";
        return false;
    }

    IniKey* user = settings->getKey("USER", true);
    if(!user)
    {
        Log(lError) << "Failed creating \"USER\" key";
        return false;
    }

    if(user->mValue.size() == 0)
    {
        user->mValue = UserE->getValue();
    }
    else
    {
        UserE->setValue(user->mValue);
    }

    IniKey* imageFolder = settings->getKey("IMAGE_FOLDER", true);
    if(!imageFolder)
    {
        Log(lError) << "Failed creating \"IMAGE_FOLDER\" key";
        return false;
    }

    if(imageFolder->mValue.size() != 0)
    {
        //Verify that the currently selecte image folder
        //matches what is written in the file
        if(ImageFolderE->getValue() != imageFolder->mValue)
        {
            MessageDlg("This file seem to belong to a different folder!\nMake sure you know what you are doing..!", mtError, TMsgDlgButtons() << mbOK, 0);
        }
    }
    else
    {
		imageFolder->mValue = ImageFolderE->getValue();
    }

    //Setup classes
    IniSection* classes = values.getSection("CLASSES", true); //Autocreate section
    if(!classes)
    {
        Log(lError) << "Failed creating \"VALUES\" section";
        return false;
    }

    if(classes->keyCount() == 0)
    {
        //Add from classifier (when new project)
        StringList s = mClassifier.getClassLabels();
        for(int i = 0; i < s.count(); i++)
        {
            IniKey* k = classes->getKey(s[i], true);
            if(!k)
            {
                Log(lError) << "Problem creating key...";
            }
            else
            {
                k->mValue = dsl::toString(i + 1);
            }
        }
    }
    else
    {
	    //Populate internal classifier list when reading from file
    	mClassifier.updateClasses();
    }

    populateImagesLB(values);

    //Now populate the classifier frame..
	mCF = new TClassifierFrame(mClassifier, *ImageFilesLB, this);
    mCF->Parent = ClassifierPanel;
    mCF->Align = alClient;
    mCF->populate();

    //Add switch to button form action to popup
    TMenuItem* i = new TMenuItem(mCF->PopupMenu1);
    i->Action = ToggleButtonFrameDockedA;
    mCF->PopupMenu1->Items->Add(i);
    enableDisablePanel(ProjFilePathPanel, false);
    enableDisablePanel(ClassifierPanel, true);
    values.save();
    return true;
}

bool  TMainForm::populateImagesLB(IniFile& values)
{
    //Check current folder for files and populate list box
	StringList files = getFilesInDir(ImageFolderE->getValue(), "png", false);

    //Create ini file section
    IniSection* sec = values.getSection("VALUES", true); //Autocreate section
    if(!sec)
    {
        Log(lError) << "Failed creating \"VALUES\" section";
        return false;
    }

    //Make sure the section has the same number of keys as images in the folder
    if(sec->keyCount() != files.count())
    {
        if(sec->keyCount() != 0)
        {
            Log(lError) << "This file contain different number of records than is present in the folder!";
			Log(lError) << "Seem file is corrupt for some reason. Stop here and check file by ahnd before continuing!";
            return false;
        }

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
	ImageFilesLB->Clear();
    for(size_t i = 0; i < sec->keyCount(); i++)
    {
        IniKey* key = sec->getKey(i);
        if(key)
        {
            string item(key->mKey);
            item = item + " " + key->mValue;
        	ImageFilesLB->Items->AddObject(vclstr(item), (TObject*) key );
        }
    }
    return true;
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if(Key == VK_ESCAPE)
    {
        Close();
    }


    string sCh;
  	sCh = (Shift.Contains(ssShift)) ? stdstr(Char(Key)) : stdstr(LowerCase(Char(Key)));
    char ch = sCh[0];

    Log(lDebug3) << "Key " << ch <<" was pressed";

    if(!isProjectOpen())
    {
        return;
    }

    //Find the button with key == ch
    shared_ptr<TArrayBotButton> btn = mCF->getButtonWithKey(ch);
    if(btn)
    {
        SendMessage(btn->Handle, BM_CLICK, 0, 0);
    }
}

int __fastcall SortListByValue (TStringList* sl, int item1, int item2)
{
    IniKey* k1 = (IniKey*) sl->Objects[item1];
    IniKey* k2 = (IniKey*) sl->Objects[item2];
    return CompareStr(k1->mValue.c_str(), k2->mValue.c_str()) * -1;
}

int __fastcall SortListByKey (TStringList* sl, int item1, int item2)
{
	IniKey* k1 = (IniKey*) sl->Objects[item1];
  	IniKey* k2 = (IniKey*) sl->Objects[item2];

    return CompareStr(k1->mKey.c_str(), k2->mKey.c_str());
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::sortByValueAExecute(TObject *Sender)
{
    Log(lInfo) << "Sorting list based on Values";
    TStringList* sl = new TStringList();
    sl->Assign(ImageFilesLB->Items);
    sl->CustomSort(SortListByValue);
    ImageFilesLB->Items->Assign(sl);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::sortByFileNameAExecute(TObject *Sender)
{
	Log(lInfo) << "Sorting list based on Keys";
    TStringList* sl = new TStringList();
    sl->Assign(ImageFilesLB->Items);
    sl->CustomSort(SortListByKey);
    ImageFilesLB->Items->Assign(sl);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FileOpen1Accept(TObject *Sender)
{
    //Open project file here
    string fName(stdstr(FileOpen1->Dialog->FileName));
    Log(lInfo) << "Opening classification file: "<<fName;
    ImageFolderE->setValue(getFilePath(fName));

    //Main entry on opening a project, is openProject
    bool res = openProject(fName);

    ImageFilesGB->Caption = "Image Files (" + IntToStr(ImageFilesLB->Count) + ")";
    FileOpen1->Enabled 		= !res;
    NewProjectA->Enabled 	= !res;
    CloseProjectA->Enabled 	= res;
    SaveProjectA->Enabled 	= res;
    SaveProjectAsA->Enabled = res;

    StatusBar1->SimpleText = (res == true) ? FileOpen1->Dialog->FileName : String("");
    if(res)
    {
    	OpenCloseProjectBtn->Action = CloseProjectA;
    }
    else
    {
    	OpenCloseProjectBtn->Action = FileOpen1;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CloseProjectAExecute(TObject *Sender)
{
    IniFile& values = mClassifier.getProjectValues();
    values.save();
	delete mCF;
    mCF = NULL;
    values.clear();

    UserE->Enabled = true;
    ImageFilesLB->Clear();

    enableDisablePanel(ProjFilePathPanel, true);
    enableDisablePanel(ClassifierPanel, false);
    OpenCloseProjectBtn->Action = FileOpen1;

    FileOpen1->Enabled 		= true;
    NewProjectA->Enabled 	= true;
    CloseProjectA->Enabled 	= false;
    SaveProjectA->Enabled 	= false;
    SaveProjectAsA->Enabled = false;
    StatusBar1->SimpleText 	= "";
    ImageFilesGB->Caption = "Image Files (0)";
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::NewProjectAExecute(TObject *Sender)
{
    //Create a new project file
    //Bring up a custom dialog..
    auto_ptr<TNewProjectForm> f = auto_ptr<TNewProjectForm>(new TNewProjectForm(this));
    f->ImageFolderE->setValue(ImageFolderE->getValue());
    f->UserE->setValue(UserE->getValue());

    int r = f->ShowModal();
    while(r == mrTryAgain)
    {
        r = f->ShowModal();
    }

    if(r == mrCancel)
    {
        return;
    }

    //Create and open new project
    //Create fileName
    string fName = f->UserE->getValue() + string("_") + f->ProjectNameE->getValue() + string(".chf");
    fName = joinPath(f->ImageFolderE->getValue(), fName);

    if(fileExists(fName))
    {
        stringstream msg;
        msg << "The file: " << fName << " exists!. Overwrite?";
        int mr = MessageDlg(msg.str().c_str(), mtWarning, TMsgDlgButtons() << mbOK<<mbCancel, 0);
        if(mr == mrCancel)
        {
            return;
        }
        else
        {
            clearFile(fName);
        }
    }

    //Start fresh
    mClassifier.clear();

    //Make sure ini file is created here.. and then re open it in FileOpenAccept
    mClassifier.setUser(f->UserE->getValue());
    mClassifier.setImageFolder(f->ImageFolderE->getValue());

    //Setup classes
    mClassifier.addClasses(f->getClasses());

    mClassifier.save(fName);
    //Open project
    ImageFolderE->setValue(f->ImageFolderE->getValue());
    FileOpen1->Dialog->FileName = vclstr(fName);
    UserE->setValue(f->UserE->getValue());

    FileOpen1Accept(Sender);
}


//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAExecute(TObject *Sender)
{
    IniFile& values = mClassifier.getProjectValues();
    //Save current project
	if(values.save())
    {
        Log(lInfo) << "The projectfile: "<<values.getFileName()<< " was saved to folder: "<<getFilePath(values.getFullFileName());
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAsAExecute(TObject *Sender)
{
    //Open FileSaveAs dialog
    IniFile& values = mClassifier.getProjectValues();
    SaveDialog1->FileName = values.getFullFileName().c_str();
    if(!SaveDialog1->Execute())
    {
        Log(lInfo) << "Decided not to save file..";
        return;
    }

    string newFName(stdstr(SaveDialog1->FileName));
    Log(lInfo) << "Saving to file: " << newFName;

    values.setFileName(newFName);
    CloseProjectAExecute(Sender);

    //Open this new file
    FileOpen1->Dialog->FileName = newFName.c_str();
	FileOpen1Accept(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FileOpen1Cancel(TObject *Sender)
{
    ;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ToggleButtonFrameDockedAExecute(TObject *Sender)
{
    //Check where the button frame is
    if(ClassifierPanel->Parent == mBottomPanel)
    {
        //Transfer frame to floating button form
        if(!mFloatingButtonsForm.get())
        {
            mFloatingButtonsForm = auto_ptr<TFloatingButtonsForm>(new TFloatingButtonsForm(*this, this));
        }
        ClassifierPanel->Parent = mFloatingButtonsForm.get();
        ClassifierPanel->Align = alClient;
        mFloatingButtonsForm->Show();
    }
    else
    {
		mFloatingButtonsForm->Close();        //Assign the frame to BottomPanel
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::ClassifierPanelResize(TObject *Sender)
{
	int classCount = mClassifier.classCount();
    if(!classCount)
    {
        return;
    }
    int buttonWidth = ClassifierPanel->Width / classCount;
    for(int i = 0; i < classCount; i++)
    {
        ClassValue* val = mClassifier.getClass(i);
        if(val)
        {
            val->mButton->Width = buttonWidth;
            val->mButton->Align = alLeft;
            val->mButton->Left = i*val->mButton->Width + 10;
        }
    }
}


