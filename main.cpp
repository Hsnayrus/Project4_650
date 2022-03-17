#include <pqxx/pqxx>

#include "exerciser.h"
#include "query_funcs.h"

int main(int argc, char * argv[]) {
  //Allocate & initialize a Postgres connection object
  pqxx::connection * actualConnection;

  try {
    //Establish a connection to the database
    //Parameters: database name, user name, user password
    actualConnection =
        new pqxx::connection("dbname=ACC_BBALL user=postgres password=passw0rd");
    if (actualConnection->is_open()) {
      std::cout << "Opened database successfully: " << actualConnection->dbname() << endl;
    }
    else {
      std::cout << "Can't open database" << endl;
      return 1;
    }
  }
  catch (const std::exception & e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }

  //TODO: create PLAYER, TEAM, STATE, and COLOR tables in the ACC_BBALL database
  //      load each table with rows from the provided source txt files

  // exercise(actualConnection);

  /*
    Code snippet to initialize the color table with all values
  */
  std::vector<std::string> colorAttributes;
  setColorTableAttributes(colorAttributes);
  dropTable(actualConnection, "color", true);
  createTable(actualConnection, "color", colorAttributes);
  parseColorFile(actualConnection);
  testColorTable(actualConnection, "color");

  // dropTable(actualConnection, "color", true);

  //Close database connection
  actualConnection->disconnect();

  return 0;
}
