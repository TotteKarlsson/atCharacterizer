#pragma hdrstop
#include "atClassifierBase.h"
#include <sstream>
//---------------------------------------------------------------------------

using namespace std;


ClassifierBase::ClassifierBase()
{}

ClassifierBase::~ClassifierBase()
{}

ClassValue ClassifierBase::operator[](int i) const
{
	return mValues[i];
}

int ClassifierBase::count()
{
    return mValues.size();
}

ClassValue& ClassifierBase::addClass(const string& value, char ch)
{
    mValues.push_back(ClassValue(value,ch));
    return mValues.back();
}

//StringList ClassifierBase::getValues() const
//{
//    StringList vals;
//
//	return mValues;
//}


void ClassifierBase::clear()
{
    mValues.clear();
}
