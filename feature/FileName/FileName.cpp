
#include <dirent.h>

#include "FileName.h"

CFileName::CFileName (){
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

CFileName::~CFileName(){
    format.clear();
}

std::string CFileName::extensionParse (std::vector <std::string> fileName){
    return fileName[nameIndex];
}

std::string CFileName::codecParse (std::vector <std::string> fileName){
    return fileName[nameIndex];
} 

std::string CFileName::reelsParse (std::vector <std::string> fileName){
    return fileName[nameIndex];
}

std::string CFileName::resolutionParse(int length, std::vector <std::string> fileName){
    std::string name = "";
    for (int i = nameIndex - 1; i < nameIndex + length; i++){
        name = fileName[nameIndex] + ".";
    }
    name.pop_back();
    return name;
}

std::string CFileName::dateParse(std::vector <std::string> fileName){
    return fileName[nameIndex];
}
std::string CFileName::episodeParse(std::string tag, std::vector <std::string> fileName){
    enum {
        E00,
        E000,
        S00E00,
        S00E000,

    };
    unsigned int season = 0;
    unsigned int episode = 0;
    std::string name ="";
    std::string sFileName = fileName[nameIndex];
    int type = -1;
    std::map<std::string, int>::const_iterator pos = format.find(tag);
    if (pos->first == "E00"){
        name += "E";
        name += sFileName.substr(1).c_str();
    }
    else if (pos->first =="E000"){
        type = E000;
    }
    else if (pos->first =="S00E00"){
        name += "S";
        name += sFileName.substr(1).c_str();
        type = S00E00;
    }
    else if (pos->first =="S00E000"){
        type = S00E000;
    }

    return name;
}

// std::string CJob::CFileName::phraseParse(int end, std::vector <std::string> fileName){
//         std::string title = "";
//         for (int i = nameIndex; i< nameIndex + end; i++){
//             title += fileName[i] + " ";
//             nameIndex++;
//         }
//         title.pop_back();
//         return title;
// }

std::string CFileName::formatParse(int order,std::vector <std::string> fileTag, std::vector <std::string> fileName){
    std::string name = "";
    int size = fileName.size();
    int length = 0;
    switch (order){
        case 0: //title
            fileTag[++tagIndex].pop_back();
            length = atoi(fileTag[tagIndex].substr(1).c_str());
            name = phraseParse(nameIndex, length, fileName);
            nameIndex += length;
            break;
        case 1: //episode
            name = episodeParse(fileTag[tagIndex], fileName);
            nameIndex++;
            break;
        case 2: //date
            name = dateParse (fileName);
            nameIndex++;
            break;
        case 3: //subtitle
            fileTag[++tagIndex].pop_back();
            length = atoi(fileTag[tagIndex].substr(1).c_str());
            name = phraseParse(nameIndex, length, fileName);
            nameIndex += length;
            break;
        case 4: //resolution
            if (fileTag[tagIndex+1].at(0) == '['){
                fileTag[++tagIndex].pop_back();
                length = atoi(fileTag[tagIndex].substr(1).c_str());
            }
            name = resolutionParse(length, fileName);
            nameIndex++;
            break;
        case 5: //reels
            name = reelsParse(fileName);
            nameIndex++;
            break;
        case 6: //codec
            name = codecParse(fileName);
            nameIndex++;
            break;
        case 7: //extension
            name = extensionParse(fileName);
            nameIndex++;
            break;
        defaut :
            nameIndex++;
            break;
    }
    tagIndex++;
    return name;
}

int CFileName::proceed (CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    const std::string path = optionGroup->workPath + "/";
    std::string folderName;
    std::string currentTag = optionGroup->fileTag;
    std::vector <std::string> vCurrentName;
    std::vector <std::string> vCurrentTag;

    std::vector <std::string> fileList;
    std::vector <std::string> captionList;
    std::vector <std::string> symbolicLinkList;
    std::vector <std::string> pbfList;

    std::string fileName[8]= {"",};
    CJob::CSubJob* pSubJob = pJob->pSubJob; 
    pSubJob->getDirectory(path);

    fileList = pSubJob->fileList;
    captionList = pSubJob->captionList;
    pbfList = pSubJob->pbfList;

    unsigned int caption = pJob->pSubJob->captionList.size();

    vCurrentTag =  spliter(currentTag, '.');
    // fileName = pSubJob->getTag();

    for (int i=0; i<fileList.size(); i++){
        std::string index;
        index = std::to_string(i);
        std::string name = fileList[i];
        vCurrentName = spaceSpliter (fileList[i], '.');
        int j=0;

        while (j<vCurrentTag.size()){
            std::map<std::string, int>::const_iterator pos = format.find(vCurrentTag[tagIndex]);
            if (nameIndex == vCurrentName.size()){
                std::cout<<"Number of tag exeeds length of the file name"<<std::endl;
                return 0;
            }
            if (pos != format.end()){
                name = formatParse(pos->second, vCurrentTag, vCurrentName);
                fileName[pos->second] = name;
                pJob->pSubJob->fileName[pos->second] = name;
            }
            else { 
                tagIndex++;
                nameIndex++;
            }
            j = tagIndex;
        }

        name = "";
        for (int j=0; j<7; j++){
            if (fileName[j] == ""){
                continue;
            }
            name += fileName[j] + ".";
        }

        if (rename ((path+fileList[i]).c_str(), (path+name+fileName[7]).c_str()) != 0){
            std::cout<<"error renaming video"<<std::endl;
        }
        else{
            if (pbfList.size()){
                if (rename ((path+pbfList[i]).c_str(), (path+name+"pbf").c_str()) != 0){
                    std::cout<<"error renaming pbf"<<std::endl;
                }
                else {
                    pbfList[i] = name + "pbf";
                    pJob->pSubJob->pbfList[i] = name + "pbf";
                    std::cout<<"sucess on renaming pbf"<<std::endl;
                }
            }
            fileList[i] = name+fileName[7];
            pJob->pSubJob->fileList[i] = name+fileName[7];
            std::cout<<"success on video"<<std::endl;
            nameIndex = 0;
            tagIndex = 0;
        }
        if (caption){
            if (rename ((path+captionList[i]).c_str(), (path+name+"srt").c_str())){
                std::cout<<"error renaming caption"<<std::endl;
            }
            else {
                captionList[i] = name+"srt";
                pJob->pSubJob->captionList[i] = name + "srt";
                std::cout<<"success on caption"<<std::endl;
            }
            caption--;
        }
    }
    for (int i=0; i<8; i++){
        pJob->pSubJob->fileName[i] = fileName[i];
    }
    return 1;
}

void CFileName::ThreadMain () {
    
}