#include <iostream>

#include "player.h"
#include "utils/date.h"

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

        std::cout << "GameLog Length\t" << date2gamelog.size() << "\n";

        std::cout << std::endl;

    }

    std::unordered_map<std::string, std::string> Player::getInfo(){
        return std::unordered_map<std::string, std::string> {{"playerId",playerId}, {"playerName", playerName}};
    }

    void Player::addPosition(std::string pos) {
        positions.insert(pos);
    }

    std::unordered_set<std::string> Player::getPositions () {
        return positions;
    }

    void Player::addGameLog(std::chrono::sys_days date, GameLog::GameLog gamelog) {

        // if(player_id == "bridgmi01" && date2gamelog.count(date)){
        //     std::cout << "already in" << player_id << std::endl;
        //     date2gamelog[date].showGameLog();
        //     gamelog.showGameLog();
        //     std::cout << player_id << " game played " << date2gamelog.size() << std::endl;
        //     throw 50;
        // }

        date2gamelog[date] = gamelog;
        // if (player_id == "bridgmi01") {
        //     std::cout << player_id << " game played " << date2gamelog.size() << std::endl;
        // }
        
    }

    GameLog::GameLog Player::getGameLog(std::chrono::sys_days date) {
        return date2gamelog[date];
    }

    int Player::getGameLogSize(){
        return date2gamelog.size();
    }

}