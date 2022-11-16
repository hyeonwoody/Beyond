#include "Parse.h"

std::string phraseParse (int start, int length, std::vector<std::string> vphrase){
    std::string phrase = "";
    for (int i = start; i<start + length; i++){
        phrase += vphrase[i] + " ";
    }
    phrase.pop_back();
    return phrase;
}

std::string tail(std::string source, unsigned short length){
    if (length >= source.size()){
        return source;
    }
    return source.substr(source.size() - length);
}

std::vector <std::string> spaceSpliter (std::string str, char delimeter){
    std::vector<std::string> split;
    std::string tmp;

    for (int i=0; !(str[i] == '\n' || str[i] == '\0'); i++){
        if (str[i] == delimeter){
            split.push_back(tmp);
            tmp.clear();
            continue;
        }
        if (str[i] == ' '){
            split.push_back(tmp);
            tmp.clear();
            continue;
        }

        tmp.push_back(str[i]);
        
    }
    split.push_back(tmp);
    tmp.clear();
    return split;
}

std::vector <std::string> spliter (std::string str, char delimeter){
    std::vector<std::string> split;
    std::string tmp;
    
    for (int i=0; !(str[i] == '\n' || str[i] == '\0'); i++){
        if (str[i] == delimeter){
            split.push_back(tmp);
            tmp.clear();
            continue;
        }

        tmp.push_back(str[i]);
        
    }
    split.push_back(tmp);
    tmp.clear();

    // int num = 1;

    // for (int i=0; !(str[i] == '\n'|| str[i] == '\0'); i++){
    //     if (str[i] == delimeter){
    //         num++;
    //     }
    // }

    // string* split = new string [num];
    // int splitIndex=0;
    // for (int  i=0; !(str[i] == '\n' || str[i] == '\0'); i++){
    //     if (str[i] == delimeter){
    //         splitIndex++;
    //         continue;
    //     }
    //     split[splitIndex].push_back(str[i]);
    // }
    
    
    return split;
}