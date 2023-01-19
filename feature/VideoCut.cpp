
#include <iostream>
#include <fstream>
#include <codecvt>
#include <locale>
#include <string>

#include <sys/stat.h> // mkdir

#include "../Beyond.h"
#include "../Parse.h"

std::string utf16_to_utf8(std::u16string const& str){
    std::wstring_convert<std::codecvt_utf8_utf16<char16_t, 0x10ffff, std::codecvt_mode::little_endian>, char16_t> cnv;
    std::string utf8 = cnv.to_bytes(str);
    if (cnv.converted() < str.size()){

    }
    return utf8;
}

CJob::CVideoCut::STime* CJob::CVideoCut::parsePbf(std::string path, std::string file){

    std::ifstream openFile(path+file);
    int numLine = 0;
    std::vector<std::string> number = {};
    std::vector<std::string> name = {};
    std::string line;
    std::string tmp;

    CJob::CVideoCut::STime* pTime;

    openFile.seekg(0, std::ios::end);
    size_t size = (size_t) openFile.tellg();

    //skip Bom
    openFile.seekg(2, std::ios::beg);
    size -= 2;

    std::u16string u16((size / 2) + 1, '\0');
    openFile.read((char*)&u16[0], size);
    std::string what = utf16_to_utf8(u16);
    std::cout<<"이거는 : "<<what<<std::endl;

    openFile.close();
    what = what.substr(what.find('\n',1));
    int equal = what.find ('=');
    int star = what.find ('*');
    while (equal != -1 && star != -1){
            line = what.substr(equal+1, star - equal - 1);
            number.push_back(line);
            tmp = what.substr (star+1, what.find('*', star+1)- (star+1));
            name.push_back(tmp);
        what = what.substr(what.find('\n',1));
        equal = what.find('=');
        star = what.find('*');
        
        
        numLine++;
    }
    pTime = (CJob::CVideoCut::STime*)malloc(sizeof(CJob::CVideoCut::STime)*numLine);
    memset(pTime, 0, sizeof(CJob::CVideoCut::STime)*numLine);
    for (int i=0; i<numLine; i++){
        pTime[i].second = (stoi(number[i]) / 1000) % 60;
        pTime[i].minute = (stoi(number[i]) / 1000) / 60;
        while (pTime[i].minute >= 60){
            pTime[i].minute -= 60;
            pTime[i].hour = +1;
        }
        pTime[i].name = name[i];
        pTime[i].value = true;
    }
    return pTime;
}
bool CJob::CVideoCut::proceed (CJob* pJob, SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    
    std::string path = optionGroup->workPath + "/";
    std::string folderName = "temporary";
    std::string currentTag = optionGroup->fileTag;

    std::vector <std::string> pbfList;
    std::vector <std::string> fileList;

    CJob::CSubJob* pSubJob = pJob->pSubJob;
    std::string command = "";


    if (pJob->pFileName != nullptr){
        pbfList = pSubJob->pbfList;
    }
    else {
        pSubJob->getDirectory(path);
        pbfList = pSubJob->pbfList;
        fileList = pSubJob->fileList;
    }



    const unsigned char optionSize = 5;
    const std::string option[optionSize] = {"-ss", "-to", "-i",  "-c copy", "-y"};
    mkdir((path+folderName).c_str(),0777);
    for (int i=0; i<pbfList.size(); i++){
        // STime* pTime = parsePbf(path+pbfList[i]);
        STime* pTime= parsePbf(path, pbfList[i]);
        std::cout<<pTime->hour<<"시"<<pTime->minute<<"분"<<pTime->second<<"초"<<std::endl;
        int j =0;
        while (pTime[j].value == true){
            j++;
        }
        if (j%2 != 0){
            std::cout <<"Chapters are not even number"<<std::endl;
            return false;
        }
        else {
            
            for (int k = 0; k<j; k++){
                command = "/usr/bin/ffmpeg ";
                for (int l=0; l<optionSize; l++){
                    switch (l){
                        case 0: // -ss
                            command += option[l] + " ";
                            command += std::to_string(pTime[k].hour)+":";
                            command += std::to_string(pTime[k].minute)+":";
                            command += std::to_string(pTime[k].second);
                            command += " ";
                            break;
                        case 1: // -to
                            k++;
                            command += option[l] + " ";
                            command += std::to_string(pTime[k].hour)+":";
                            command += std::to_string(pTime[k].minute)+":";
                            command += std::to_string(pTime[k].second);
                            command += " ";
                            break;
                        case 2: // -i
                            command += option[l] + " ";
                            command += "\""+path + fileList[i]+"\"";
                            command += " ";
                            break;
                        
                        case 3: // -c copy
                            command += option[l] + " ";
                            command += "\""+path + folderName;
                            command += "/"+pTime[k-1].name+".mp4\"";
                            command += " ";
                            break;
                        case 4: // -y
                            command += option[l];
                     }
                }
                system (command.c_str());
                //system (("cd "+path+" && "+command).data());
            }
        }
        
        
    }
    return true;
}