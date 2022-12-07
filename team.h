#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>
#include <chrono>
#include <variant>
#include <map>

#include "player.h"
#include "roster.h"

namespace Team {

    class Team {

        public:
            Team(std::string);
            std::string getName();
            bool addPlayer(std::chrono::sys_days, Player::Player*);
            bool dropPlayer(std::chrono::sys_days, Player::Player*);

        private:
            std::string teamName;
            std::map<std::chrono::sys_days, Roster::Roster> dailyRoster;

    };
}

#endif