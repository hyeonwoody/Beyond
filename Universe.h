struct SOptionGroup{
    std::string workPath;
    std::string currentPath;
    std::string jobPath;
    std::string subject;
    std::string fileTag;
};

struct SFlagGroup{
    bool copy;
    bool subtitle;
    bool symbolicLink;
    bool cut;
};

struct SMapping{
    std::string name;
    void* address;
    unsigned int index;
    bool isInt;
    bool essential;
    bool used;
    std::string description;  
};
