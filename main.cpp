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
  /*
    Code snippet to initialize the color table with all values
  */
  std::vector<std::string> colorAttributes;
  setColorTableAttributes(colorAttributes);
  dropTable(actualConnection, "color", true);
  createTable(actualConnection, "color", colorAttributes);
  parseColorFile(actualConnection);
  std::string testAllEntriesColor = "SELECT * FROM COLOR;";
  std::ofstream outputStream("colorTableAfterParsing.txt");
  testColorQuery(actualConnection, testAllEntriesColor, outputStream);
  outputStream.close();

  /*
    Code snippet to initialize the state table with all values
  */
  std::vector<std::string> stateAttributes;
  setStateTableAttributes(stateAttributes);
  dropTable(actualConnection, "state", true);
  createTable(actualConnection, "state", stateAttributes);
  outputStream = std::ofstream("stateTableAfterParsing.txt");
  parseStateFile(actualConnection);
  std::string testAllEntriesState = "SELECT * FROM STATE;";
  testStateQuery(actualConnection, testAllEntriesState, outputStream);
  outputStream.close();

  /*
    Code snippet to initialize the team table with all values
  */
  std::vector<std::string> teamAttributes;
  setTeamTableAttributes(teamAttributes);
  dropTable(actualConnection, "team", true);
  createTable(actualConnection, "team", teamAttributes);
  parseTeamFile(actualConnection);
  outputStream = std::ofstream("teamTableAfterParsing.txt");
  std::string testAllEntriesTest = "SELECT * FROM TEAM;";
  testTeamQuery(actualConnection, testAllEntriesTest, outputStream);
  outputStream.close();

  /*
    Code snippet to initialize the player table with all values
  */
  std::vector<std::string> playerAttributes;
  setPlayerTableFields(playerAttributes);
  dropTable(actualConnection, "player", true);
  createTable(actualConnection, "player", playerAttributes);
  parsePlayerFile(actualConnection);
  outputStream = std::ofstream("playerTableAfterParsing.txt");
  std::string testAllEntriesPlayer = "SELECT * FROM PLAYER";
  testPlayerQuery(actualConnection, testAllEntriesPlayer, outputStream);
  outputStream.close();

  exercise(actualConnection);

  //Close database connection
  actualConnection->disconnect();

  return 0;
}
