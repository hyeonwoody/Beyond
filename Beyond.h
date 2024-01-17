
#include <iostream>
#include <string.h>

#include <vector>
#include <string>


#include "Option.h"
#include "Job.h"


#define OPTION_NUM 8
#define FLAG_NUM 8

#define DATABASE 0

#define WINDOWS 0


/**
 * Configurations
*/





class CMain
{
public:
    COption option;
    CJob job;
    
    
public:
    CMain(){
    }
    void Init();
    int Main();

    int ParseParam();
    int SortJob();
    int ProceedJob();
public:
private:
    
};

extern CMain app;