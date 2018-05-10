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
//---------------------------------------------------------------------------
class TNewProjectForm : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TPanel *Panel1;
	TButton *Button1;
	TButton *Button2;
	TSTDStringLabeledEdit *ImageFolderE;
	TIntegerLabeledEdit *IntegerLabeledEdit1;
	TSTDStringLabeledEdit *UserE;
	TSTDStringLabeledEdit *ProjectNameE;
	TButton *Button3;
	TActionList *ActionList1;
	TBrowseForFolder *BrowseForFolder1;
	void __fastcall Button3Click(TObject *Sender);
	void __fastcall BrowseForFolder1Accept(TObject *Sender);
	void __fastcall BrowseForFolder1BeforeExecute(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TNewProjectForm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TNewProjectForm *NewProjectForm;
//---------------------------------------------------------------------------
#endif
