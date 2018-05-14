#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "TImageForm.h"
//---------------------------------------------------------------------------
using namespace dsl;

//---------------------------------------------------------------------------
void __fastcall TMainForm::Exit1Click(TObject *Sender)
{
	Close();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mShutDownTimerTimer(TObject *Sender)
{
	mShutDownTimer->Enabled = false;

	if(mLogFileReader.isRunning())
	{
		Log(lDebug) << "Shutting down log file reader";
		mLogFileReader.stop();
	}

    Close();
}

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
	Log(lInfo) << "In FormClose";
	Log(lInfo) << "In main forms destructor";

	if(gImageForm)
    {
		gImageForm->mPrepareForDeletion = true;
    	gImageForm->Close();
    }

	//Save project history
	mBottomPanelHeight = mBottomPanel->Height;

    //We have to write properties here, cause the form owns some of them and they will
    //be destroyed here..
    mAppProperties.writeProperties();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCloseQuery(TObject *Sender, bool &CanClose)
{
	Log(lInfo) << "Closing down....";
	//Check if we can close.. abort all threads..
	if(mLogFileReader.isRunning())
    {
    	CanClose = false;
    }

	if(CanClose == false)
	{
		mShutDownTimer->Enabled = true;
	}
}

