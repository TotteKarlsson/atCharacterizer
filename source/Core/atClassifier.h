#ifndef atClassifierH
#define atClassifierH
#include <vector>
#include "dslStringList.h"
#include "TArrayBotBtn.h"
#include "dslSharedPointer.h"

//---------------------------------------------------------------------------
using std::vector;
using std::string;
using dsl::StringList;
using dsl::shared_ptr;

class Classifier
{
    public:
                                        Classifier();
                                        ~Classifier();
        ClassValue&                     addClass(const string& value, char ch = 's');

        void                            clear();
//        Classifier&                    operator=(const Classifier& rhs);
//        Classifier&                    operator=(const StringList& rhs);

        ClassValue                      operator[](int i) const;
        int                             count();

    private:
        vector<ClassValue>              mValues;

};
#endif
