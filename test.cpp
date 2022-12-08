#include <iostream>
#include <string.h>
#include <unordered_map>
#include <unordered_set>
#include "utils/date.h"

#include "league.h"
#include "match.h"
#include "optimizer.h"

int main() {

    std::string currTime = "2022-10-24";

    std::istringstream iss {"2020-10-24"};
    std::chrono::sys_days theDayPoint;
    iss >> date::parse("%F", theDayPoint);
    
    League::League testLeague(currTime);
    
    testLeague.loadData();
    // testLeague.showPlayer("lavinza01");
    // testLeague.showPlayer("bridgmi01");

    testLeague.addTeam("fff321755");
    testLeague.addTeam("dyadi");
    
    testLeague.showTeams();

    std::unordered_map<std::string, std::unordered_set<std::string>> newPlacement{
        {"BN", std::unordered_set<std::string>{"poolejo01", "maxeyty01", "claxtni01", "antetgi01", "butleji01"}}
    };

    // std::unordered_map<std::string, std::unordered_set<std::string>> newPlacement{
    //     {"PG", std::unordered_set<std::string>{"poolejo01"}},
    //     {"SG", std::unordered_set<std::string>{"maxeyty01"}},
    //     {"C", std::unordered_set<std::string>{"claxtni01"}},
    //     {"PF", std::unordered_set<std::string>{"antetgi01"}},
    //     {"SF", std::unordered_set<std::string>{"butleji01"}}
    // };
    
    // testLeague.teamAddPlayer(0, "antetgi01");
    // testLeague.teamAddPlayer(0, "adebaba01");
    // testLeague.teamAddPlayer(0, "butleji01");
    // testLeague.teamAddPlayer(0, "maxeyty01");
    // testLeague.teamAddPlayer(0, "anunoog01");
    // testLeague.teamAddPlayer(0, "porteke02");
    // testLeague.teamAddPlayer(0, "poolejo01");
    // testLeague.teamAddPlayer(0, "westbru01");
    // testLeague.teamAddPlayer(0, "claxtni01");
    // testLeague.teamAddPlayer(0, "huntede01");
    // testLeague.teamAddPlayer(0, "willigr01");
    // testLeague.teamAddPlayer(0, "allengr01");

    testLeague.teamAddPlayer(1, "bridgmi01");

    // testLeague.showPlayer("bridgmi01");

    std::cout << testLeague.teamSetPlayerPlacement(0, newPlacement) << std::endl;
    std::cout << testLeague.teamPlacePlayer(1, "bridgmi01", "SF", true) << std::endl;

    testLeague.showTeamPlayers(0);
    testLeague.showTeamPlayers(1);

    Match::Match newMatch("fff321755", "dyadi", &testLeague);
    

    newMatch.createWeekRosterBaseOnModay();
    newMatch.simulate();
    newMatch.showResults();

    Optimizer::StupidOptimizer optimizer(&newMatch);
    newMatch.applyOptimizer(theDayPoint, &optimizer);
    newMatch.showResults();
    
    return 0;
}
