#include "league.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <chrono>
#include <unordered_map>

#include "utils/date.h"
#include "team.h"

#define POSITION_THRESHOLD 25

namespace League {

    League::League(std::string dateString) {
        // input string format: YYYY-MM-DD
        std::istringstream iss {dateString};
        std::chrono::sys_days tp;
        iss >> date::parse("%F", tp);
        currDate = tp;

        setCategory(std::unordered_set<std::string> {"fgpct", "ftpct", "3pm", "pts", "trb", "ast", "stl", "blk", "tov"});

        loadData();

    }

    League::League(std::chrono::sys_days currDate) : currDate(currDate) {
        setCategory(std::unordered_set<std::string> {"fgpct", "ftpct", "3pm", "pts", "trb", "ast", "stl", "blk", "tov"});
        loadData();
    }
    
    // League::League(std::chrono::sys_days currDate) : currDate(currDate) {}

    void League::showPlayer(std::string player_id) {
        
        if (!idToPlayer.count(player_id)) {
            std::cout << player_id << " not in the league" << std::endl;
            return;
        }

        idToPlayer[player_id].showInfo();

        return;

    }
    
    int League::getPlayerCnt() {
        return idToPlayer.size();

    }

    void League::addTeam(std::string teamName) {
        Team::Team newTeam(teamName);
        teamList.push_back(newTeam);
    }

    void League::showTeams() {
        for (int i = 0; i < teamList.size(); ++i) {
            std::cout << "Team No. " << i << ": " << teamList[i].getName() << std::endl;
        }
    }

    void League::showTeamPlayers(int teamNo) {
        
        std::cout << "\n==========ShowTeam:"<< teamNo <<"==========" << std::endl;
        std::cout << "-----idToTeamNumber-----" << std::endl;
        for (auto& [playerId, playerTeamNo]:idToTeamNumber) {
            if (playerTeamNo == teamNo){
                std::cout << playerId << "\t" << idToPlayer[playerId].getInfo()["playerName"] << std::endl;
            }
        }
        teamList[teamNo].getRoster(currDate).showRoster();
        std::cout << std::endl;
    }

    void League::teamAddPlayer(int teamNo, std::string playerId) {
        
        if (teamNo < 0 || teamNo >= teamList.size()) {
            std::cout << "Invalid team number\n";
            return;
        }

        if (!idToPlayer.count(playerId)) {
            std::cout << "Invalid player id\n";
            return;
        }

        if (idToTeamNumber[playerId] != -1) {
            std::cout << "Player " << playerId << " is not a free agent\n";
            return;
        }
        
        if (teamList[teamNo].addPlayer(currDate, &idToPlayer[playerId])) {
            idToTeamNumber[playerId] = teamNo;
        }
        
    }

    void League::teamDropPlayer(int teamNo, std::string playerId) {

        if (teamNo < 0 || teamNo >= teamList.size()) {
            std::cout << "Invalid team number\n";
            return;
        }

        if (!idToPlayer.count(playerId)) {
            std::cout << "Invalid player id\n";
            return;
        }

        if (idToTeamNumber[playerId] != teamNo) {
            std::cout << "Player " << playerId << " is not owned by the given team\n";
            return;
        }

        if (teamList[teamNo].dropPlayer(currDate, &idToPlayer[playerId])) {
            idToTeamNumber[playerId] = -1;
        }

    }

    void League::teamAddPlayerToWatchList(int teamNo, std::string playerId) {

        if (teamNo < 0 || teamNo >= teamList.size()) {
            std::cout << "Invalid team number\n";
            return;
        }

        if (!idToPlayer.count(playerId)) {
            std::cout << "Invalid player id\n";
            return;
        }

        teamList[teamNo].addPlayerToWatchList(&idToPlayer[playerId]);

    };

    void League::teamDropPlayerFromWatchList(int teamNo, std::string playerId) {

        if (teamNo < 0 || teamNo >= teamList.size()) {
            std::cout << "Invalid team number\n";
            return;
        }

        if (!idToPlayer.count(playerId)){
            std::cout << "Invalid player id\n";
            return;
        }

        teamList[teamNo].dropPlayerFromWatchList(&idToPlayer[playerId]);

    };

    bool League::teamPlacePlayer(int teamNo, std::string playerId, std::string position, bool force = true) {
        if (idToTeamNumber[playerId] != -1 && idToTeamNumber[playerId] != teamNo) {
            return false;
        }
        bool res = teamList[teamNo].placePlayerToDate(currDate, &idToPlayer[playerId], position, force);
        if (res) {
            idToTeamNumber[playerId] = teamNo;
        }
        return res;
    }

