#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>
#include <chrono>
#include <variant>
#include <map>

#include "player.h"
#include "roster.h"

namespace Match {
    class Match;
}

namespace Optimizer {
    class StupidOptimizer;
    class GreedyOptimizer;
    class StreamOptimizer;
}

namespace Team {

    class Team {
        
        public:
            Team(std::string);
            std::string getName();
            
            bool addPlayer(std::chrono::sys_days, Player::Player*);
            bool dropPlayer(std::chrono::sys_days, Player::Player*);

            void addPlayerToWatchList(Player::Player*);
            void dropPlayerFromWatchList(Player::Player*);
            std::unordered_set<Player::Player*> getWatchList();

            bool placePlayerToDate(std::chrono::sys_days, Player::Player*, std::string, bool);
            bool swapPlayerPlacementToDate(std::chrono::sys_days, Player::Player*, Player::Player*, bool);
            bool setPlayerPlacementToDate(std::chrono::sys_days, std::unordered_map<std::string, std::unordered_set<Player::Player*>>);

            Roster::Roster& getRoster(std::chrono::sys_days);
            GameLog::GameLog getDailySum(std::chrono::sys_days);
            GameLog::GameLog getDailySum(std::chrono::sys_days, std::map<std::chrono::sys_days, Roster::Roster>);
            GameLog::GameLog getDailySumForecast(std::chrono::sys_days, std::map<std::chrono::sys_days, Roster::Roster>);

            bool copyRoster(std::chrono::sys_days, std::chrono::sys_days);

        private:
            std::string teamName;
            std::map<std::chrono::sys_days, Roster::Roster> dailyRoster;
            std::unordered_set<Player::Player*> watchList;

        friend class Match::Match;
        friend class Optimizer::StupidOptimizer;
        friend class Optimizer::GreedyOptimizer;
        friend class Optimizer::StreamOptimizer;

    };
}

#endif