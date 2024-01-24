
#include "../../Job.h"

class CSymbolicLink : public CJob
    {
    public :
        int result = 0;
    public :
        int proceed (CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup);
        void setResult (int result) {this->result = result;};
    };