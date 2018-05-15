#pragma hdrstop
#include "atClassifierBase.h"
#include <sstream>
#include "dslIniSection.h"
#include "dslLogger.h"
#include "dslIniKey.h"
//---------------------------------------------------------------------------

using namespace std;
using namespace dsl;

ClassifierBase::ClassifierBase()
{}

ClassifierBase::~ClassifierBase()
{}

bool ClassifierBase::save(const string& fName)
{
    if(fName.size())
    {
	    mProjectValues.setFileName(fName);
    }

    return mProjectValues.save();
}

int ClassifierBase::updateClasses()
{
    //Get classes from file
    //Setup classes
    IniSection* classes = mProjectValues.getSection("CLASSES");
    if(!classes)
    {
        Log(lError) << "There are no classes to update from!";
        return 0;
    }

    int keyCount(0);
    for(int i = 0; i < classes->keyCount(); i++)
    {
        IniKey* aClass = classes->getKey(i);
        if(aClass)
        {
            addClass(aClass->mKey, 's' + i);
            keyCount++;
        }
        else
        {
            Log(lError) << "Bad class in list!!";
        }
    }
    return keyCount;
}

int ClassifierBase::classCount()
{
    return mClasses.size();
}

ClassValue* ClassifierBase::getClass(int i)
{
    if(i > -1 && i < classCount())
    {
        return &(mClasses[i]);
    }
    return NULL;
}

void ClassifierBase::setUser(const string& user)
{
    IniSection* s = mProjectValues.getSection("SETTINGS", true);

    if(!s)
    {
        Log(lError) << "Failed setting up user";
        return;
    }

    IniKey* k = s->getKey("USER", true);
    if(!k)
    {
        Log(lError) << "Failed setting up user";
        return;
    }
    k->mValue = (user);
}

void ClassifierBase::setImageFolder(const string& f)
{
    IniSection* s = mProjectValues.getSection("SETTINGS", true);

    if(!s)
    {
        Log(lError) << "Failed setting up imagefolder";
        return;
    }

    IniKey* k = s->getKey("IMAGE_FOLDER", true);
    if(!k)
    {
        Log(lError) << "Failed setting up image folder";
        return;
    }
    k->mValue = (f);

}

IniFile& ClassifierBase::getProjectValues()
{
    return mProjectValues;
}

shared_ptr<TArrayBotButton> ClassifierBase::getButtonWithKey(char ch)
{
    for(int i = 0; i < mClasses.size(); i++)
    {
        ClassValue& b = mClasses[i];
        if(b.mKey == ch)
        {
            return b.mButton;
        }
    }
    return shared_ptr<TArrayBotButton>();
}

StringList ClassifierBase::getClassLabels()
{
    StringList lbls;
    for(int i = 0; i < mClasses.size(); i++)
    {
        lbls.append(mClasses[i].mValue);
    }
    return lbls;
}

bool ClassifierBase::addClasses(const StringList& s)
{
    IniSection* classes = mProjectValues.getSection("CLASSES", true); //Autocreate section
    if(!classes)
    {
        Log(lError) << "Failed creating \"VALUES\" section";
        return false;
    }

    //Add from classifier

    for(int i = 0; i < s.count(); i++)
    {
        IniKey* k = classes->getKey(s[i], true);
        if(!k)
        {
            Log(lError) << "Problem creating key...";
        }
        else
        {
            k->mValue = dsl::toString(i + 1);
        }
    }
    return true;
}

ClassValue& ClassifierBase::addClass(const string& value, char ch)
{
    mClasses.push_back(ClassValue(value,ch));
    return mClasses.back();
}

void ClassifierBase::clear()
{
    mClasses.clear();
    mProjectValues.clear();
}
