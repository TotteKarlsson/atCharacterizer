#ifndef atTClassifierFrameH
#define atTClassifierFrameH
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "dslStringList.h"
#include "TArrayBotBtn.h"
#include <Vcl.Buttons.hpp>
#include <Vcl.Menus.hpp>
#include <vector>
#include "atClassifierBase.h"
#include "dslSharedPointer.h"
#include "atClassifierBase.h"
//---------------------------------------------------------------------------
using dsl::StringList;
using std::vector;
using std::auto_ptr;
using dsl::shared_ptr;

class TClassifierFrame : public TFrame
{
    __published:
	TPopupMenu *PopupMenu1;
	TMenuItem *AssignButtonKeys1;
	void __fastcall AssignButtonKeys1Click(TObject *Sender);


    private:
                                                    //Classifier holds various class values
        ClassifierBase&			        			mClassifier;

    public:
    							__fastcall 	        TClassifierFrame(ClassifierBase& c, TComponent* Owner);
    							__fastcall 	        ~TClassifierFrame();

        shared_ptr<TArrayBotButton>        			getButtonWithKey(char ch);
        void                                        empty();
        void                    	                populate();
};

extern PACKAGE TClassifierFrame *ClassifierFrame;

#endif
