#pragma hdrstop
#include "atClassValue.h"
#include <sstream>
//---------------------------------------------------------------------------

using namespace std;

ClassValue::ClassValue(const string& cat, char ch )
:
mValue(cat),
mKeyBoardShortCut(ch),
mButton(shared_ptr<TArrayBotButton>(new TArrayBotButton(NULL)))
{
    stringstream caption;
    caption << mValue << " \n(\'"<<mKeyBoardShortCut<<"\')";
    mButton->Caption = caption.str().c_str();
}

ClassValue::~ClassValue()
{}

