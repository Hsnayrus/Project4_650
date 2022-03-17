#include "query_funcs.h"

#include <fstream>

#define PlayerTable \
  "PLAYER(PLAYER_ID,TEAM_ID,UNIFORM_NUM,FIRST_NAME,LAST_NAME,MPG,PPG,RPG,APG,SPG,BPG)"

#define TeamTable "TEAM(TEAM_ID,NAME,STATE_ID,COLOR_ID,WINS,LOSSES)"

#define StateTable "STATE(NAME)"

#define ColorTable "COLOR(NAME)"

void displayInterval() {
  std::cout << "^*^*^*^*^*^*^*^*^*^*^*^*\n";
}

pqxx::result basicExecuteQuery(pqxx::connection * connectionToDatabase,
                               std::string queryToExec,
                               bool displayMessage) {
  pqxx::work newWork(*connectionToDatabase);
  pqxx::result newResult = newWork.exec(queryToExec);
  newWork.commit();
  if (displayMessage) {
    displayInterval();
    std::cout << newResult.query() << " was executed successfully\n";
  }
  return newResult;
}

void dropTable(pqxx::connection * connectionToDatabase,
               std::string tableName,
               bool cascade) {
  std::transform(tableName.begin(), tableName.end(), tableName.begin(), ::toupper);
  std::string basicQuery =
      "DROP TABLE IF EXISTS " + tableName + (cascade ? " CASCADE;" : ";");
  pqxx::result newResult = basicExecuteQuery(connectionToDatabase, basicQuery, true);
  displayInterval();
}

void createTable(pqxx::connection * connectionToDatabase,
                 std::string tableName,
                 std::vector<std::string> attributes) {
  std::transform(tableName.begin(), tableName.end(), tableName.begin(), ::toupper);
  std::string basicQuery = "CREATE TABLE " + tableName + "(\n";
  for (std::vector<std::string>::iterator it = attributes.begin(); it != attributes.end();
       ++it) {
    basicQuery.append(*it);
    if (it != attributes.end() - 1) {
      basicQuery.append(",\n");
    }
  }
  basicQuery.append(");");
  pqxx::result newResult = basicExecuteQuery(connectionToDatabase, basicQuery, true);
  displayInterval();
  std::cout << tableName << " was successfully created\n";
}

void setPlayerTableFields(std::vector<std::string> & playerAttributes) {
  playerAttributes.push_back("FNAME VARCHAR(15) NOT NULL");
  playerAttributes.push_back("SSN CHAR NOT NULL");
}

void add_player(pqxx::connection * C,
                int team_id,
                int jersey_num,
                std::string first_name,
                std::string last_name,
                int mpg,
                int ppg,
                int rpg,
                int apg,
                double spg,
                double bpg) {
}

void add_team(pqxx::connection * C,
              std::string name,
              int state_id,
              int color_id,
              int wins,
              int losses) {
}

void setStateTableAttributes(std::vector<std::string> & stateAttributes) {
  stateAttributes.push_back("STATE_ID SERIAL PRIMARY KEY");
  stateAttributes.push_back("NAME VARCHAR(5) NOT NULL");
}

void parseStateFile(pqxx::connection * connectionToDatabase) {
  std::ifstream stateFile("state.txt");
  std::string line;
  int stateID;
  std::string name;
  while (std::getline(stateFile, line)) {
    std::stringstream newStream(line);
    newStream >> stateID >> name;
    add_state(connectionToDatabase, name);
  }
}

void testStateQuery(pqxx::connection * connectionToDatabase,
                    std::string query,
                    std::ostream & outputStream) {
  pqxx::result newResult = basicExecuteQuery(connectionToDatabase, query, false);
  displayInterval();
  for (auto r : newResult) {
    outputStream << r["STATE_ID"].as<int>() << " " << r["NAME"].c_str() << std::endl;
  }
}

void add_state(pqxx::connection * C, std::string name) {
  std::string insertString = std::string("INSERT INTO ") + StateTable +
                             std::string(" VALUES(") + C->quote(name) + ");";
  basicExecuteQuery(C, insertString, false);
}

void setColorTableAttributes(std::vector<std::string> & colorAttributes) {
  colorAttributes.push_back("COLOR_ID SERIAL PRIMARY KEY");
  colorAttributes.push_back("NAME VARCHAR(50) NOT NULL");
}

void add_color(pqxx::connection * C, std::string name) {
  std::string insertString = std::string("INSERT INTO ") + ColorTable +
                             std::string(" VALUES(") + C->quote(name) + ");";
  //True for testing purposes
  basicExecuteQuery(C, insertString, false);
}

void parseColorFile(pqxx::connection * connectionToDatabase) {
  std::ifstream colorFile("color.txt");
  std::string line;
  int colorID;
  std::string name;
  while (std::getline(colorFile, line)) {
    std::stringstream newStream(line);
    newStream >> colorID >> name;
    add_color(connectionToDatabase, name);
  }
}

void testColorQuery(pqxx::connection * connectionToDatabase,
                    std::string query,
                    std::ostream & outputStream) {
  pqxx::result newResult = basicExecuteQuery(connectionToDatabase, query, false);
  displayInterval();
  for (auto r : newResult) {
    outputStream << r["COLOR_ID"].as<int>() << " " << r["NAME"].c_str() << std::endl;
  }
  //   outputStream.close();
}

void query1(pqxx::connection * C,
            int use_mpg,
            int min_mpg,
            int max_mpg,
            int use_ppg,
            int min_ppg,
            int max_ppg,
            int use_rpg,
            int min_rpg,
            int max_rpg,
            int use_apg,
            int min_apg,
            int max_apg,
            int use_spg,
            double min_spg,
            double max_spg,
            int use_bpg,
            double min_bpg,
            double max_bpg) {
}

void query2(pqxx::connection * C, std::string team_color) {
}

void query3(pqxx::connection * C, std::string team_name) {
}

void query4(pqxx::connection * C, std::string team_state, std::string team_color) {
}

void query5(pqxx::connection * C, int num_wins) {
}
