#include <dirent.h>
#include "../Beyond.h"
#include "../Parse.h"
bool CJob::CSubJob::isFolder (unsigned char type){
    return type == 0x04;
}

bool CJob::CSubJob::isFile (unsigned char type){
    return type == 0x08;
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

    while (dirp){
        if (dp = readdir(dirp) ){
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
            }
        }
        else {
            break;
        }
    }
    closedir(dirp);

    return true;
}