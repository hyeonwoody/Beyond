#pragma once
#include "Job.h"

class CFeature {
    public :
    virtual int proceed (CJob* pjob, SOptionGroup* optionGroup, SFlagGroup* flagGroup) = 0;
    virtual void ThreadMain() = 0;
};