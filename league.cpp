#include "league.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <unordered_map>

#include "utils/date.h"

#define POSITION_THRESHOLD 25

namespace League {
    
    League::League() {}

    void League::showAthlete(std::string player_id) {
        
        if (!id2athlete_map.count(player_id)) {
            std::cout << player_id << "Not in the League" << std::endl;
            return;
        }

        id2athlete_map[player_id].showInfo();

        return;

    }
    
    int League::getAthleteNum() {

        return id2athlete_map.size();

    }

    void League::load_data() {

        std::ifstream raw_file("rawdata3.csv");
        std::string raw_line;

        // get_title
        std::vector<std::string> titles;
        getline(raw_file, raw_line);
        size_t pos = 0;
        int col = 0;
        std::string delimiter = ",";
        while ((pos = raw_line.find(delimiter)) != std::string::npos) {
                titles.push_back(raw_line.substr(0, pos));
                raw_line.erase(0, pos + delimiter.length()); 
                col++;
        }

        while(getline(raw_file, raw_line)){
            // parsing
            pos = 0;
            col = 0;
            std::unordered_map<std::string,std::string> parsed_line;
            while ((pos = raw_line.find(delimiter)) != std::string::npos) {
                parsed_line[titles[col]]  = raw_line.substr(0, pos);
                raw_line.erase(0, pos + delimiter.length());
                col++;
            }

            // create or add log to player
            std::string player_id = parsed_line["player_id"];
            if (!id2athlete_map.count(player_id)) {
                Athlete::Athlete newAthlete(player_id, parsed_line["player"]);
                id2athlete_map[player_id] = newAthlete;
                std::cout << "New Athlete\t" << parsed_line["player"] << std::endl;
            }

            // Add GameLog
            std::istringstream iss {parsed_line["game_date"]};
            std::chrono::sys_days key;
            iss >> date::parse("%F", key);
            
            int fg = std::stoi(parsed_line["fg"]);
            int fga = std::stoi(parsed_line["fga"]);
            int fg3 = std::stoi(parsed_line["fg3"]);
            int fg3a = std::stoi(parsed_line["fg3a"]);
            int ft = std::stoi(parsed_line["ft"]);
            int fta = std::stoi(parsed_line["fta"]);

            int orb = std::stoi(parsed_line["orb"]);
            int drb = std::stoi(parsed_line["drb"]);
            
            int ast = std::stoi(parsed_line["ast"]);
            int stl = std::stoi(parsed_line["stl"]);
            int blk = std::stoi(parsed_line["blk"]);
            int tov = std::stoi(parsed_line["tov"]);
            int pf = std::stoi(parsed_line["pf"]);

            // std::cout << "hi" << std::endl;

            GameLog::GameLog log(fg, fga, fg3, fg3a, ft, fta, orb, drb, ast, stl, blk, tov, pf);
            
            id2athlete_map[player_id].addGameLog(key, log);

            // Add Position
            try {
                if (parsed_line["PG%"] != "NA" && std::stoi(parsed_line["PG%"]) >= POSITION_THRESHOLD) {
                    id2athlete_map[player_id].addPosition("PG");
                }
                if (parsed_line["SG%"] != "NA" && std::stoi(parsed_line["SG%"]) >= POSITION_THRESHOLD) {
                    id2athlete_map[player_id].addPosition("SG");
                }
                if (parsed_line["PF%"] != "NA" && std::stoi(parsed_line["PF%"]) >= POSITION_THRESHOLD) {
                    id2athlete_map[player_id].addPosition("PF");
                }
                if (parsed_line["SF%"] != "NA" && std::stoi(parsed_line["SF%"]) >= POSITION_THRESHOLD) {
                    id2athlete_map[player_id].addPosition("SF");
                }
                if (parsed_line["C%"] != "NA" && std::stoi(parsed_line["C%"]) >= POSITION_THRESHOLD) {
                    id2athlete_map[player_id].addPosition("C");
                }
            } catch (...) {
                std::cout << parsed_line["PG%"] << std::endl;
                std::cout << parsed_line["SG%"] << std::endl;
                std::cout << parsed_line["PF%"] << std::endl;
                std::cout << parsed_line["SF%"] << std::endl;
                std::cout << parsed_line["C%"] << std::endl;
                throw 100;
            }
 
            // std::cout << "hi2" << std::endl;


            // debug
            // std::cout << "================================================" << std::endl;
            // for (auto& [key, val]: parsed_line){
            //     std::cout << key << "\t\t" << val << std::endl;
            // }
            // std::cout << "================================================" << std::endl;

        }

        return;
    }


}
