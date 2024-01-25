#include <iostream>
#include <cstdio>    // fopen, fclose, fread, fwrite, BUFSIZ
#include <ctime>
#include <algorithm>

#include "Beyond.h"
/**
 * Proceed the jobs that is on pipe.
*/
int CMain::ProceedJob() {
    job.proceed(&option.optionGroup, &option.flagGroup);
    return 0;
}

/**
 * Sort Jobs by priority (index)
*/

    int COMP_BY_INDEX(SMapping* x, SMapping* y){
        return (x->index != y->index) && (x->index < y->index);
    }

int CMain::SortJob(){
    
    sort (this->job.jobList.begin(), this->job.jobList.end(), COMP_BY_INDEX);
    return 0;
}

/**
 * Put the jobs on the pipe if it is used.
*/
int CMain::ParseParam() {

    SMapping* pOption = this->option.optionList;
    for (int i = 0; i<OPTION_NUM; i++){
        if (pOption->used && (pOption->index > 1 )){ //ommit workpath, currentpath and subject
            job.pending(pOption);
        }
        pOption++;
    }

    SMapping* pFlag = this->option.flagList;
    for (int i = 0; i<FLAG_NUM; i++){
        if (pFlag->used){ //ommit workpath, currentpath and subject
            job.pending(pFlag);
        }
        pFlag++;
    }    
    
    free(this->option.optionList);
    this->option.optionList = nullptr;
    free(this->option.flagList);
    this->option.flagList = nullptr;
    return 0;
}

/**
 * Actuall Program start here.
 * Starting to plan what to do based on Param
*/
int CMain::Main(){

    int ret = 0;

    if (ret = ParseParam()< 0){
        return 3;
    }

    if (ret = SortJob() <0){
        return 4;
    }
    
    if (ret = ProceedJob() < 0){
        return 5;
    }


    return 0;
}


int GetFeature (unsigned int cotrol){
    bool a = 0;
    std::cout <<"option.list["<<std::endl;
    return 1;
}

/**
 * Get param and Compare it with flag and option if it is used or not.
*/
int GetParam(COption* option){
    std::cout<<"[GetParam] option->m_argc : "<<option->m_argc<<std::endl;
    for (int i=1; i<option->m_argc; i++){
        for (int j = 0; j<OPTION_NUM; j++){
            if (option->optionList[j].name.compare(option->m_argv[i]) == 0){
                option->optionList[j].used = true;
                i++;
                (*((std::string*)option->optionList[j].address)).assign(option->m_argv[i], strlen(option->m_argv[i]));
            }
        }
        for (int j = 0; j<FLAG_NUM; j++){
            if (option->flagList[j].name.compare(option->m_argv[i]) == 0){
                option->flagList[j].used = true;
                *((bool*)option->flagList[j].address) = true;
            }
        }
    }
    return 0;
}

void Usage(){
    printf ("Usage : Beyond -[Option Parameter] -[Flag Parameter]");
}

int main(int argc, char* argv[]) {
    if (argc == 1){
        Usage();
        return 1;
    }
    else {
        CMain app; //Actual Program
        COption* option = &app.option; //options in memory
        
        option->m_argc = argc;
        option->m_argv = argv;

        int ret = 0;


        // for (int i=0; i<argc; i++){
        //     option->m_argv[i] = (char *) malloc (strlen(argv[i])+1);
        //     memcpy (&option->m_argv[i], argv[i], strlen(argv[i])+1);
        // }

        option->Init(); //add option on memory 
        if (ret = GetParam (option) < 0){ 
            return 2;
        }


        app.Main();
        return 0;
    }
}