#include "Beyond.h"

CJob::CSymbolicLink* CJob::symbolicLink (SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    this->pSymbolicLink = new CJob::CSymbolicLink();
    CSymbolicLink* newSymbolicLink = this->pSymbolicLink;
    
    newSymbolicLink->proceed(this, optionGroup, flagGroup);
    return newSymbolicLink;
}

CJob::CFileName* CJob::fileName(SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    this->pFileName = new CJob::CFileName();
    CFileName* newFileName = this->pFileName;

    newFileName->proceed(this, optionGroup, flagGroup);
    return newFileName; 
}

bool CJob::proceed(SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    
    while (jobList.size() != 0){
        SMapping *newJob = jobList.back();
        jobList.pop_back();

        switch (newJob->index){
            case 2:
                if (newJob->description[0] == 'O'){

                }
                else 
                    pSymbolicLink = symbolicLink(optionGroup, flagGroup);
                break;
            case 3: //workpath
                if (newJob->description[0] == 'O') //OptionGroup
                    pFileName = fileName(optionGroup, flagGroup);
                else {}
                break;
            default:
                break;
        }
        

        std::cout << "new job : "<<newJob->description<<std::endl;
    }
    return true;
}


bool CJob::pending(SMapping* job){
    jobList.push_back(job);
    return true;
}