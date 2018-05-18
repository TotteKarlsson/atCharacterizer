#include <vcl.h>
#pragma hdrstop
#include "TFloatingButtonsForm.h"
#include "TMainForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFloatingButtonsForm *FloatingButtonsForm;
//---------------------------------------------------------------------------
__fastcall TFloatingButtonsForm::TFloatingButtonsForm(TMainForm& main, TComponent* Owner)
	: TForm(Owner),
    mMainForm(main)
{
}
//---------------------------------------------------------------------------
void __fastcall TFloatingButtonsForm::FormCloseQuery(TObject *Sender, bool &CanClose)

{
;
}

//---------------------------------------------------------------------------
void __fastcall TFloatingButtonsForm::FormClose(TObject *Sender, TCloseAction &Action)
{
    //Assign the frame to BottomPanel
    mMainForm.ClassifierPanel->Parent = mMainForm.mBottomPanel;
    mMainForm.ClassifierPanel->Align = alLeft;
    mMainForm.ClassifierPanel->Width = 400;
	int classCount = mMainForm.mClassifier.classCount();
    int buttonWidth = mMainForm.ClassifierPanel->Width / classCount;
    for(int i = 0; i < classCount; i++)
    {
        ClassValue* val = mMainForm.mClassifier.getClass(i);
        if(val)
        {
            val->mButton->Width = buttonWidth;
            val->mButton->Align = alLeft;
            val->mButton->Left = i*val->mButton->Width + 10;
        }
    }
    mMainForm.Splitter1->Left = mMainForm.ClassifierPanel->Width + 10;
}

//---------------------------------------------------------------------------
void __fastcall TFloatingButtonsForm::FormResize(TObject *Sender)
{
//    //Change size of buttons
//    //Set up buttons
//	int classCount = mMainForm.mClassifier.classCount();
//    int buttonWidth = this->Width / classCount;
//    for(int i = 0; i < classCount; i++)
//    {
//        ClassValue* val = mMainForm.mClassifier.getClass(i);
//        if(val)
//        {
//            val->mButton->Width = buttonWidth;
//            val->mButton->Align = alLeft;
//            val->mButton->Left = i*val->mButton->Width + 10;
//        }
//    }
}

void __fastcall TFloatingButtonsForm::FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift)
{
	mMainForm.FormKeyDown(this, Key, Shift);
}
//---------------------------------------------------------------------------
