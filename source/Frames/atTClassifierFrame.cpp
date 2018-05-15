#include <vcl.h>
#pragma hdrstop
#include "atTClassifierFrame.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TClassifierFrame *ClassifierFrame;
using namespace dsl;

//---------------------------------------------------------------------------
__fastcall TClassifierFrame::TClassifierFrame(ClassifierBase& c, TComponent* Owner)
	: TFrame(Owner),
    mClassifier(c)
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
	MessageDlg("Assign keys", mtWarning, TMsgDlgButtons() << mbOK, 0);
}


