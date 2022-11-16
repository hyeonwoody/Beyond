#include "Beyond.h"

bool CJob::fileName(SOptionGroup* optionGroup){
    CFileName fileName;

    fileName.proceed(optionGroup);
    return true; 
}

bool CJob::proceed(SOptionGroup* optionGroup){
    
    while (jobList.size() != 0){
        SMapping *newjob = jobList.back();
        jobList.pop_back();

        switch (newjob->index){
            case 3: //workpath
                fileName(optionGroup);
                break;
            default:
                break;
        }
        

        std::cout << "new job : "<<newjob->description<<std::endl;
    }
    return true;
}


bool CJob::add(SMapping* job){
    jobList.push_back(job);
    return true;
}