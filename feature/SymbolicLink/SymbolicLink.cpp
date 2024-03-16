
#include "SymbolicLink.h"
#include <fcntl.h> //open
#include <unistd.h> //read, write, close
#include <cstdio> //BUFSIZ
#include <iostream>
#include <filesystem> //createDirectories

#include <sys/sendfile.h> //sendfile
#include <sys/stat.h> //fstat
#include <sys/stat.h> //mkdir
#include <sys/types.h> //fstat

int CSymbolicLink::proceed (CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    std::string path = optionGroup->workPath + "/";
    std::string currentPath="";
    std::string currentTag = optionGroup->fileTag;

    std::vector <std::string> fileList;
    std::vector <std::string> captionList;
    std::vector <std::string> symbolicList;

    CJob::CSubJob* pSubJob = pJob->pSubJob;
    if (!pSubJob->isDone()){
        pSubJob->getDirectory(path);
    }

        /**
         * NEEDs filename Spliter
        */
    
    fileList = pSubJob->fileList;
    captionList = pSubJob->captionList;
    symbolicList = pSubJob->symbolicLinkList;    
    
    mkdir(("/zzz/workstation/big/"+pSubJob->fileName[2]+"_"+pSubJob->fileName[0]).c_str(), 0777);
    currentPath = "/zzz/workstation/big/"+pSubJob->fileName[2]+"_"+pSubJob->fileName[0]+"/";


    for (int i = 0; i<fileList.size(); i++){
        std::string sourcePath = path+fileList[i];
        std::string destPath = currentPath + fileList[i];

        std::cout <<"SOURCE : "<<sourcePath <<std::endl;
        std::cout <<"DESTINATION : "<<destPath <<std::endl;

        if (symlink (sourcePath.c_str(), destPath.c_str()) != 0){
            std::cout<<"error on file symbolic"<<std::endl;
            this->setResult (-1);
        }
        // if (symlink ((path+fileList[i]).c_str(), (currentPath+fileList[i]).c_str()) != 0){
        //     std::cout<<"error on file symbolic"<<std::endl;
        //     this->setResult (-1);
        // }
    }

    for (int i = 0; i<captionList.size(); i++){
        if (symlink ((path+captionList[i]).c_str(), (currentPath+captionList[i]).c_str()) != 0){
            std::cout<<"error on caption symbolic"<<std::endl;
            this->setResult (-2);
        }
    }

    
    for (int i = 0; i<symbolicList.size(); i++){
        int source = open ((path+symbolicList[i]).c_str(), O_RDONLY, 0);
        int dest = open ((currentPath+symbolicList[i]).c_str(), O_WRONLY | O_CREAT, 0644);
        struct stat statSource;
        fstat (source, &statSource);

        sendfile(dest,source, 0, statSource.st_size); 
        close(source);
        close(dest);
    }

    return true;
}

void CSymbolicLink::ThreadMain() {
    
}