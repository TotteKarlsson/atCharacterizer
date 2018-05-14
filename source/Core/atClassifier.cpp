#pragma hdrstop
#include "atClassifier.h"
#include <sstream>
//---------------------------------------------------------------------------

using namespace std;


Classifier::Classifier()
{}

Classifier::~Classifier()
{}

ClassValue Classifier::operator[](int i) const
{
	return mValues[i];
}

int Classifier::count()
{
    return mValues.size();
}

ClassValue& Classifier::addClass(const string& value, char ch)
{
    mValues.push_back(ClassValue(value,ch));
    return mValues.back();
}

//StringList Classifier::getValues() const
//{
//    StringList vals;
//
//	return mValues;
//}


void Classifier::clear()
{
    mValues.clear();
}
