
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <map>


#define OPTION_NUM 8
#define FLAG_NUM 10

struct SMapping{
std::string name;
void* address;
unsigned int index;
bool isInt;
bool essential;
bool used;
std::string description;  
};

class CJob
{
public:
    std::vector <SMapping*> jobList;
    CJob(){
        
    }
    bool add_job_todo (SMapping* job);
};



class CFileName
{
public:
    std::map <std::string, int> format;
    std::string* collection;

public:
    CFileName (){
        format.insert({"title", 0});
        format.insert({"episode", 1});
        format.insert({"date", 2});
        format.insert({"subtitle", 3});
        format.insert({"resolution", 4});
        format.insert({"reel", 5});
        format.insert({"codec", 6});
        format.insert({"extension", 7});
        collection = (std::string *) malloc (sizeof(std::string) * format.size());
        
    }
};

class COption
{
    
public:
    int m_argc;
    char** m_argv;
    

    struct SFlagGroup{
        bool copy;
        bool subtitle;
        bool a;
        bool b;
        bool c;
    }; 

    struct SOptionGroup{
        std::string workPath;
        std::string currentPath;
        std::string jobPath;
        std::string subject;
        std::string fileName;
    };

    SMapping optionList[OPTION_NUM]; //string // index
    unsigned int optionIndex;
    
    SMapping flagList[FLAG_NUM];
    unsigned int flagIndex;

    SFlagGroup flagGroup;
    SOptionGroup optionGroup;

    
    
    

public:
    COption(){
        m_argc = 0;
        m_argv = nullptr;

        
        optionIndex = 0;
        flagIndex = 0;

        memset (&optionGroup, 0, sizeof(SOptionGroup));
        optionGroup.workPath = "W:";
        optionGroup.currentPath = "D:\\Users\\220618\\Store";
        
        memset (&flagGroup, 0, sizeof(SFlagGroup));

    }
    
    bool add_option_insert (SMapping* newMapping);

    template <typename AssignTo>
    bool add_option(std::string optionName, AssignTo& variable, std::string optionDescription = "", bool essential = false);

    
    bool add_flag_insert (SMapping* newMapping);
    
    bool add_flag(std::string flag_name, bool& variable, std::string flag_description="");

    void Init();
    void GetFeature(unsigned int feature);
};


class CMain
{
public:
    COption option;
    CJob job;
public:
    CMain(){
    }
    void Init();
    int Main();

    int ParseParam();

private:
    
};

extern CMain app;