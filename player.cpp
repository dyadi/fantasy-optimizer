#include <iostream>

#include "player.h"
#include "utils/date.h"

using date::operator<<;

namespace Player {
    
    Player::Player() {}

    Player::Player(std::string playerId, std::string playerName) : playerId(playerId), playerName(playerName) {}

    void Player::showInfo(){
        std::cout << "========================" << "\n";
        std::cout << "Palyer_ID\t" << playerId << "\n";
        std::cout << "Palyer_Name\t" << playerName << "\n";
        std::cout << "Palyer_Position\t";
        for (auto pos: positions){
            std::cout << pos << " ";
        }
        std::cout << "\n";

        std::cout << "GameLog Length\t" << dateToGameLog.size() << "\n";

        std::cout << std::endl;

    }

    std::unordered_map<std::string, std::string> Player::getInfo(){
        return std::unordered_map<std::string, std::string> {{"playerId", playerId}, {"playerName", playerName}};
    }

    void Player::addPosition(std::string pos) {
        positions.insert(pos);
    }

    std::unordered_set<std::string> Player::getPositions () {
        return positions;
    }

    void Player::addGameLog(std::chrono::sys_days date, GameLog::GameLog gamelog) {

        // if(player_id == "bridgmi01" && dateToGameLog.count(date)){
        //     std::cout << "already in" << player_id << std::endl;
        //     dateToGameLog[date].showGameLog();
        //     gamelog.showGameLog();
        //     std::cout << player_id << " game played " << dateToGameLog.size() << std::endl;
        //     throw 50;
        // }

        dateToGameLog[date] = gamelog;
        // if (player_id == "bridgmi01") {
        //     std::cout << player_id << " game played " << dateToGameLog.size() << std::endl;
        // }
        
    }

    GameLog::GameLog Player::getGameLog(std::chrono::sys_days date) {
        if (!dateToGameLog.count(date)) {
            throw 1;
        }
        return dateToGameLog[date];
    }

    int Player::getGameLogSize(){
        return dateToGameLog.size();
    }

    void Player::updateAvgStats(){

        int gameCnt = getGameLogSize();

        GameLog::GameLog sumGameLog;
        for (auto& [_, gl] : dateToGameLog) {
            sumGameLog += gl;
        }

        avgStats = sumGameLog.getStats();

        for (auto& [cat, val] : avgStats) {
            if (cat == "fgpct" || cat == "ftpct" || cat == "3ppct" || cat == "astovr") {
                continue;
            }
            avgStats[cat] /= gameCnt;
        }

        avgStats["score"] = avgStats["pts"] + 3*avgStats["blk"] + 2*avgStats["stl"] + 2*avgStats["ast"] +
                            1.5*avgStats["orb"] + avgStats["drb"] * 1.5*avgStats["trb"] - 2*avgStats["tov"] + 
                            avgStats["dd"] + avgStats["fgm"] - 1.5*(1/(avgStats["fgpct"]/avgStats["fgm"]-avgStats["fgm"])) - 
                            0.5*(1/(avgStats["ftpct"]/avgStats["ftm"]-avgStats["ftm"])) + 2*avgStats["3pm"];

    }

    std::unordered_map<std::string, double> Player::getAvgStats() {
        return avgStats;
    }
    

    bool Player::willPlay(std::chrono::sys_days date) {
        return (bool) dateToGameLog.count(date);
    }

}