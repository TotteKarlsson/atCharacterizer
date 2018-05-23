#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslLogger.h"
#include "dslVCLUtils.h"
#include "TImageForm.h"
using namespace dsl;

//---------------------------------------------------------------------------
void __fastcall TMainForm::ImageFilesLBClick(TObject *Sender)
{
    //Extract filename and show image
    int index = ImageFilesLB->ItemIndex;

    if(index < 0)
    {
        return;
    }

    IniKey* key = (IniKey*) ImageFilesLB->Items->Objects[index];
    if(!key)
    {
        Log(lError) << "No Such file: " <<key->mKey;
        return;
    }
    string fName(joinPath(ImageFolderE->getValue(), key->mKey + ".png"));

    Image1->Picture->LoadFromFile(fName.c_str());
    Log(lInfo) << "Opened file: " << fName.c_str();

    if(gImageForm)
    {
        gImageForm->load(fName);
    }

    if(mMagnifyForm->Visible)
    {
		mMagnifyForm->loadImage(fName);
    }
}


