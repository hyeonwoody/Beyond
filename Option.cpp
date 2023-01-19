#include "Beyond.h"
#include "Parse.h"

bool COption::add_flag_insert (SMapping* newMapping){
    memcpy (&this->flagList[flagListIndex], newMapping, sizeof(SMapping));
    flagListIndex++;
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
        newMapping->used = false;
        add_flag_insert (newMapping);
    }
    flagIndex++;
    return true;
}

bool COption::add_option_insert(SMapping* newMapping){
    memcpy (&this->optionList[optionListIndex], newMapping, sizeof(SMapping));
    optionListIndex++;
    return true; 
}

template <typename AssignTo>
bool COption::add_option(std::string optionName, AssignTo& variable, std::string optionDescription, bool essential){

    std::vector <std::string> pOptionName = spliter(optionName, ',');
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
}


/**
 * When you add option or flag, make sure you edit the OPTION_NUM & FLAG_NUM in Beyond.h
*/
void COption::Init(){
    
    optionList = (SMapping*) malloc (sizeof(SMapping)*OPTION_NUM);
    add_option ("-w,--workpath", optionGroup.workPath,  "O workstation path", true);
    add_option ("-c,--currentpath", optionGroup.currentPath, "O workplace path", true);
    add_option ("-f,--fileName", optionGroup.fileTag, "O file name allign [Title.Episode.Resolution.Reel.Codec.Extension] ex)Title.[`length of title`].Resolution.Reel", false);
    add_option ("-s,--subject", optionGroup.subject, "O job subject", false);
    

    flagList = (SMapping*) malloc (sizeof(SMapping)*FLAG_NUM);
    add_flag("-cp,--copy", flagGroup.copy, "F Copy from workstation to workplace");
    add_flag("-sb,--subtitle", flagGroup.subtitle, "F Subtitle file name"); 
    add_flag("-sy,--symbolic", flagGroup.symbolicLink, "F Create symbolic link on currentpath");
    add_flag("-ca,--cut", flagGroup.cut, "F video cut with Certain part, and duration");
}