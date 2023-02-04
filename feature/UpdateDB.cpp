#include "../Beyond.h"
#include <mariadb/conncpp.hpp>

static bool initDB = false;



void showTable (std::unique_ptr<sql::Connection> &conn){
    try {
        // Create a new Statement
        std::unique_ptr<sql::Statement> stmnt(conn->createStatement());
        // Execute query
        sql::ResultSet *res = stmnt->executeQuery("select * from tasks");
        // Loop through and print results
        while (res->next()) {
            std::cout << "id = " << res->getInt(1);
            std::cout << ", description = " << res->getString(2);
            std::cout << ", completed = " << res->getBoolean(3) << "\n";
        }
    }
    catch(sql::SQLException& e){
      std::cerr << "Error selecting tasks: " << e.what() << std::endl;
   }
}


int CJob::updateDB (int index, bool isOption){
    
    sql::Driver* driver = sql::mariadb::get_driver_instance();

    // Configure Connection
    sql::SQLString url("jdbc:mariadb://200.40.8.10:3306/clips");
    sql::Properties properties({{"user", "map"}, {"password", "maroON$5^"}});

    // Establish Connection
    std::unique_ptr<sql::Connection> conn(driver->connect(url, properties));
    showTable(conn);
    //set type of job
    switch (index){
            case 2:
                if (isOption){

                }
                else {

                }
                break;
            case 3: //workpath
                if (isOption){ //OptionGroup
                    
                } 
                else { //flagGroup

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
    return 0;
}