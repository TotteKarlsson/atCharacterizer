#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
#include <string>
#include <Vcl.Styles.hpp>
#include <Vcl.Themes.hpp>
#include "atApplicationSupportFunctions.h"
#include "dslRestartApplicationUtils.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
//---------------------------------------------------------------------------
using namespace dsl;

using std::string;
USEFORM("Forms\TImageForm.cpp", ImageForm);
USEFORM("TMainForm.cpp", MainForm);
USEFORM("Forms\TAboutATCharacterizerForm.cpp", AboutATCharacterizer);
//---------------------------------------------------------------------------
extern string		gAppName					= "The Characterizer";
extern string       gLogFileName                = "Characterizer.log";
extern string       gAppDataLocation            = joinPath(getSpecialFolder(CSIDL_LOCAL_APPDATA), gAppName);
extern string 		gApplicationRegistryRoot  	= "\\Software\\Allen Institute\\Characterizer\\0.5.0";
extern string       gApplicationStyle           = "Iceberg Classico";
extern string       gApplicationMutexName       = "CharacterizerMutex";
extern HWND         gOtherAppWindow             = NULL;
extern string       gRestartMutexName           = "CharacterizerRestartMutex";

int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{
    //The app mutex is used to check for already running instances
    HANDLE appMutex;
	try
	{

        appMutex = ::CreateMutexA(NULL, FALSE, gApplicationMutexName.c_str());
        if( ERROR_ALREADY_EXISTS == GetLastError() )
        {
            // The Program is already running somewhere
            MessageDlg("It seems that the Characterizer is already running!\nOnly one instance can be running at any one time..", mtWarning, TMsgDlgButtons() << mbOK, 0);
            ::EnumWindows(FindOtherWindow, NULL);

            if(gOtherAppWindow != NULL)
            {
                //Send a custom message to restore window here..
            }

            return(1); // Exit program
        }

		gApplicationStyle = readStringFromRegistry(gApplicationRegistryRoot, "", "Theme",  gApplicationStyle);
		Application->Initialize();


        string iconFile("App_Icon.ico");
        if(fileExists(iconFile))
        {
			Application->Icon->LoadFromFile(iconFile.c_str());
        }
        else
        {
            Log(lWarning) << "Application icon ("<<iconFile<<")  was not found";
        }


		Application->MainFormOnTaskBar = true;
        setupLogging();

		TStyleManager::TrySetStyle("Carbon");
		Application->CreateForm(__classid(TMainForm), &MainForm);
		Application->Run();
		writeStringToRegistry(gApplicationRegistryRoot, "", "Theme",  gApplicationStyle);
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}

//---------------------------------------------------------------------------
#pragma comment(lib, "dslCommon")
#pragma comment(lib, "dslMath")
#pragma comment(lib, "dslVCLCommon.lib")

#pragma comment(lib, "dslVCLComponents.bpi")
#pragma comment(lib, "dslVCLVisualComponents.bpi")

//#pragma comment(lib, "atCore.lib")
#pragma comment(lib, "atResources.lib")
#pragma comment(lib, "poco_foundation-static.lib")
#pragma comment(lib, "tinyxml2-static.lib")



