#include "../Beyond.h"
#include <fcntl.h> //open
#include <unistd.h> //read, write, close
#include <cstdio> //BUFSIZ

#include <sys/sendfile.h> //sendfile
#include <sys/stat.h> //fstat
#include <sys/stat.h> //mkdir
#include <sys/types.h> //fstat

bool CJob::CSymbolicLink::proceed (CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    
    std::string path = optionGroup->workPath + "/";
    std::string newPath ="";
    std::string currentTag = optionGroup->fileTag;

    std::vector <std::string> fileList;
    std::vector <std::string> captionList;
    std::vector <std::string> symbolicList;

    CJob::CSubJob* pSubJob = pJob->pSubJob;
    
    pSubJob->getDirectory(path);
    
    fileList = pSubJob->fileList;
    captionList = pSubJob->captionList;
    symbolicList = pSubJob->symbolicLinkList;    
    
    mkdir(("/zzz/workstation/Movie/Others/"+pSubJob->fileName[2]+"_"+pSubJob->fileName[0]).c_str(), 0777);
    newPath = "/zzz/workstation/Movie/Others/"+pSubJob->fileName[2]+"_"+pSubJob->fileName[0]+"/";


    for (int i = 0; i<fileList.size(); i++){
        std::cout<<"왜 두번 "<<path+fileList[i]<<std::endl;
        if (symlink ((path+fileList[i]).c_str(), (newPath+fileList[i]).c_str()) != 0){
            std::cout<<"error on file symbolic"<<std::endl;
        }
    }

    for (int i = 0; i<captionList.size(); i++){
        if (symlink ((path+captionList[i]).c_str(), (newPath+captionList[i]).c_str()) != 0){
            std::cout<<"error on caption symbolic"<<std::endl;
        }
    }

    
    for (int i = 0; i<symbolicList.size(); i++){
        int source = open ((path+symbolicList[i]).c_str(), O_RDONLY, 0);
        int dest = open ((newPath+symbolicList[i]).c_str(), O_WRONLY | O_CREAT, 0644);
        struct stat statSource;
        fstat (source, &statSource);

        sendfile(dest,source, 0, statSource.st_size); 
        close(source);
        close(dest);
    }

    return true;
}