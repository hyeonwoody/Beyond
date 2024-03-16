#include "../Feature.h"
#include "../../Job.h"
#include "../../Parse.h"
#include <map>
#include <vector>


class CFileName : public CFeature
{

    public :
        static CFeature *Create() {return new CFileName();}
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
        ~CFileName();
        int proceed(CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup);
        
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
