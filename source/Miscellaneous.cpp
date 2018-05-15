#include <vcl.h>
#pragma hdrstop
#include "TMainForm.h"
#include "dslVCLUtils.h"
#include "dslLogger.h"
#include "dslRestartApplicationUtils.h"
#include "TAboutATCharacterizerForm.h"
#include "TImageForm.h"
//---------------------------------------------------------------------------

using namespace dsl;
extern string gAppName;
extern string gApplicationStyle;
extern string gRestartMutexName;
extern string gApplicationRegistryRoot;


void __fastcall TMainForm::logMsg()
{
    infoMemo->Lines->Add(vclstr(mLogFileReader.getData()));
    mLogFileReader.purge();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::OpenaClone1Click(TObject *Sender)
{
	if(!gImageForm)
    {
    	gImageForm = new TImageForm(gApplicationRegistryRoot, "", this);
    }

	gImageForm->Show();
	ImageFilesLBClick(Sender);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::About1Click(TObject *Sender)
{
	TAboutATCharacterizer* a = new TAboutATCharacterizer(this);
	a->ShowModal();
    delete a;
}

void __fastcall TMainForm::ThemesMenuClick(TObject *Sender)
{
   TMenuItem* menuItem = dynamic_cast<TMenuItem*>(Sender);
    if(!menuItem)
    {
        return;
    }

	//Uncheck any checked items
	for(int i = 0; i < ThemesMenu->Count; i++)
	{
		TMenuItem* menuItem = ThemesMenu->Items[i];
		if(menuItem && menuItem->Checked)
		{
			menuItem->Checked = false;
		}
	}

	TRegistryForm::writeToRegistry();

	TReplaceFlags rFlags(rfIgnoreCase|rfReplaceAll);
	String styleName = StringReplace(menuItem->Caption, "&", "", rFlags);
	TStyleManager::SetStyle(styleName);

	//Check the menu item
	menuItem->Checked = (TStyleManager::ActiveStyle->Name == styleName) ? true : false;

	//Write to registry
	gApplicationStyle = stdstr(styleName);
	writeStringToRegistry(gApplicationRegistryRoot, "", "Theme", gApplicationStyle);
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mCLearMemoClick(TObject *Sender)
{
	infoMemo->Clear();
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mCloseBottomPanelBtnClick(TObject *Sender)
{
	mBottomPanel->Visible = false;
    mShowBottomPanelBtn->Top = StatusBar1->Top - 1;
    Splitter2->Visible = false;
    mShowBottomPanelBtn->Visible = true;
}

//---------------------------------------------------------------------------
void __fastcall TMainForm::mShowBottomPanelBtnClick(TObject *Sender)
{
	mBottomPanel->Visible = true;
    Splitter2->Visible = true;
    mShowBottomPanelBtn->Visible = false;
    Splitter2->Top = mBottomPanel->Top - 1;
    StatusBar1->Top = mBottomPanel->Top + mBottomPanel->Height + 1;
}
