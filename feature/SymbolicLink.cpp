#include "../Beyond.h"
#include <unistd.h>

#include <sys/stat.h> //mkdir
#include <sys/types.h>

bool CJob::CSymbolicLink::proceed (CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    
    std::string path = optionGroup->workPath + "/";
    std::string newPath ="";
    std::string currentTag = optionGroup->fileTag;

    std::vector <std::string> fileList;
    std::vector <std::string> captionList;


    //memcpy (&fileName, &pJob->pSubJob->fileName, sizeof(pJob->pSubJob->fileName));

    CJob::CSubJob* pSubJob = pJob->pSubJob;

    if (pJob->pFileName != nullptr){
        fileList = pSubJob->fileList;
        captionList = pSubJob->captionList;   
    }
    else {
        pSubJob->getDirectory(path);
    }
    mkdir(("/zzz/workstation/Movie/Others/"+pSubJob->fileName[2]+"_"+pSubJob->fileName[0]).c_str(), 0777);
    newPath = "/zzz/workstation/Movie/Others/"+pSubJob->fileName[2]+"_"+pSubJob->fileName[0]+"/";


    newPath = "/zzz/workstation/Movie/Others/";
    for (int i = 0; i<fileList.size(); i++){
        if (symlink ((path+fileList[i]).c_str(), (newPath+fileList[i]).c_str()) != 0){
            std::cout<<"error on file symbolic"<<std::endl;
        }
    }

    for (int i = 0; i<captionList.size(); i++){
        if (symlink ((path+captionList[i]).c_str(), (newPath+captionList[i]).c_str()) != 0){
            std::cout<<"error on caption symbolic"<<std::endl;
        }
    }

    return true;
}