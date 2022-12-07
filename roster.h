#ifndef ROSTER_H
#define ROSTER_H

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

#include "player.h"
#include "gamelog.h"

namespace Roster {
    
    class Roster {

        public:
            Roster();
            Roster(int, int, int, int, int, int, int, int, int);
            // Roster(const Roster&);
            bool isInRoster(Player::Player*);
            bool addToBench(Player::Player*);
            bool placePlayer(Player::Player*, std::string, bool);
            bool swapPlayerPlacement(Player::Player*, Player::Player*, bool);
            bool dropFromEverySpot(Player::Player*);
            bool canPlace(Player::Player*, std::string);
            int getTotalLimit();
            int getTotalPlayer();
            void showRoster();
            GameLog::GameLog getSum(std::chrono::sys_days);

        private:
            // std::unordered_set<Player::Player*> pgRoster;
            // std::unordered_set<Player::Player*> sgRoster;
            // std::unordered_set<Player::Player*> gRoster;
            // std::unordered_set<Player::Player*> sfRoster;
            // std::unordered_set<Player::Player*> pfRoster;
            // std::unordered_set<Player::Player*> fRoster;
            // std::unordered_set<Player::Player*> utilRoster;
            // std::unordered_set<Player::Player*> bench;

            std::unordered_map<std::string, std::unordered_set<Player::Player*>> playerPlacement;

            // int sgLimit;
            // int pgLimit;
            // int gLimit;
            // int sfLimit;
            // int pfLimit;
            // int fLimit;
            // int utilLimit;
            // int benchSpot;

            std::unordered_map<std::string, int> positionQuota;

            std::string positionTitle[9] {"BN", "PG", "SG", "SF", "PF", "C", "G", "F", "UTIL"};

    };

}

#endif