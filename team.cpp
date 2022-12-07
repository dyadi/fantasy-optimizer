#include "team.h"
#include "roster.h"
#include <iostream>

namespace Team {
    
    Team::Team(std::string teamName) : teamName(teamName) {}

    std::string Team::getName(){
        return teamName;
    }

    bool Team::addPlayer(std::chrono::sys_days date, Player::Player* player) {
        
        if (!dailyRoster.count(date)){
            Roster::Roster newRoster;
            dailyRoster[date] = newRoster;
        }
        
        if (dailyRoster[date].isInRoster(player)) {
            return false;
        }
        
        return dailyRoster[date].addToBench(player);
    }

    bool Team::dropPlayer(std::chrono::sys_days date, Player::Player* player) {
        
        if (!dailyRoster.count(date)){
            std::cout << "Can't drop aththlete, no roster in that date." << std::endl;
            return false;
        }

        return dailyRoster[date].dropFromEverySpot(player);

    }

}
