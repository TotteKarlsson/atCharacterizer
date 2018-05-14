#pragma hdrstop
#include "atClassValue.h"
#include <sstream>
//---------------------------------------------------------------------------

using namespace std;

ClassValue::ClassValue(const string& cat, char ch )
:
mValue(cat),
mKey(ch),
mButton(shared_ptr<TArrayBotButton>(new TArrayBotButton(NULL)))
{
    stringstream caption;
    caption << mValue << " (\'"<<mKey<<"\')";
    mButton->Caption = caption.str().c_str();
}

ClassValue::~ClassValue()
{}

