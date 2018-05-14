#include <vcl.h>
#pragma hdrstop
#include "atClassesFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "TArrayBotBtn"
#pragma resource "*.dfm"
TClassesFrame *ClassesFrame;

//---------------------------------------------------------------------------
__fastcall TClassesFrame::TClassesFrame(TComponent* Owner)
	: TFrame(Owner)
{
}

//---------------------------------------------------------------------------
void TClassesFrame::populate(const StringList& categories)
{
    mClasses.clear();
    int buttonWidth = this->Width / categories.count();

    for(int i = 0; i < categories.count(); i++)
    {
	    ClassValue& aClass = mClasses.addClass(categories[i], 's' + i);
        aClass.mButton->Left = buttonWidth * i + 1;
        aClass.mButton->Align = alLeft;
        aClass.mButton->Parent = this;
        aClass.mButton->Width =  buttonWidth;
    }
}

//---------------------------------------------------------------------------
TArrayBotButton* TClassesFrame::getButtonWithKey(char ch)
{
    for(int i = 0; i < mClasses.count(); i++)
    {

    }
}


//---------------------------------------------------------------------------
void __fastcall TClassesFrame::AssignButtonKeys1Click(TObject *Sender)
{
	MessageDlg("Assign keys", mtWarning, TMsgDlgButtons() << mbOK, 0);
}


