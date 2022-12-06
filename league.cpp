#include "league.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <unordered_map>

#include "utils/date.h"

namespace League {
    
    League::League() {}
            

    void League::load_data() {

        std::ifstream raw_file("rawdata2.csv");
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
            string player_id = parsed_line["player_id"];
            if (!id2athlete_map.count(player_id)) {
                // create new player
            }
                
            istringstream iss {parsed_line["game_date"]};
            chrono::sys_days key;
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

            GameLog::GameLog log(fg, fga, fg3, fg3a, ft, fta, orb, drb, ast, stl, blk, tov, pf);
            
            id2athlete_map[player_id].addGameLog(key, log);

            // debug
            for (auto& [key, val]: parsed_line){
                std::cout << key << "\t\t" << val << std::endl;
            }

            break;
        }
        
        
        return;
    }


}
