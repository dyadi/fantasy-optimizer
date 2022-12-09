#ifndef LEAGUE_H
#define LEAGUE_H

#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <chrono>
#include <map>

#include "player.h"
#include "team.h"

namespace Match {
    class Match;
}

namespace Optimizer {
    class StupidOptimizer;
    class GreedyOptimizer;
    class StreamOptimizer;
}

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
            void teamDropPlayer(int, std::string);
            void teamAddPlayerToWatchList(int, std::string);
            void teamDropPlayerFromWatchList(int, std::string);
            bool teamPlacePlayer(int, std::string, std::string, bool);
            bool teamSwapPlayerPlacement(int, std::string, std::string, bool);
            bool teamSetPlayerPlacement(int, std::unordered_map<std::string, std::unordered_set<std::string>>);
            void showPlayer(std::string);
            void setCategory(std::unordered_set<std::string>);
            

            int getPlayerCnt();

        private:
            // call by constructor, load data
            // std::vector<Player> player_list;
            std::unordered_map<std::string, Player::Player> idToPlayer;
            std::unordered_map<std::string, int> idToTeamNumber;
            std::vector<Team::Team> teamList;
            std::chrono::sys_days currDate;
            std::unordered_map<std::string, bool> categories;
            std::vector<std::string> categoryKey {"fgm", "fgpct", "ftm", "ftpct", "3pm", "3pmpct", "pts", "astor", "drb", "orb", "trb", "ast", "stl", "blk", "tov", "dd"};

            int weeklyBudget;
            
        friend class Match::Match;
        friend class Optimizer::StupidOptimizer;
        friend class Optimizer::GreedyOptimizer;
        friend class Optimizer::StreamOptimizer;

        
    };
}

#endif