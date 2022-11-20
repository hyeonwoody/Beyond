#include "Beyond.h"

bool CJob::proceed(SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    while (jobList.size() != 0){
        SMapping *newJob = jobList.back();
        jobList.pop_back();
        bool isFlag = false;

        unsigned int index = newJob->index;

        switch (index){
            case 2:
                if (newJob->description[0] == 'O'){

                }
                else {
                    this->pSymbolicLink = new CJob::CSymbolicLink();
                    this->pSymbolicLink->proceed(this, optionGroup, flagGroup);
                    isFlag = true;
                }
                break;
            case 3: //workpath
                if (newJob->description[0] == 'O'){ //OptionGroup
                    this->pFileName = new CJob::CFileName();
                    this->pFileName->proceed(this, optionGroup, flagGroup);
                } 
                else {
                    isFlag = true;
                }
                break;
            default:
                break;
        }
        #if DATABASE 
        this->pSubJob->updateDB (index, isFlag);
        #endif

        
        std::cout << "new job : "<<newJob->description<<std::endl;
    }
    return true;
}


bool CJob::pending(SMapping* job){
    jobList.push_back(job);
    return true;
}