class COption
{
public:
public:
    int m_argc;
    char** m_argv;
    
    
    SMapping* optionList; //string // index
    unsigned int optionListIndex;
    unsigned int optionIndex;
    
    SMapping* flagList;
    unsigned int flagListIndex;
    unsigned int flagIndex;

    SOptionGroup optionGroup;
    SFlagGroup flagGroup;
    

public:
    COption(){
        m_argc = 0;
        m_argv = nullptr;

        optionListIndex = 0;
        optionIndex = 0;
        
        flagListIndex = 0;
        flagIndex = 0;


        memset (&optionGroup, 0, sizeof(SOptionGroup));
        optionGroup.workPath = "W:";
        optionGroup.currentPath = "/zzz/workstation/Movie/Others";
        
        memset (&flagGroup, 0, sizeof(SFlagGroup));

    }
    ~COption(){
    }

    bool add_option_insert (SMapping* newMapping);

    template <typename AssignTo>
    bool add_option(std::string optionName, AssignTo& variable, std::string optionDescription = "", bool essential = false);

    
    bool add_flag_insert (SMapping* newMapping);
    
    bool add_flag(std::string flag_name, bool& variable, std::string flag_description="");

    void Init();
    void GetFeature(unsigned int feature);
};