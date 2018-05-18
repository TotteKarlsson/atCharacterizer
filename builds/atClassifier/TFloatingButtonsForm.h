#ifndef TFloatingButtonsFormH
#define TFloatingButtonsFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//#include "TMainForm.h"
//---------------------------------------------------------------------------

class TMainForm;
class TFloatingButtonsForm : public TForm
{
    __published:	// IDE-managed Components
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormResize(TObject *Sender);
	void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);


    private:
        TMainForm&              	mMainForm;
    public:
        				__fastcall TFloatingButtonsForm(TMainForm& main, TComponent* Owner);
};

extern PACKAGE TFloatingButtonsForm *FloatingButtonsForm;
#endif
