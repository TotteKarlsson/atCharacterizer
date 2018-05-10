#include <vcl.h>
#pragma hdrstop
#include "TNewProjectForm.h"
#include "dslVCLUtils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dslTIntegerLabeledEdit"
#pragma link "dslTSTDStringLabeledEdit"
#pragma resource "*.dfm"
TNewProjectForm *NewProjectForm;
//---------------------------------------------------------------------------

using namespace dsl;

__fastcall TNewProjectForm::TNewProjectForm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TNewProjectForm::Button3Click(TObject *Sender)
{
	//Browse for folder
}


//---------------------------------------------------------------------------
void __fastcall TNewProjectForm::BrowseForFolder1Accept(TObject *Sender)
{
	//Extract Folder
    if(!BrowseForFolder1->Folder.Length())
    {
        return;
    }

    ImageFolderE->setValue(stdstr(BrowseForFolder1->Folder));
}

void __fastcall TNewProjectForm::BrowseForFolder1BeforeExecute(TObject *Sender)

{
	BrowseForFolder1->Folder = vclstr(ImageFolderE->getValue());
}
//---------------------------------------------------------------------------
