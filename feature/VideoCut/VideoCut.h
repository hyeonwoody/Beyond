#include "../Feature.h"
#include <vector>

extern "C" {

    #include "../../libs/FFmpeg/libavutil/timestamp.h"
    #include "../../libs/FFmpeg/libavformat/avformat.h"
}

class CVideoCut : public CFeature
{

    public :
        static CFeature *Create() {return new CVideoCut();}

    

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
    void finalize() {
        if (!clipList.empty()){
            for (SClip* clip : clipList){
                delete(clip);
                clip = nullptr;
            }
            clipList.clear();
        }
    }
    struct SFile {
    AVFormatContext *formatContext;
    std::string fileName;
    };

    public :
        int result = 0;
    public :
        std::vector <SClip*> clipList;
        int proceed (CJob* pjob, SOptionGroup* optionGroup, SFlagGroup* flagGroup) override;
        void ThreadMain() override;
        //int proceed_(CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup);
        int setResult (int result) {this->result = result;};
        STime* parsePbf (std::string path, std::string file);
};