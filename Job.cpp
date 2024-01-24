#include "Beyond.h"

#include "./feature/FileName/FileName.h"
#include "./feature/SymbolicLink/SymbolicLink.h"
#include "./feature/VideoCut/VideoCut.h"
#include "./feature/UpdateDB/UpdateDB.h"

CJob::~CJob(){
}

bool CJob::proceed(SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    SMapping *currentJob;
    int* ptrJob = NULL;
    for (int i=0; i<jobList.size(); i++){
        currentJob = jobList[i];
        bool isOption = false;
        
        this->pTest = new CJob::CTest(); 
        delete this->pTest;

        std::cout << "On Process New Job : "<<currentJob->description<<std::endl;
        unsigned int index = currentJob->index;
        CJob* tmp = nullptr;
        switch (index){
            case 2:
                if (currentJob->description[0] == 'O'){
                    tmp = new CFileName();
                    isOption = true;
                }
                else {
                    tmp = new CSymbolicLink();
                }
                break;
            case 3: //workpath
                if (currentJob->description[0] == 'O'){ //OptionGroup
                    isOption = true;
                } 
                else { //flagGroup
                    tmp = new CVideoCut();
                }
                break;
            case 4: //
                if (currentJob->description[0] == 'O'){ //OptionGroup
                    isOption = true;
                } 
                else {
                    
                }
                break;
            default:
                break;
        }
        #if DATABASE 
        update
        #endif
        if (tmp){
            tmp->proceed(this, optionGroup, flagGroup);
            delete (this->pSubJob);
        }
        
        std::cout << "Completed New Job : "<<currentJob->description<<std::endl;
    }
    return true;
}

int CJob::proceed(CJob* job, SOptionGroup* optionGroup, SFlagGroup* flagGroup) {
    // Implementation of the proceed function
    // ...
    return 0;  // Replace this with the actual implementation
}

bool CJob::pending(SMapping* job){
    jobList.push_back(job);
    return true;
}