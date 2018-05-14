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
#pragma link "atClassesFrame"
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

bool TMainForm::isFolderOpen()
{
    return ActionbuttonsPanel->Enabled;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenaClone1Click(TObject *Sender)
{
	if(!gImageForm)
    {
    	gImageForm = new TImageForm(gApplicationRegistryRoot, "", this);
    }

	gImageForm->Show();
	imagesLBClick(Sender);
}

bool TMainForm::openProject(const string& fName)
{
	mProjectFile.clear();
    Log(lInfo) << "Loading project from file: " << fName;
    if(!mProjectFile.load(fName))
    {
        Log(lError) << "Failed loading project file: " << fName;
    }

    //Get SETTINGS section
    IniSection* settings = mProjectFile.getSection("SETTINGS", true); //Autocreate section
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

    ImageFolderE->setValue(imageFolder->mValue);

    //Check current folder for files and populate list box
	StringList files = getFilesInDir(ImageFolderE->getValue(), "png", false);

    //Create ini file section
    IniSection* sec = mProjectFile.getSection("VALUES", true); //Autocreate section
    if(!sec)
    {
        Log(lError) << "Failed creating \"VALUES\" section";
        return false;
    }

    //Make sure the section has the same number of keys as images in the folder
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
	imagesLB->Clear();
    for(size_t i = 0; i < sec->keyCount(); i++)
    {
        IniKey* key = sec->getKey(i);
        if(key)
        {
            string item(key->mKey);
            item = item + " " + key->mValue;
        	imagesLB->Items->AddObject(vclstr(item), (TObject*) key );
        }
    }

    enableDisablePanel(ProjFilePathPanel, false);
    enableDisablePanel(ActionbuttonsPanel, true);
    return true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::imagesLBClick(TObject *Sender)
{
    //Extract filename and show image
    int index = imagesLB->ItemIndex;

    if(index < 0)
    {
        return;
    }

    IniKey* key = (IniKey*) imagesLB->Items->Objects[index];
    if(!key)
    {
        Log(lError) << "No Such file: " <<key->mKey;
        return;
    }
    string fName(joinPath(ImageFolderE->getValue(), key->mKey + ".png"));

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
	int idx = imagesLB->ItemIndex;

    if(idx < 0)
    {
        Log(lWarning) << "No image is selected..";
        return;
    }

    //Extract key
    IniKey* key = (IniKey*) imagesLB->Items->Objects[idx];
    if(!key)
    {
        Log(lError) << "Bad key..";
    }

    Log(lInfo) << "Updating synaptogram: " << key->mKey;

    TAction* a = dynamic_cast<TAction*>(Sender);
    if(a == YesA)
    {
        Log(lInfo) <<  "Yes action";
        if(ValidationCB->Checked)
        {
            if(MessageDlg("YES ??", mtInformation, TMsgDlgButtons() << mbOK<<mbCancel, 0) == mrCancel)
            {
                return;
            }
        }
        //Add.change value
        key->mValue = "Yes";
    }
    else if(a == NoA)
    {
        Log(lInfo) <<  "No action";
        if(ValidationCB->Checked)
        {
            if(MessageDlg("NO ??", mtInformation, TMsgDlgButtons() << mbOK<<mbCancel, 0) == mrCancel)
            {
                return;
            }
        }
        key->mValue = "No";
    }
    else if(a = MaybeA)
    {
        Log(lInfo) <<  "Maybe action";
        if(ValidationCB->Checked)
        {
            if(MessageDlg("PASS ??", mtInformation, TMsgDlgButtons() << mbOK<<mbCancel, 0) == mrCancel)
            {
                return;
            }
        }
        key->mValue = "Pass";
    }

    //Update item in listbox
	imagesLB->Items->Strings[idx] = string(key->mKey + " " + key->mValue).c_str();

    //Auto advance..
    if(idx < imagesLB->Count)
    {
		imagesLB->ItemIndex = imagesLB->ItemIndex + 1;
        imagesLBClick(NULL);
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

    if(isFolderOpen())
    {
            //Find the button with key == ch
            TArrayBotButton *btn = TClassesFrame1->getButtonWithKey(ch);
            if(btn)
            {
				SendMessage(btn->Handle, BM_CLICK, 0, 0);
            }

//            case 's':
//            case 'S':     		SendMessage(YesBtn->Handle, BM_CLICK, 0, 0);      break;
//
//            case 'd':
//            case 'D':           SendMessage(MaybeBtn->Handle, BM_CLICK, 0, 0);     break;
//
//            case 'F':
//            case 'f':           SendMessage(NoBtn->Handle, BM_CLICK, 0, 0);      break;

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
    sl->Assign(imagesLB->Items);
    sl->CustomSort(SortListByValue);
    imagesLB->Items->Assign(sl);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::sortByFileNameAExecute(TObject *Sender)
{
	Log(lInfo) << "Sorting list based on Keys";
    TStringList* sl = new TStringList();
    sl->Assign(imagesLB->Items);
    sl->CustomSort(SortListByKey);
    imagesLB->Items->Assign(sl);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FileOpen1Accept(TObject *Sender)
{
    //Open project file here
    string fName(stdstr(FileOpen1->Dialog->FileName));
    Log(lInfo) << "Opening file: "<<fName;

	if(openProject(fName))
    {
		FileOpen1->Enabled = false;
	    CloseProjectA->Enabled = true;
 		OpenCloseProjectBtn->Action = CloseProjectA;
	    SaveProjectA->Enabled = true;
	    SaveProjectAsA->Enabled = true;
        StatusBar1->SimpleText = FileOpen1->Dialog->FileName;
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::CloseProjectAExecute(TObject *Sender)
{
    mProjectFile.save();
    UserE->Enabled = true;
    imagesLB->Clear();
    enableDisablePanel(ProjFilePathPanel, true);
    enableDisablePanel(ActionbuttonsPanel, false);
    OpenCloseProjectBtn->Action = FileOpen1;
    FileOpen1->Enabled = true;
    CloseProjectA->Enabled = false;
    SaveProjectA->Enabled = false;
    SaveProjectAsA->Enabled = false;
    StatusBar1->SimpleText = "";
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
    if(r != mrOk)
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

    //Capture the categories
    StringList cats = f->getValues();

    //Setup classifer panel
    Log(lInfo) << "Setting up classifier panel with the following classes: " << cats;
    TClassesFrame1->populate(cats);


    //Open project
    FileOpen1->Dialog->FileName = vclstr(fName);
    UserE->setValue(f->UserE->getValue());
    FileOpen1Accept(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAExecute(TObject *Sender)
{
    //Save current project
	if(mProjectFile.save())
    {
        Log(lInfo) << "The projectfile: "<<mProjectFile.getFileName()<< " was saved to folder: "<<getFilePath(mProjectFile.getFullFileName());
    }
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::SaveProjectAsAExecute(TObject *Sender)
{
    //Open FileSaveAs dialog
    SaveDialog1->FileName = mProjectFile.getFullFileName().c_str();
    SaveDialog1->Execute();

    string newFName(stdstr(SaveDialog1->FileName));
    Log(lInfo) << "Saving to file: " << newFName;
    mProjectFile.setFileName(newFName);
    mProjectFile.save();

    //Open this new file
    FileOpen1->Dialog->FileName = newFName.c_str();
	FileOpen1Accept(Sender);
}

void TMainForm::setupClassifierPanel()
{

}