    bool League::teamSwapPlayerPlacement(int teamNo, std::string playerReplacerId, std::string playerReplaceeId, bool force = true) {
        if (idToTeamNumber[playerReplacerId] != -1 && idToTeamNumber[playerReplacerId] != teamNo) {
            return false;
        }
        if (idToTeamNumber[playerReplaceeId] != teamNo) {
            return false;
        }
        bool res = teamList[teamNo].swapPlayerPlacementToDate(currDate, &idToPlayer[playerReplacerId], &idToPlayer[playerReplaceeId], force);
        
        if (res) {
            idToTeamNumber[playerReplacerId] = teamNo;
        }
        return res;
    }

    bool League::teamSetPlayerPlacement(int teamNo, std::unordered_map<std::string, std::unordered_set<std::string>> newPlacementId) {
        for (auto& [_, placement] : newPlacementId) {
            for (auto& playerId : placement) {
                if (idToTeamNumber[playerId] != -1 && idToTeamNumber[playerId] != teamNo) {
                    return false;
                }
            }
        }
        std::unordered_map<std::string, std::unordered_set<Player::Player*>> newPlacement;
        for (auto& [pos, playerIdSet] : newPlacementId) {
            for (auto pId: playerIdSet) {
                newPlacement[pos].insert(&idToPlayer[pId]);
            }
        }
        for (auto& [_, placement] : newPlacementId) {
            for (auto& playerId : placement) {
                idToTeamNumber[playerId] = teamNo;
            }
        }
        return teamList[teamNo].setPlayerPlacementToDate(currDate, newPlacement);
    }

    void League::setCategory(std::unordered_set<std::string> customCategories) {
        
        for (auto& cat : categoryKey) {
            categories[cat] = false;
        }

        for (auto& cat : customCategories) {
            if (categories.count(cat)) {
                categories[cat] = true;
            } else {
                std::cout << "Category " << cat << " is not allowed." << std::endl;
            }
        }
    }

    void League::loadData() {

        std::ifstream raw_file("rawdata_deduplicate.csv");
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

        int cnt = 0;

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

            // select season
            if (parsed_line["season"] != "2023") {
                continue;
            }

            // ignore if not played
            if (parsed_line["did_not_play"] == "1"){
                continue;
            }

            // create or add log to player
            std::string player_id = parsed_line["player_id"];
            if (!idToPlayer.count(player_id)) {
                Player::Player newPlayer(player_id, parsed_line["player"]);
                idToPlayer[player_id] = newPlayer;
                idToTeamNumber[player_id] = -1;
                // std::cout << "New Player\t" << parsed_line["player"] << "\t" << parsed_line["player_id"] << std::endl;
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

            GameLog::GameLog log(fg, fga, fg3, fg3a, ft, fta, orb, drb, ast, stl, blk, tov, pf);
            
            idToPlayer[player_id].addGameLog(key, log);

            // Add Position
            try {
                if (parsed_line["PG%"] != "NA" && std::stoi(parsed_line["PG%"]) >= POSITION_THRESHOLD) {
                    idToPlayer[player_id].addPosition("PG");
                }
                if (parsed_line["SG%"] != "NA" && std::stoi(parsed_line["SG%"]) >= POSITION_THRESHOLD) {
                    idToPlayer[player_id].addPosition("SG");
                }
                if (parsed_line["PF%"] != "NA" && std::stoi(parsed_line["PF%"]) >= POSITION_THRESHOLD) {
                    idToPlayer[player_id].addPosition("PF");
                }
                if (parsed_line["SF%"] != "NA" && std::stoi(parsed_line["SF%"]) >= POSITION_THRESHOLD) {
                    idToPlayer[player_id].addPosition("SF");
                }
                if (parsed_line["C%"] != "NA" && std::stoi(parsed_line["C%"]) >= POSITION_THRESHOLD) {
                    idToPlayer[player_id].addPosition("C");
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

            cnt++;
        }
        

        int sum = 0;
        for(auto& [pid, ath] : idToPlayer) {
            sum += ath.getGameLogSize();
        }

        std::cout << "raw cnt:" << cnt << "\ngameLog cnt:" << sum << std::endl;

        for(auto & [_, p] : idToPlayer) {
            p.updateAvgStats();
        }


        return;
    }

}
