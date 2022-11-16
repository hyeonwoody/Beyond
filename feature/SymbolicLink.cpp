#include "../Beyond.h"

bool CJob::CSymbolicLink::proceed (CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    
    if (pJob->pTest == nullptr){
        std::cout << "Test is null"  << std::endl;
    }
    if (1){
        std::cout << "it is not nullptr"<<std::endl;
    }
    else {
        std::cout << "it is null"<<std::endl;
    }
    return true;
}