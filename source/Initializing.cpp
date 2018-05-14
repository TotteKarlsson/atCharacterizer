#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------

using namespace dsl;
extern string gAppName;
extern string gAppDataLocation;
extern string gApplicationStyle;
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
	this->Caption = vclstr(createWindowTitle(gAppName, Application));
    this->DoubleBuffered = true;

	TStyleManager::SetStyle(gApplicationStyle.c_str());

	gLogger.setLogLevel(mLogLevel);
	mLogFileReader.start(true);
}

bool TMainForm::setupAndReadIniParameters()
{
//	shared_ptr<IniFileProperties> GeneralProperties = shared_ptr<IniFileProperties>(new IniFileProperties(&(mAppProperties.getIniFile()), "GENERAL"));
	shared_ptr<IniFileProperties> GeneralProperties = mAppProperties.appendNewINISection("GENERAL");

	//Setup parameters
	GeneralProperties->setSection("GENERAL");
	GeneralProperties->add((BaseProperty*)  &mBottomPanelHeight.setup( 	            	"HEIGHT_OF_BOTTOM_PANEL",    	    205));
	GeneralProperties->add((BaseProperty*)  &mLogLevel.setup( 	                    	"LOG_LEVEL",    	                lAny));
	GeneralProperties->add((BaseProperty*)  &UserE->getProperty()->setup(      			"USER",    	                        "JohnDoe"));
	GeneralProperties->add((BaseProperty*)  &ImageFolderE->getProperty()->setup(      	"IMAGE_FOLDER",    	                "C:"));

	//Read from file. Create if file do not exist
	GeneralProperties->read();

	//Update UI
	mBottomPanel->Height = mBottomPanelHeight;
    ImageFolderE->update();
	UserE->update();
    return true;
}

