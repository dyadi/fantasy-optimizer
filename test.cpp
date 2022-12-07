#include <iostream>
#include <string.h>
#include "utils/date.h"

#include "league.h"
#include "match.h"

int main() {

    std::string currTime = "2022-10-31";

    // std::istringstream iss {"2020-12-21"};
    // std::chrono::sys_days theDayPoint;
    // iss >> date::parse("%F", theDayPoint);
    
    League::League testLeague(currTime);
    
    testLeague.loadData();
    // testLeague.showPlayer("lavinza01");
    // testLeague.showPlayer("bridgmi01");

    testLeague.addTeam("dyadi");
    testLeague.addTeam("fff321755");
    
    testLeague.showTeams();
    
    testLeague.teamAddPlayer(0, "lavinza01");
    testLeague.teamAddPlayer(1, "bridgmi01");

    testLeague.showPlayer("bridgmi01");

    std::cout << testLeague.teamPlacePlayer(0, "lavinza01", "SG", true) << std::endl;
    std::cout << testLeague.teamPlacePlayer(1, "bridgmi01", "SF", true) << std::endl;

    testLeague.showTeamPlayers(0);
    testLeague.showTeamPlayers(1);

    Match::Match newMatch("dyadi", "fff321755", &testLeague);

    newMatch.createWeekRosterBaseOnModay();
    newMatch.simulate();
    newMatch.showResults();
    

    return 0;
}
