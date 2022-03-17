#include <algorithm>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <pqxx/pqxx>
#include <string>

#ifndef _QUERY_FUNCS_
#define _QUERY_FUNCS_

void displayInterval();

pqxx::result basicExecuteQuery(pqxx::connection * connectionToDatabase,
                               std::string queryToExec,
                               bool displayMessage);

void dropTable(pqxx::connection * connectionToDatabase,
               std::string tableName,
               bool cascade);

void createTable(pqxx::connection * connectionToDatabase,
                 std::string tableName,
                 std::vector<std::string> attributes);

//Player Table functions
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
                double bpg);
void setPlayerTableFields(std::vector<std::string> & playerAttributes);
void parsePlayerFile(pqxx::connection * connectionToDatabase);
void testPlayerQuery(pqxx::connection * connectionToDatabase,
                     std::string query,
                     std::ostream & outputStream);

//Team Table functions
void add_team(pqxx::connection * C,
              std::string name,
              int state_id,
              int color_id,
              int wins,
              int losses);
void parseTeamFile(pqxx::connection * connectionToDatabase);
void setTeamTableAttributes(std::vector<std::string> & teamAttributes);
void testTeamQuery(pqxx::connection * connectionToDatabase,
                   std::string query,
                   std::ostream & outputStream);

//State Table functions
void add_state(pqxx::connection * C, std::string name);
void parseStateFile(pqxx::connection * connectionToDataBase);
void setStateTableAttributes(std::vector<std::string> & teamAttributes);
void testStateQuery(pqxx::connection * connectionToDatabase,
                    std::string query,
                    std::ostream & outputStream);

//Color functions
void add_color(pqxx::connection * C, std::string name);
void parseColorFile(pqxx::connection * connectionToDatabase);
void setColorTableAttributes(std::vector<std::string> & colorAttributes);
void testColorQuery(pqxx::connection * connectionToDatabase,
                    std::string query,
                    std::ostream & outputStream);

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
            double max_bpg);

void query2(pqxx::connection * C, std::string team_color);

void query3(pqxx::connection * C, std::string team_name);

void query4(pqxx::connection * C, std::string team_state, std::string team_color);

void query5(pqxx::connection * C, int num_wins);

#endif  //_QUERY_FUNCS_
