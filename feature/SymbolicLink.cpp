#include "../Beyond.h"

bool CJob::CSymbolicLink::proceed (CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    
    std::string path = optionGroup->workPath + "/";
    std::string folderName;
    std::string currentTag = optionGroup->fileTag;
    std::vector <std::string> vCurrentName;
    std::vector <std::string> vCurrentTag;
   


    if (pJob->pTest == nullptr){
        
    }
    if (1){
        std::cout << "it is not nullptr"<<std::endl;
    }
    else {
        std::cout << "it is null"<<std::endl;
    }
    return true;
}