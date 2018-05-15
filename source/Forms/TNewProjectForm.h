//---------------------------------------------------------------------------

#ifndef TNewProjectFormH
#define TNewProjectFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslTIntegerLabeledEdit.h"
#include "dslTSTDStringLabeledEdit.h"
#include <Vcl.ExtCtrls.hpp>
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.StdActns.hpp>
#include <Vcl.Dialogs.hpp>
#include "dslStringList.h"
//---------------------------------------------------------------------------

using dsl::StringList;
class TNewProjectForm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TPanel *Panel1;
	TButton *Button1;
	TButton *Button2;
	TSTDStringLabeledEdit *ImageFolderE;
	TSTDStringLabeledEdit *UserE;
	TSTDStringLabeledEdit *ProjectNameE;
	TButton *Button3;
	TActionList *ActionList1;
	TBrowseForFolder *BrowseForFolder1;
	TGroupBox *GroupBox2;
	TListBox *ClassesLB;
	TButton *AddCategoryBtn;
	TPanel *Panel2;
	TButton *Button4;
	TFileOpenDialog *FileOpenDialog1;
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall AddCategoryBtnClick(TObject *Sender);
	void __fastcall Button4Click(TObject *Sender);
	void __fastcall FileOpenDialog1FileOkClick(TObject *Sender, bool &CanClose);
	void __fastcall Button2Click(TObject *Sender);

    private:

    public:
    						__fastcall TNewProjectForm(TComponent* Owner);
        StringList          getClasses();
};
//---------------------------------------------------------------------------
extern PACKAGE TNewProjectForm *NewProjectForm;
//---------------------------------------------------------------------------
#endif
