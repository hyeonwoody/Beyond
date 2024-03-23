#include "../Feature.h"
#include "Job.h"
#include "Parse.h"
#include <map>
#include <vector>


class CFileName : public CFeature
{
    public:
        std::map <std::string, int> format;
        std::string path;

        int tagIndex = 0;
        int nameIndex = 0 ;
        int align = 0;

    public:
        CFileName ();
        ~CFileName();
        static CFeature *Create() {return new CFileName();}
        int proceed(CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup) override;
        
        void setPath(std::string currentPath) {path = currentPath;};
        std::string getPath(){return path;};

        std::string formatParse(int order, std::vector <std::string> fileTag, std::vector <std::string> fileName);
        std::string episodeParse(std::string tag, std::vector <std::string> fileName);
        std::string dateParse(std::vector <std::string> fileName);
        std::string resolutionParse(int length, std::vector <std::string> fileName);
        std::string reelsParse(std::vector <std::string> fileName);
        std::string codecParse(std::vector <std::string> fileName);
        std::string extensionParse(std::vector <std::string> fileName);

        void ThreadMain() override;
};
