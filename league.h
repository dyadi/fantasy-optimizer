#ifndef LEAGUE_H
#define LEAGUE_H

#include <vector>
#include <unordered_map>
#include <string>
#include <chrono>
#include <map>

#include "player.h"
#include "team.h"

namespace League {

    class League {
        public:
            League(std::string);
            League(std::chrono::sys_days);
            void loadData();

            void addTeam(std::string);
            void showTeams();
            void showTeamPlayers(int);
            void teamAddPlayer(int, std::string);

            void showPlayer(std::string);

            int getPlayerCnt();

        private:
            // call by constructor, load data
            // std::vector<Player> player_list;
            std::unordered_map<std::string, Player::Player> idToPlayer;
            std::unordered_map<std::string, int> idToTeamNumber;
            std::vector<Team::Team> teamList;
            std::chrono::sys_days currDate;

            int weeklyBudget;
            
    };
}

#endif