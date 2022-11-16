#include "Beyond.h"
#include "Parse.h"

bool COption::add_flag_insert (SMapping* newMapping){
    // SMapping* pFlagList = flagList + flagIndex;
    // pFlagList = (SMapping *) malloc (sizeof(SMapping));
    // memcpy (&pFlagList, newMapping, sizeof(SMapping));
    // flagIndex++;
    
    memcpy (&this->flagList[flagIndex], newMapping, sizeof(SMapping));

    return true;
}

bool COption::add_flag(std::string flagName, bool& variable, std::string flagDescription){
    std::vector <std::string> pFlagName = spliter (flagName, ',');
    for (int i=0; i<pFlagName.size(); i++){
         SMapping *newMapping = new SMapping ();
        newMapping->name = pFlagName[i]; 
        newMapping->index = flagIndex;
        newMapping->address = &variable;
        newMapping->description = flagDescription;
        newMapping->essential = false;
        add_flag_insert (newMapping);
    }
    flagIndex++;
    return true;
}

bool COption::add_option_insert(SMapping* newMapping){
    memcpy (&this->optionList[optionListIndex], newMapping, sizeof(SMapping));
    optionListIndex++;
    // SMapping* pOptionList = optionList + optionIndex;
    // pOptionList = (SMapping *) malloc (sizeof(SMapping));
    // memcpy (&pOptionList, newMapping, sizeof(SMapping));

    return true; 
}

template <typename AssignTo>
bool COption::add_option(std::string optionName, AssignTo& variable, std::string optionDescription, bool essential){

    std::vector <std::string> pOptionName = spliter(optionName, ',');
    //void* address = &variable;
    for (int i=0; i< pOptionName.size(); i++){
        SMapping *newMapping = new SMapping ();
        newMapping->name = pOptionName[i]; 
        newMapping->index = optionIndex;
        newMapping->address = &variable;
        newMapping->description = optionDescription;
        newMapping->essential = essential;
        newMapping->used = false;
        
        add_option_insert(newMapping);
    }
    optionIndex++;
    return true;
    //return add_option_insert (spliter(option_name), value, option_description, bool essential);
}

void COption::Init(){
    add_option ("-w,--workpath", optionGroup.workPath,  "workstation path", true);
    add_option ("-c,--currentpath", optionGroup.currentPath, "workplace path", true);
    add_option ("-s,--subject", optionGroup.subject, "job subject", false);
    add_option ("-f,--fileTag", optionGroup.fileTag, "1: file name allign [Title.Episode.Resolution.Reel.Codec.Extension]", false);

    add_flag("-cp,--copy,", flagGroup.copy, "Copy from workstation to workplace");
    add_flag("-sb,--subtitle", flagGroup.subtitle, "subtitle file name");

}