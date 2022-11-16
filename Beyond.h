
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <map>


#define OPTION_NUM 8
#define FLAG_NUM 10

#define WINDOWS 0




struct SOptionGroup{
    std::string workPath;
    std::string currentPath;
    std::string jobPath;
    std::string subject;
    std::string fileTag;
};

struct SMapping{
    std::string name;
    void* address;
    unsigned int index;
    bool isInt;
    ~SMapping(){}
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
    bool add (SMapping* job);
    bool proceed(SOptionGroup* optionGroup);

    bool fileName(SOptionGroup* optionGroup);
};



class CFileName
{
public:
    std::map <std::string, int> format;
    std::string* collection;
    std::string path;

    int tagIndex = 0;
    int nameIndex = 0 ;
    int align = 0;


public:
    CFileName (){
        const unsigned int formatLength = 8;
        format.insert({"title", 0});

        format.insert({"episode", 1});
        format.insert({"E00", 1});
        format.insert({"E000", 1});
        format.insert({"S00E00", 1});
        format.insert({"S00E000", 1});

        format.insert({"date", 2});
        
        format.insert({"subtitle", 3});
        
        format.insert({"resolution", 4});
        
        format.insert({"reel", 5});
        format.insert({"reels", 5});
        
        format.insert({"codec", 6});
        
        format.insert({"extension", 7});

        collection = (std::string *) malloc (sizeof(std::string) * format.size());
    }
    ~CFileName (){
        free(collection);
    }


    bool isFile (unsigned char type);
    bool isFolder (unsigned char type);

    bool proceed(SOptionGroup* info);
    
    void setPath(std::string newPath) {path = newPath;};
    std::string getPath(){return path;};

    std::string formatParse(int order, std::vector <std::string> fileTag, std::vector <std::string> fileName);

    std::string episodeParse(std::string tag, std::vector <std::string> fileName);
    std::string dateParse(std::vector <std::string> fileName);
    std::string resolutionParse(int length, std::vector <std::string> fileName);
    std::string reelsParse(std::vector <std::string> fileName);
    std::string codecParse(std::vector <std::string> fileName);
    std::string extensionParse(std::vector <std::string> fileName);
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

    

    SMapping optionList[OPTION_NUM]; //string // index
    unsigned int optionListIndex;
    unsigned int optionIndex;
    
    SMapping flagList[FLAG_NUM];
    unsigned int flagIndex;

    SFlagGroup flagGroup;
    SOptionGroup optionGroup;

    
    
    

public:
    COption(){
        m_argc = 0;
        m_argv = nullptr;

        optionListIndex = 0;
        optionIndex = 0;
        
        flagIndex = 0;

        memset (&optionGroup, 0, sizeof(SOptionGroup));
        optionGroup.workPath = "W:";
        optionGroup.currentPath = "D:\\Users\\220618\\Store";
        
        memset (&flagGroup, 0, sizeof(SFlagGroup));

    }
    ~COption(){
        
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
    int ProceedJob();

private:
    
};

extern CMain app;