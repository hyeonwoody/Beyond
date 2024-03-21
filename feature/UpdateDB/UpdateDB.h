
#include "Job.h"

#if DB

#include <mariadb/conncpp.hpp>
#include <vector>

class CUpdateDB{

    void SymbolicLink (std::unique_ptr<sql::Connection> &conn, CJob::CSubJob *pSubJob);
    void VideoCut (std::unique_ptr<sql::Connection> &conn, std::vector<CJob::SClip *> clipList);
    int Update (int index, bool isOption);
};
#endif