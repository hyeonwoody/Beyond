#include "./feature/VideoCut/VideoCut.h"


#include "./feature/FileName/FileName.h"
#include "./feature/SymbolicLink/SymbolicLink.h"

#include "./feature/UpdateDB/UpdateDB.h"
#include "./feature/FeatureFactory.cpp"

#define TEST 0

CJob:: CJob(){
    pSubJob = new CSubJob();
}

CJob::~CJob(){
    if (pSubJob){
        delete (pSubJob);
        pSubJob = nullptr;
    }

}

bool CJob::proceed(SOptionGroup* optionGroup, SFlagGroup* flagGroup){
    SMapping *currentJob;
    int* ptrJob = NULL;
    for (int i=0; i<jobList.size(); i++){
        currentJob = jobList[i];
        bool isOption = false;
        
        #if TEST 
        this->pTest = new CJob::CTest(); 
        delete this->pTest;
        this->pTest = nullptr;
        #endif

        std::cout << "On Process New Job : "<<currentJob->description<<std::endl;
        unsigned int index = currentJob->index;
        CJob* pJob = nullptr;
        CFeature* pFeature = nullptr;
        switch (index){
            case 2:
                if (currentJob->description[0] == 'O'){
                    //pJob = new CFileName();
                    isOption = true;
                    FeatureFactory::RegisterFeature ("FileName", CFileName::Create);
                    pFeature = FeatureFactory::CreateFeature("FileName");
                }
                else {
                    FeatureFactory::RegisterFeature ("SymbolicLink", CSymbolicLink::Create);
                    //pJob = new CSymbolicLink();
                    pFeature = FeatureFactory::CreateFeature("SymbolicLink");
                }
                break;
            case 3: //workpath
                if (currentJob->description[0] == 'O'){ //OptionGroup
                    isOption = true;
                } 
                else { //flagGroup
                    FeatureFactory::RegisterFeature ("VideoCut", CVideoCut::Create);
                    pFeature = FeatureFactory::CreateFeature ("VideoCut");
                    //pFeature = new CVideoCut();
                    
                }
                break;
            case 4: //
                if (currentJob->description[0] == 'O'){ //OptionGroup
                    isOption = true;
                } 
                else {
                    
                }
                break;
            default:
                break;
        }
        #if DATABASE 
        update
        #endif
        if (pJob){
            //pJob->proceed(this, optionGroup, flagGroup);
            delete (pJob);
        }
        if (pFeature){
            pFeature->proceed(this, optionGroup, flagGroup);
            delete (pFeature);
        }
        
        std::cout << "Completed New Job : "<<currentJob->description<<std::endl;
    }
    return true;
}

bool CJob::pending(SMapping* job){
    jobList.push_back(job);
    return true;
}