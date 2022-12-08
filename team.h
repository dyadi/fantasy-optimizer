#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>
#include <chrono>
#include <variant>
#include <map>

#include "player.h"
#include "roster.h"

// #include "match.h"

namespace Match {
    class Match;
}

namespace Optimizer {
    class StupidOptimizer;
}

namespace Team {

    class Team {

        public:
            Team(std::string);
            std::string getName();
            
            bool addPlayer(std::chrono::sys_days, Player::Player*);
            bool dropPlayer(std::chrono::sys_days, Player::Player*);

            bool placePlayerToDate(std::chrono::sys_days, Player::Player*, std::string, bool);
            bool swapPlayerPlacementToDate(std::chrono::sys_days, Player::Player*, Player::Player*, bool);
            bool setPlayerPlacementToDate(std::chrono::sys_days, std::unordered_map<std::string, std::unordered_set<Player::Player*>>);

            Roster::Roster& getRoster(std::chrono::sys_days);
            GameLog::GameLog getDailySum(std::chrono::sys_days);
            GameLog::GameLog getDailySum(std::chrono::sys_days, std::map<std::chrono::sys_days, Roster::Roster>);

            bool copyRoster(std::chrono::sys_days, std::chrono::sys_days);


        private:
            std::string teamName;
            std::map<std::chrono::sys_days, Roster::Roster> dailyRoster;

        friend class Match::Match;
        friend class Optimizer::StupidOptimizer;

    };
}

#endif