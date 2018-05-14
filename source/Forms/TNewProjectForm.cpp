#include <vcl.h>
#pragma hdrstop
#include "TNewProjectForm.h"
#include "dslVCLUtils.h"
#include "TTextInputDialog.h"
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
	FileOpenDialog1->Execute();
}

StringList TNewProjectForm::getValues()
{
    StringList items(getStrings(CategoryLB));

    return items;
}

//---------------------------------------------------------------------------
void __fastcall TNewProjectForm::AddCategoryBtnClick(TObject *Sender)
{
	auto_ptr<TTextInputDialog> d = auto_ptr<TTextInputDialog>(new TTextInputDialog(this));

    StringList items(getStrings(CategoryLB));

    string text = items.asString();
    d->setText(text);
    d->ShowModal();

	CategoryLB->Clear();

    items.clear();
    items.appendList(StringList(d->getText()));

    for(int i = 0; i < items.count(); i++)
    {
    	CategoryLB->AddItem(items[i].c_str(), NULL);
    }
}

//---------------------------------------------------------------------------
void __fastcall TNewProjectForm::Button4Click(TObject *Sender)
{
	CategoryLB->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TNewProjectForm::FileOpenDialog1FileOkClick(TObject *Sender, bool &CanClose)
{
	//Extract Folder
    if(!FileOpenDialog1->FileName.Length())
    {
        return;
    }

    ImageFolderE->setValue(stdstr(FileOpenDialog1->FileName));
}


