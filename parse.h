
#include <iostream>
#include <string>
#include <vector>


std::vector <std::string> spliter (std::string str, char delimeter=','){
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