#include <vcl.h>
#pragma hdrstop
#include "atTClassifierFrame.h"
#include "dslLogger.h"
#include "TAssingShortcutsForm.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TClassifierFrame *ClassifierFrame;
using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TClassifierFrame::TClassifierFrame(ClassifierBase& c, TListBox& lb, TComponent* Owner)
	: TFrame(Owner),
    mClassifier(c),
    ImageFilesLB(lb)
{}

__fastcall TClassifierFrame::~TClassifierFrame()
{
    mClassifier.clear();
}

void TClassifierFrame::empty()
{
    mClassifier.clear();
}
void TClassifierFrame::populate()
{
    //Setup classifer panel
    StringList l = mClassifier.getClassLabels();
    Log(lInfo) << "Setting up classifier panel with the following classes: " << l;

	int classCount = mClassifier.classCount();

    if(!classCount)
    {
        Log(lError) << "Can't populate the frame. Class count is zero!";
        return;
    }

    //Set up buttons for each class
    int buttonWidth = this->Width / classCount;
    for(int i = 0; i < classCount; i++)
    {
        ClassValue* val = mClassifier.getClass(i);
        if(val)
        {
            val->mButton->Parent = this;
            val->mButton->Width = buttonWidth;
            val->mButton->Align = alLeft;
            val->mButton->Left = i*val->mButton->Width + 10;
            val->mButton->OnClick = onBtnClick;
        }
    }
}

//---------------------------------------------------------------------------
shared_ptr<TArrayBotButton> TClassifierFrame::getButtonWithKey(char ch)
{
	return mClassifier.getButtonWithKey(ch);
}

//---------------------------------------------------------------------------
void __fastcall TClassifierFrame::AssignButtonKeys1Click(TObject *Sender)
{
    auto_ptr<TAssignShortCutsForm> f = auto_ptr<TAssignShortCutsForm>(new TAssignShortCutsForm(mClassifier, this));
    int res = f->ShowModal();


    if(res == mrOk)
    {
        //Capture new keys
        for(int i = 0; i < mClassifier.classCount(); i ++)
        {
            string newKey = stdstr(f->Grid->Cells[1][i+1]);
            ClassValue* c = mClassifier.getClass(i);
            c->mKeyBoardShortCut = newKey[0];
            stringstream caption;
		    caption << c->mValue << " \n(\'"<<c->mKeyBoardShortCut<<"\')";
		    c->mButton->Caption = caption.str().c_str();
        }
    }
}

void __fastcall TClassifierFrame::onBtnClick(TObject *Sender)
{
    TArrayBotButton* btn = dynamic_cast<TArrayBotButton*>(Sender);
    if(btn)
    {
        //Get class for this button
        ClassValue* cv = mClassifier.getValueFromButton(btn);
        if(cv)
        {
            Log(lInfo) << "Button with value: " << cv->mValue <<" was pressed";

            //Now set the value of this class to the currently selected key
			assingClassToCurrentItem(cv);
        }
    }
}

//---------------------------------------------------------------------------
void TClassifierFrame::assingClassToCurrentItem(ClassValue* cv)
{
	int idx = ImageFilesLB.ItemIndex;

    if(idx < 0)
    {
        Log(lWarning) << "No image is selected..";
        return;
    }

    //Extract key
    IniKey* key = (IniKey*) ImageFilesLB.Items->Objects[idx];
    if(!key)
    {
        Log(lError) << "Bad key..";
    }

    Log(lInfo) << "Updating classification for item: " << key->mKey;

	//Add.change value
    key->mValue = cv->mValue;

    //Update item in listbox
	ImageFilesLB.Items->Strings[idx] = string(key->mKey + " " + key->mValue).c_str();

    //Auto advance..
    if(idx < ImageFilesLB.Count)
    {
		ImageFilesLB.ItemIndex = ImageFilesLB.ItemIndex + 1;
        ImageFilesLB.OnClick(NULL);
    }
}



