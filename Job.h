#pragma once
#include "Option.h"
#include <vector>
#include <string>

class CJob
{
public:

    struct STime{
        int hour = 0;
        int minute = 0;
        int second = 0;
        std::string source = "";
        std::string name = "";
        bool value = false;
    };

    struct SClip{
        std::string source = "";
        std::string name = "";
        int startTime = 0;
        int endTime = 0;
    };

    class CSubJob
    {
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
        
        
    };

    CJob(){
        pTest =nullptr;

    }
    virtual ~CJob(); 

    

    class CTest
    {
    public:
        CTest()
        {
            printf("Constructor : %x\n", this);
        }
        ~CTest()
        {
            printf("Destructor : %x\n", this);
        }
        int a;
    };

public:
    std::vector <SMapping*> jobList;
    bool pending (SMapping* job);
    bool proceed (SOptionGroup* optionGroup, SFlagGroup* flagGroup);
    virtual int proceed(CJob* job, SOptionGroup* optionGroup, SFlagGroup* flagGroup);

    CJob::CSubJob* pSubJob;
    CTest* pTest; //for Test Purpose
    // ~CJob(){
    //     delete pSubJob;
    //     delete pFileName;
    //     delete pSymbolicLink;
    //     delete pVideoCut;
    // }
};
