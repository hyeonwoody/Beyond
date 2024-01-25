
#include <dirent.h>
#include "../Beyond.h"
#include "../Parse.h"
#include <map>

    
    void CJob::CSubJob::setDone(bool value){
        this->done = value;
    }
    bool CJob::CSubJob::isDone(){
        return this->done;
    }


    bool CJob::CSubJob::isFolder (unsigned char type){
        return type == 0x04;
    }

    bool CJob::CSubJob::isFile (unsigned char type){
        return type == 0x08;
    }
    bool CJob::CSubJob::isSymbolicLink (unsigned char type){
        return type == 0x0A;
    }

bool CJob::CSubJob::getDirectory (std::string path){
    DIR* dirp;
    struct dirent* dp;
    std::string* name;
    dirp = opendir(path.c_str());
    unsigned int caption = 0;
    int a = 0;

    std::map <std::string, int> extension;
    extension.insert({"srt", 0});
    extension.insert({"SRT", 0});
    extension.insert({"smi", 1});
    extension.insert({"SMI", 1});
    extension.insert({"txt", 2});
    extension.insert({"mp4", 3});
    extension.insert({"MP4", 3});
    extension.insert({"mkv", 3});
    extension.insert({"MKV", 3});
    extension.insert({"pbf", 4});
    
    /**
     * Initialization (captionList.shrink_to_fit())
    */
    if (this->captionList.size() > 0){
        captionList.clear();
        std::vector<std::string>().swap(captionList);
    }
    if (this->fileList.size() > 0){
        fileList.clear();
        std::vector<std::string>().swap(fileList);
    }
    if (this->pbfList.size() > 0){
        pbfList.clear();
        std::vector<std::string>().swap(pbfList);

    }

    std::cout<<std::endl<<"File List :"<<std::endl;
    while (dirp){
        if (dp = readdir(dirp)){
            std::cout<<dp->d_name<<std::endl;
            if (isFile (dp->d_type)){
                std::map<std::string, int>::const_iterator pos = extension.find(tail (dp->d_name, 3));
                if (pos->second == 0){
                    captionList.push_back(dp->d_name);
                    caption++;
                }
                else if (pos->second == 1){
                    /**
                     * Write code for SMI -> srt
                    */
                }
                else if (pos->second == 3){
                    fileList.push_back(dp->d_name);
                }
                else if (pos->second == 4){
                    pbfList.push_back(dp->d_name);
                }
            }
            else if (isSymbolicLink(dp->d_type)){
                symbolicLinkList.push_back(dp->d_name);
            }
        }
        else {
            break;
        }
    }
    std::cout<<"End of The File"<<std::endl<<std::endl;
    closedir(dirp);

    this->setDone(true);

    return true;
}