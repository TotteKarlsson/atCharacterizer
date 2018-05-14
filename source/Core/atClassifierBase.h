#ifndef atClassifierBaseH
#define atClassifierBaseH
#include <vector>
#include "dslStringList.h"
#include "TArrayBotBtn.h"
#include "dslSharedPointer.h"
#include "atClassValue.h"
//---------------------------------------------------------------------------
using std::vector;
using std::string;
using dsl::StringList;
using dsl::shared_ptr;

class ClassifierBase
{
    public:
                                        ClassifierBase();
                                        ~ClassifierBase();
        ClassValue&                     addClass(const string& value, char ch = 's');

        void                            clear();
//        ClassifierBase&                    operator=(const ClassifierBase& rhs);
//        ClassifierBase&                    operator=(const StringList& rhs);

        ClassValue                      operator[](int i) const;
        int                             count();

    private:
        vector<ClassValue>              mValues;

};
#endif
