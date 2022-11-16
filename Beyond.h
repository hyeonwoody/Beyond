
#include <iostream>
#include <string.h>
#include <string>
#include <vector>
#include <map>


#define OPTION_NUM 8
#define FLAG_NUM 6 

#define WINDOWS 0


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


class CJob
{
public:

    class CFileName
    {
    public:
        std::map <std::string, int> format;
        std::string* collection;
        std::string path;

        int tagIndex = 0;
        int nameIndex = 0 ;
        int align = 0;

        std::vector <std::string> fileList; 
        std::vector <std::string> captionList;
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

        bool proceed(CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup);
        
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

    class CSymbolicLink
    {
    public :
        bool proceed (CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup);
    };

    class CTest
    {
    public:
        int a;
    };
public:
    std::vector <SMapping*> jobList;
    CJob(){
        
    }
    bool pending (SMapping* job);
    bool proceed(SOptionGroup* optionGroup, SFlagGroup* flagGroup);

    CFileName* fileName(SOptionGroup* optionGroup, SFlagGroup* flagGroup);
    CFileName* pFileName = nullptr;

    CSymbolicLink* symbolicLink(SOptionGroup* optionGroup, SFlagGroup* flagGroup);
    CSymbolicLink* pSymbolicLink = nullptr;

    CTest* pTest = nullptr;
};

class COption
{
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
        optionGroup.currentPath = "D:\\Users\\220618\\Store";
        
        memset (&flagGroup, 0, sizeof(SFlagGroup));

    }
    ~COption(){
        free(optionList);
        free(flagList);
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
public:

private:
    
};

extern CMain app;