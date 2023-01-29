#include "Beyond.h"

bool CJob::proceed(SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    this->pSubJob = new CJob::CSubJob();
    SMapping *currentJob;
    for (int i=0; i<jobList.size(); i++){
        currentJob = jobList[i];
        bool isFlag = false;

        this->pTest = new CJob::CTest(); 
        delete this->pTest;

        std::cout << "On Process New Job : "<<currentJob->description<<std::endl;
        unsigned int index = currentJob->index;
        switch (index){
            case 2:
                if (currentJob->description[0] == 'O'){
                    this->pFileName = new CJob::CFileName();
                    this->pFileName->proceed(this, optionGroup, flagGroup);
                    delete pFileName;
                }
                else {
                    this->pSymbolicLink = new CJob::CSymbolicLink();
                    this->pSymbolicLink->proceed(this, optionGroup, flagGroup);
                    isFlag = true;
                    delete pSymbolicLink;
                }
                break;
            case 3: //workpath
                if (currentJob->description[0] == 'O'){ //OptionGroup
                    
                } 
                else { //flagGroup
                    this->pVideoCut = new CJob::CVideoCut();
                    this->pVideoCut->proceed(this, optionGroup, flagGroup);
                    isFlag = true;
                    delete pVideoCut;
                    isFlag = true;
                }
                break;
            case 4: //
                if (currentJob->description[0] == 'O'){ //OptionGroup
                } 
                else {
                    
                }
                break;
            default:
                break;
        }
        #if DATABASE 
        this->pSubJob->updateDB (index, isFlag);
        #endif

        std::cout << "Completed New Job : "<<currentJob->description<<std::endl;
    }
    return true;
}


bool CJob::pending(SMapping* job){
    jobList.push_back(job);
    return true;
}