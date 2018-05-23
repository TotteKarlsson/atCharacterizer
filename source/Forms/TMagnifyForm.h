#ifndef TMagnifyFormH
#define TMagnifyFormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <Vcl.Menus.hpp>
#include "dslTRegistryForm.h"
#include <System.Actions.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.StdActns.hpp>
//---------------------------------------------------------------------------
class TMainForm;

class TMagnifyForm : public TRegistryForm
{
    __published:	// IDE-managed Components
	TImage *Image1;
	TTimer *Timer1;
	TPopupMenu *PopupMenu1;
	TMenuItem *OneP5X;
	TMenuItem *TwoX;
	TMenuItem *ThreeX;
	TMenuItem *FourX;
	TMenuItem *N1;
	TMenuItem *SmallSquare;
	TMenuItem *BigSquare;
	TMenuItem *DefaultFormSize;
	TMenuItem *N2;
	TActionList *ActionList1;
	TMenuItem *Close1;
	TAction *HideForm;
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
        void __fastcall Image1MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
              int X, int Y);
	void __fastcall FormShow(TObject *Sender);
	void __fastcall Image1MouseMove(TObject *Sender, TShiftState Shift, int X,
          int Y);
	void __fastcall Image1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall MagMenuClick(TObject *Sender);
	void __fastcall FormSizeClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall HideFormExecute(TObject *Sender);

    private:
        TMainForm*          mMainForm;
        bool                mIsMagnifying;
        void                render();
		double 				mZoomFactor;

    public:		// User declarations
        				__fastcall 	TMagnifyForm(TMainForm* mf);
        				__fastcall 	~TMagnifyForm();
        bool                        loadImage(const string& fName);
};

extern PACKAGE TMagnifyForm *MagnifyForm;
#endif
