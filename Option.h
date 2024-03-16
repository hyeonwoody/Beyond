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
    COption();
    ~COption();
    void Cleanup();
    bool add_option_insert (SMapping* currentMapping);

    template <typename AssignTo>
    bool add_option(std::string optionName, AssignTo& variable, std::string optionDescription = "", bool essential = false);

    
    bool add_flag_insert (SMapping* currentMapping);
    
    bool add_flag(std::string flag_name, bool& variable, std::string flag_description="");

    void Init();
    void GetFeature(unsigned int feature);
};