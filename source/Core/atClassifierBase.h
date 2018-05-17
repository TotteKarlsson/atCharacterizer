#ifndef atClassifierBaseH
#define atClassifierBaseH
#include <vector>
#include "dslStringList.h"
#include "TArrayBotBtn.h"
#include "dslSharedPointer.h"
#include "atClassValue.h"
#include "dslIniFile.h"
//---------------------------------------------------------------------------
using std::vector;
using std::string;
using dsl::StringList;
using dsl::shared_ptr;
using dsl::IniFile;
using dsl::gEmptyString;

class ClassifierBase
{
    public:
                                        ClassifierBase();
                                        ~ClassifierBase();
        bool                            addClasses(const StringList& cats);
        ClassValue&                     addClass(const string& value, char ch = 's');
        ClassValue*                     getClass(int i);
		ClassValue*						getValueFromButton(TArrayBotButton* btn);
        void                            clear();
        int                             classCount();
        IniFile&                        getProjectValues();
        bool                            save(const string& fName = gEmptyString);
        StringList                      getClassLabels();
        StringList                      getClassShortCuts();

		shared_ptr<TArrayBotButton> 	getButtonWithKey(char ch);
        void                            setUser(const string& user);
        void                            setImageFolder(const string& f);
		int        						updateClasses();

    private:
        vector<ClassValue>              mClasses;
        IniFile                         mProjectValues;

};
#endif
