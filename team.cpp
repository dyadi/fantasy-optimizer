#include "team.h"
#include "roster.h"
#include <iostream>

namespace Team {
    
    Team::Team(std::string teamName) : teamName(teamName) {}

    std::string Team::getName(){
        return teamName;
    }

    bool Team::addAthlete(std::chrono::sys_days date, Athlete::Athlete* athlete) {
        
        if (!dailyRoster.count(date)){
            Roster::Roster newRoster;
            dailyRoster[date] = newRoster;
        }
        
        if (dailyRoster[date].isInRoster(athlete)) {
            return false;
        }
        
        return dailyRoster[date].addToBench(athlete);
    }

    bool Team::dropAthlete(std::chrono::sys_days date, Athlete::Athlete* athlete) {
        
        if (!dailyRoster.count(date)){
            std::cout << "Can't drop aththlete, no roster in that date." << std::endl;
            return false;
        }

        return dailyRoster[date].dropFromEverySpot(athlete);

    }

}
