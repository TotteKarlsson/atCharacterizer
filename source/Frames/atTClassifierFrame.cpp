#include <vcl.h>
#pragma hdrstop
#include "atTClassifierFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TClassifierFrame *ClassifierFrame;

//---------------------------------------------------------------------------
__fastcall TClassifierFrame::TClassifierFrame(ClassifierBase& c, TComponent* Owner)
	: TFrame(Owner),
    mClassifier(c)
{
}

void TClassifierFrame::empty()
{
    mClassifier.clear();
}
//---------------------------------------------------------------------------
void TClassifierFrame::populate(const StringList& categories)
{
    mClassifier.clear();
    int buttonWidth = this->Width / categories.count();

    for(int i = 0; i < categories.count(); i++)
    {
        //Return a class
	    ClassValue& aClass = mClassifier.addClass(categories[i], 's' + i);
//        aClass.mButton->Left = buttonWidth * i + 1;
        aClass.mButton->Align = alLeft;
        aClass.mButton->Parent = this;
        aClass.mButton->Width =  buttonWidth;
    }
}

//---------------------------------------------------------------------------
TArrayBotButton* TClassifierFrame::getButtonWithKey(char ch)
{
    for(int i = 0; i < mClassifier.count(); i++)
    {

    }
}


//---------------------------------------------------------------------------
void __fastcall TClassifierFrame::AssignButtonKeys1Click(TObject *Sender)
{
	MessageDlg("Assign keys", mtWarning, TMsgDlgButtons() << mbOK, 0);
}


