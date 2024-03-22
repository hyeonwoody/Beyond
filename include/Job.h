#pragma once
#include "Option.h"
#include <vector>
#include <string>

class CJob
{
public:

    struct SClip{
        std::string source = "";
        std::string name = "";
        int startTime = 0;
        int endTime = 0;
    };
    class CSubJob
    {
    private:
        bool done;
    public:
        std::vector <std::string> fileList; 
        std::vector <std::string> captionList;
        std::vector <std::string> symbolicLinkList;
        std::vector <std::string> pbfList;
        
        
        std::string fileName[8]= {"",};
        bool isFolder(unsigned char type);
        bool isFile(unsigned char type);
        bool isSymbolicLink (unsigned char type);
        bool getDirectory(std::string filePath);
        void setDone(bool value);
        bool isDone();
        
    };

    CJob();
    ~CJob(); 

public:
    std::vector <SMapping*> jobList;
    bool pending (SMapping* job);
    bool proceed (SOptionGroup* optionGroup, SFlagGroup* flagGroup);

    CSubJob* pSubJob;
    // ~CJob(){
    //     delete pSubJob;
    //     delete pFileName;
    //     delete pSymbolicLink;
    //     delete pVideoCut;
    // }
};
