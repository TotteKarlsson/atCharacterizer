#ifndef atClassesFrameH
#define atClassesFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslStringList.h"
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.Menus.hpp>
#include <vector>
#include "atClassValues.h"
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------
using dsl::StringList;
using std::vector;
using std::auto_ptr;
using dsl::shared_ptr;

class TClassesFrame : public TFrame
{
    __published:
	TPopupMenu *PopupMenu1;
	TMenuItem *AssignButtonKeys1;
	void __fastcall AssignButtonKeys1Click(TObject *Sender);
    private:
        ClassValues				        			mClasses;

    public:
    					__fastcall 	                TClassesFrame(TComponent* Owner);
        void                    	                populate(const StringList& cats);
        TArrayBotButton*                 			getButtonWithKey(char ch);

};

extern PACKAGE TClassesFrame *ClassesFrame;

#endif
