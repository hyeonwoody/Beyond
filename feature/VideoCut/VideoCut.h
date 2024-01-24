
#include "../../Job.h"

class CVideoCut : public CJob
    {
    public :
    

    
    public :
        int result = 0;
    public :
        std::vector <SClip*> clipList;
        int proceed (CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup);
        //int proceed_(CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup);
        int setResult (int result) {this->result = result;};
        CJob::STime* parsePbf (std::string path, std::string file);
        
    };