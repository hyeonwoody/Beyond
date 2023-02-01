#include <map>
#include <vector>
#include <string>

class CJob
{
public:

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
        bool updateDB(unsigned int index, bool isFlag);
    };

    class CFileName
    {
    public:
        std::map <std::string, int> format;
        std::string path;

        int tagIndex = 0;
        int nameIndex = 0 ;
        int align = 0;
    public:
        CFileName (){
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
        }

        bool proceed(CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup);
        
        void setPath(std::string currentPath) {path = currentPath;};
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

    class CVideoCut
    {
    public :
    struct STime{
        int hour = 0;
        int minute = 0;
        int second = 0;
        std::string source = "";
        std::string name = "";
        bool value = false;
    };

    struct SVideo{
        std::string source = "";
        std::string name = "";
        int startTime = 0;
        int endTime = 0;
    };

    public :
        int proceed (CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup);
        CJob::CVideoCut::STime* parsePbf (std::string path, std::string file);
    };

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
    CJob(){
        
    }
    bool pending (SMapping* job);
    bool proceed(SOptionGroup* optionGroup, SFlagGroup* flagGroup);

    CSubJob* pSubJob = nullptr;
    CFileName* pFileName = nullptr;
    CSymbolicLink* pSymbolicLink = nullptr;
    CVideoCut* pVideoCut = nullptr;
    CTest* pTest = nullptr; //for Test Purpose

    // ~CJob(){
    //     delete pSubJob;
    //     delete pFileName;
    //     delete pSymbolicLink;
    //     delete pVideoCut;
    // }
};
