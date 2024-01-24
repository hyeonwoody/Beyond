#pragma once
#include <string>
#include <cstring>
struct SOptionGroup{
    std::string workPath;
    std::string currentPath;
    std::string jobPath;
    std::string subject;
    std::string fileTag;
};

struct SFlagGroup{
    bool copy;
    bool subtitle;
    bool symbolicLink;
    bool cut;
};

struct SMapping{
    std::string name;
    void* address;
    unsigned int index;
    bool isInt;
    bool essential;
    bool used;
    std::string description;  
};

class COption
{
private:
    void Cleanup(){
        if (optionList)
            free(optionList);
        if (flagList)
            free(flagList);
    }

public:
public:
    int m_argc;
    char** m_argv;
    
    
    SMapping* optionList; //string // index
    unsigned int optionListIndex;
    unsigned int optionIndex;
    
    SMapping* flagList;
    unsigned int flagListIndex;
    unsigned int flagIndex;

    SOptionGroup optionGroup;
    SFlagGroup flagGroup;
    

public:
    COption(){
        m_argc = 0;
        m_argv = nullptr;

        optionListIndex = 0;
        optionIndex = 0;
        
        flagListIndex = 0;
        flagIndex = 0;


        memset (&optionGroup, 0, sizeof(SOptionGroup));
        optionGroup.workPath = "W:";
        optionGroup.currentPath = "/zzz/workstation/Movie/Others";
        
        memset (&flagGroup, 0, sizeof(SFlagGroup));

    }
    ~COption(){
        Cleanup();
    }

    bool add_option_insert (SMapping* currentMapping);

    template <typename AssignTo>
    bool add_option(std::string optionName, AssignTo& variable, std::string optionDescription = "", bool essential = false);

    
    bool add_flag_insert (SMapping* currentMapping);
    
    bool add_flag(std::string flag_name, bool& variable, std::string flag_description="");

    void Init();
    void GetFeature(unsigned int feature);
};