#include "UpdateDB.h"
#include <mariadb/conncpp.hpp>
#include <vector>




static bool initDB = false;

void CUpdateDB::SymbolicLink (std::unique_ptr<sql::Connection> &conn, CJob::CSubJob *pSubJob){
    try {
        // Create a new PreparedStatement
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO symbolicLink (title, year) values (?, ?)"));
        stmnt->setString(1, pSubJob->fileName[0]);
        stmnt->setInt(2, atoi(pSubJob->fileName[2].c_str()));
        // Bind values to SQL statement
        // Bind variables to prepared statement parameters
        // Note that the index starts at 1--not 0
        stmnt->executeQuery();
        // Execute query
        
    }
    catch(sql::SQLException& e){
      std::cerr << "Error inserting new task: " << e.what() <<"THIS"<< std::endl;
   }
}


void showSymbolicLink (std::unique_ptr<sql::Connection> &conn){
    try {
        // Create a new Statement
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // Execute query
        sql::ResultSet *res = stmnt->executeQuery("select * from symbolicLink");
        // Loop through and print results
        int a = 0;
        while (res->next()) {
            std::cout << "title = " <<res->getString (1)<<std::endl;
            std::cout << "koreanTitle = " <<res->getString (2)<<std::endl;
            std::cout << "year = " << res->getInt(2)<<std::endl;

            std::cout << a++ <<std::endl;
        }   
    }
    catch(sql::SQLException& e){
      std::cerr << "Error selecting tasks: " << e.what() << std::endl;
   }
}

void CUpdateDB::VideoCut (std::unique_ptr<sql::Connection> &conn, std::vector<CJob::SClip *> clipList){
    try {
        // Create a new PreparedStatement
        std::unique_ptr<sql::PreparedStatement> stmnt(conn->prepareStatement("INSERT INTO clips (title, srcTitle, startTime, endTime) values (?, ?, ?, ?)"));

        // Bind values to SQL statement
        // Bind variables to prepared statement parameters
        // Note that the index starts at 1--not 0

        for (int i=0; i<clipList.size(); i++){
            stmnt->setString(1, clipList[i]->name);
            stmnt->setString(2, clipList[i]->source);
            stmnt->setInt64 (3, clipList[i]->startTime);
            stmnt->setInt64 (4, clipList[i]->endTime);
            stmnt->executeQuery();
        }
        // Execute query
        
    }
    catch(sql::SQLException& e){
      std::cerr << "Error inserting new task: " << e.what() <<"THIS"<< std::endl;
   }
}

void showVideoCut (std::unique_ptr<sql::Connection> &conn){
    try {
        // Create a new Statement
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // Execute query
        sql::ResultSet *res = stmnt->executeQuery("select * from clips");
        // Loop through and print results
        int a = 0;
        while (res->next()) {
            // std::cout << "title = " <<res->getString (1)<<std::endl;
            // std::cout << "srcTitle = " << res->getString(2)<<std::endl;
            // std::cout << "startTime = " << res->getInt(3)<<std::endl;
            // std::cout << "endTime = " << res->getInt(4)<<std::endl;
            // std::cout << "tag = " << res->getString(5)<<std::endl;
            // std::cout << a++ <<std::endl;
        }   
    }
    catch(sql::SQLException& e){
      std::cerr << "Error selecting tasks: " << e.what() << std::endl;
   }
}


int CUpdateDB::Update (int index, bool isOption){
    
    sql::Driver* driver = sql::mariadb::get_driver_instance();

    // Configure Connection
    sql::SQLString url("jdbc:mariadb://안알랴줌/BEYOND");
    sql::Properties properties({{"user", "db"}, {"password", "이거도안알랴줌"}});
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    // Establish Connection
    

    //set type of job
    switch (index){
            case 2:
                if (isOption){

                }
                else {
                    if (1){
                        showSymbolicLink (conn);
                        //this->SymbolicLink (conn, this->pSubJob);
                        showSymbolicLink(conn);
                    }  
                }
                break;
            case 3: //workpath
                if (isOption){ //OptionGroup
                    
                } 
                else { //flagGroup
                    if (1){
                        showVideoCut (conn);
                        //this->VideoCut (conn, this->pVideoCut->clipList);
                        showVideoCut(conn);
                    }  
                }
                break;
            case 4: //
                if (isOption){ //OptionGroup
                } 
                else {

                }
                break;
            default:
                break;
    }
    conn->close();
    return 0;
}