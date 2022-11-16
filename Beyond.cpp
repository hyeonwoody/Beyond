#include <iostream>
#include <cstdio>    // fopen, fclose, fread, fwrite, BUFSIZ
#include <ctime>

#include "Beyond.h"

int CMain::ProceedJob() {
    SOptionGroup* pOptionGroup = &option.optionGroup;
    job.proceed(pOptionGroup);
    return 0;
}

int CMain::ParseParam() {
    SMapping* pOption = this->option.optionList;

    for (int i = 0; i<OPTION_NUM; i++){
        if (pOption->used && (pOption->index > 2 )){ //ommit workpath, currentpath and subject
            job.add(pOption);
        }
        pOption++;
    }
    return 0;
}


int CMain::Main(){

    int ret = 0;

    if (ret = ParseParam()< 0){
        return 3;
    }

    
    if (ret = ProceedJob() < 0){
        return 4;
    }


    return 0;
}


int GetFeature (unsigned int cotrol){
    bool a = 0;
    std::cout <<"option.list["<<std::endl;
    return 1;
}

int GetParam(COption* option){\
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
                *((bool*)option->flagList[j].address) = true;
            }
        }
    }
    //cout<<"m_copy"<<boolalpha<<option->flagGroup.copy<<endl;
    return 0;
}

void Usage(){
    printf ("ff");
}

int main(int argc, char* argv[]) {
    if (argc == 1){
        Usage();
        return 1;
    }
    else {
        CMain app;
        COption* option = &app.option;
        
        option->m_argc = argc;
        option->m_argv = argv;

        int ret = 0;


        // for (int i=0; i<argc; i++){
        //     option->m_argv[i] = (char *) malloc (strlen(argv[i])+1);
        //     memcpy (&option->m_argv[i], argv[i], strlen(argv[i])+1);
        // }

        option->Init(); //add option 
        if (ret = GetParam (option) < 0){
            return 2;
        }



        return app.Main();
    }
}