#ifndef TAssingShortcutsFormH
#define TAssingShortcutsFormH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Grids.hpp>
#include "atClassifierBase.h"

//---------------------------------------------------------------------------
class TAssignShortCutsForm : public TForm
{
__published:	// IDE-managed Components
	TStringGrid *Grid;
	TPanel *Panel1;
	TButton *Button1;
	TButton *Button2;
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
	void __fastcall GridGetEditText(TObject *Sender, int ACol, int ARow, UnicodeString &Value);
	void __fastcall GridGetEditMask(TObject *Sender, int ACol, int ARow, UnicodeString &Value);



private:	// User declarations
	ClassifierBase&     mClassifier;
public:		// User declarations
	__fastcall TAssignShortCutsForm(ClassifierBase& c, TComponent* Owner);
};


extern PACKAGE TAssignShortCutsForm *AssignShortCutsForm;

#endif
