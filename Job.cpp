#include "Beyond.h"

bool CJob::symbolicLink (SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    CSymbolicLink symbolicLink;

    symbolicLink.proceed(optionGroup, flagGroup);
    return true;
}

bool CJob::fileName(SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    CFileName fileName;

    fileName.proceed(optionGroup, flagGroup);
    return true; 
}

bool CJob::proceed(SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    
    while (jobList.size() != 0){
        SMapping *newJob = jobList.back();
        jobList.pop_back();

        switch (newJob->index){
            case 3: //workpath
                if (newJob->description[0] == 'O') //OptionGroup
                    fileName(optionGroup, flagGroup);
                else 
                    symbolicLink(optionGroup, flagGroup);
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