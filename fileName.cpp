#include <stdio.h>
#include <filesystem>

#include <dirent.h>

#include "Beyond.h"
#include "Parse.h"


namespace fileName{


string formatParse(int order, std::vector <std::string> fileName){
    string name = "";
    
    switch (order){
        case 0:
            for (int i=index[order]; i<fileName.size(); i++){
                if (fileName[i].at(0) == "["){
                    break;
                }
                name += fileName[i] + " ";
                index[0] = i;   
            }
            break;
        case 1:
            fileName[i+index[0]];
            break;
        case 2:
            break;
        case 3:
            break;
    }
    return name;
}

bool CFileName::proceed (SOptionGroup* option){
    std::string path = option->workPath;
    std::string folderName;
    std::string currentOrder = option->fileName;
    std::vector <std::string> vCurrentName;
    std::vector <std::string> vCurrentOrder;

    std::map <std::string, int> extension;

    extension.insert({"srt", 0});
    extension.insert({"SRT", 0});
    extension.insert({"smi", 1});
    extension.insert({"SMI", 1});


    struct SFile{
        unsigned short m_size;
        unsigned short m_type;
        char* m_name;
    };

    SFile fileList[256]; 
    //////////////////////////////

    DIR* dirp;
    struct dirent* dp;
    std::string* name;
    dirp = opendir(path.c_str());
    int fileIndex = 0;

    int a = 0;
    while (dirp){
        if (dp = readdir(dirp) ){
            std::cout<<dp->d_name<<std::endl;
            if (fileIndex>1){
                if (extension.find(tail (dp->d_name, 3)) == extension.end()){
                    fileList[fileIndex-2].m_name = (char*) malloc(sizeof(char)*dp->d_namlen);
                    strcpy(fileList[fileIndex-2].m_name, dp->d_name);
                    fileList[fileIndex-2].m_size = dp->d_namlen;
                    std::string time = tail (dp->d_name, 3);
                }
                // if (rename ((path+"\\"+dp->d_name).c_str(), (path+"\\"+"AGU"+out).c_str()) != 0){
                //     std::cout<<"error renaming"<<std::endl;
                // }
            }
            fileIndex++;
        }
        else {
            break;
        }
    }
    closedir(dirp);


    vCurrentName = spliter(fileList[0].m_name, '.');
    vCurrentOrder =  spliter(order, ".");


    for (int i = 0; i<vNameFormat.size(); i++){
        std::cout<<vNameFormat[i]<<std::endl;
    }

    fileIndex -= 2;

    for (int i=0; i<fileIndex; i++){
        fileList[i].m_name;
        std::string index;
        index = std::to_string(i);
        std::string name = "";
        for (int j=0; j<vCurrentOrder.size(); j++){
            std::map<std::string, int>::const_iterator pos = format.find(vNameFormat[j]);
            if (pos == format.end()){
                name += vNameFormat[j] + "damn"; //not found
            }
            else {
                name = formatParse(pos->second, vCurrentName);
                switch (pos->second){
                    case 0:
                        break;
                    case 1:
                        break;
                    case 2:
                        break;
                    case 3:
                        break;
                    case 4:
                        break;
                    case 5:
                        break;
                    case 6:
                        break;
                    case 7:
                        break;
                    default :
                        break;
                }
            }
            name += ".";
        }
        
        if (rename ((path+"\\"+fileList[i].m_name).c_str(), (name).c_str()) != 0){
            std::cout<<"error renaming"<<std::endl;
        }
        else{
            std::cout<<"success"<<std::endl;
        }

    }
    
    return 1;
}
}