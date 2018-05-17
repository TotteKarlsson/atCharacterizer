#ifndef atClassValueH
#define atClassValueH
#include <string>
#include "TArrayBotBtn.h"
#include "dslSharedPointer.h"
//---------------------------------------------------------------------------

using std::string;
using dsl::shared_ptr;

class ClassValue
{
    public:
    									ClassValue(const string& cat, char ch = 's');
                                       ~ClassValue();

                                    	//Yes, no , etc...
        string          	           	mValue;

                                        //The keyboard key used to generate this value
        char            	           	mKeyBoardShortCut;

                                        //UI Button
        shared_ptr<TArrayBotButton>    	mButton;
};

#endif
