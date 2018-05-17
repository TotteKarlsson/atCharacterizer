#include <vcl.h>
#pragma hdrstop
#include "TAssingShortcutsForm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TAssignShortCutsForm *AssignShortCutsForm;
//---------------------------------------------------------------------------
__fastcall TAssignShortCutsForm::TAssignShortCutsForm(ClassifierBase& c, TComponent* Owner)
	: TForm(Owner),
    mClassifier(c)
{
    //Setup the form
    Grid->RowCount = mClassifier.classCount() + 1;

    StringList l = mClassifier.getClassLabels();
	Grid->Cells[0][0] = "Class";
	Grid->Cells[1][0] = "Key";
    for(int i = 0; i < l.count(); i++)
    {
		Grid->Cells[0][i+1] = l[i].c_str();
    }

    l = mClassifier.getClassShortCuts();
    for(int i = 0; i < l.count(); i++)
    {
		Grid->Cells[1][i+1] = l[i].c_str();
    }
	Grid->Options = Grid->Options <<  goEditing;
}

void __fastcall TAssignShortCutsForm::FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
    if(Key == VK_ESCAPE)
    {
        Close();
    }
}


void __fastcall TAssignShortCutsForm::GridGetEditText(TObject *Sender, int ACol,
          int ARow, UnicodeString &Value)
{
    //
}

//---------------------------------------------------------------------------
void __fastcall TAssignShortCutsForm::GridGetEditMask(TObject *Sender, int ACol,
          int ARow, UnicodeString &Value)
{
    Value = "a";
}


