#pragma hdrstop
#include "atApplicationSupportFunctions.h"
#include "dslUtils.h"
#include "dslLogger.h"
#include "dslRestartApplicationUtils.h"
#include "dslVCLUtils.h"

using namespace dsl;

extern string gAppDataLocation;
extern string gLogFileName;
extern string gApplicationStyle;
extern string gApplicationRegistryRoot;
extern string gAppName;
extern HWND	  gOtherAppWindow;

//---------------------------------------------------------------------------
void setupLogging()
{
	if(!folderExists(gAppDataLocation))
	{
		createFolder(gAppDataLocation);
	}

	string fullLogFileName(joinPath(gAppDataLocation, gLogFileName));
	clearFile(fullLogFileName);
	dsl::gLogger.logToFile(fullLogFileName);
	LogOutput::mShowLogLevel = true;
	LogOutput::mShowLogTime = false;
	LogOutput::mUseLogTabs = false;
	Log(lInfo) << "Logger was setup";
}

BOOL CALLBACK FindOtherWindow(HWND hwnd, LPARAM lParam)
{
	static char buffer[50];
	GetWindowTextA(hwnd, buffer, 50);

	string wName(buffer);
	if(contains(buffer, gAppName))
	{
		// do something with hwnd here
		gOtherAppWindow = hwnd;
		return FALSE;
	}

	return TRUE;
}
