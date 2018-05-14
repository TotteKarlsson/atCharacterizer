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

        string          	           mValue;
        char            	           mKey;
        shared_ptr<TArrayBotButton>    mButton;
};

#endif
