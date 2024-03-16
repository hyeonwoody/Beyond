#include "../Feature.h"
#include "../../Job.h"

class CSymbolicLink : public CFeature
    {
    public :
        int result = 0;

    public :
        static CFeature *Create() {return new CSymbolicLink();}

    public :
        int proceed (CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup);
        void setResult (int result) {this->result = result;};
        void ThreadMain() override;
    };