#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include <chrono>
#include <map>
#include <unordered_set>
#include <unordered_map>

#include "gamelog.h"

namespace Player {
    
    class Player {

        public:
            Player();

            Player(std::string, std::string);

            void showInfo();

            std::unordered_map<std::string, std::string> getInfo();

            void addPosition(std::string);

            std::unordered_set<std::string> getPositions();

            void addGameLog(std::chrono::sys_days, GameLog::GameLog);

            GameLog::GameLog getGameLog(std::chrono::sys_days);

            int getGameLogSize();

            void updateAvgStats();

        private:
            std::string playerId;
            std::string playerName;
            std::unordered_map<std::string, double> avgStats;

            std::unordered_set<std::string> positions;
            std::map<std::chrono::sys_days, GameLog::GameLog> date2gamelog;
            

    };

}

#endif