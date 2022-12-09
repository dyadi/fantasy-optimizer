#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "utils/date.h"

#include "league.h"
#include "match.h"
#include "optimizer.h"

int main() {

    std::string currTime = "2022-10-24";

    std::istringstream iss {"2022-10-24"};
    std::chrono::sys_days theDayPoint;
    iss >> date::parse("%F", theDayPoint);
    
    League::League testLeague(currTime);
    
    testLeague.addTeam("fff321755");
    testLeague.addTeam("figo");
    
    // testLeague.showTeams();

    std::unordered_map<std::string, std::unordered_set<std::string>> myPlacement{
        {"BN", std::unordered_set<std::string>{"poolejo01", "maxeyty01", "claxtni01",
                                                "antetgi01", "butleji01", "huntede01",
                                                "brookdi01", "portemi01", "willigr01",
                                                "adebaba01", "westbru01", "anunoog01",
                                                "strusma01", 
                                                }}
    }; // "manntr01", "colliza01"

    std::unordered_map<std::string, std::unordered_set<std::string>> figoPlacement{
        {"BN", std::unordered_set<std::string>{"paulch01", "jacksre01", "simonan01",
                                                "georgpa01", "haywago01", "valanjo01",
                                                "herroty01", "hartjo01", "carusal01",
                                                "porteke02", "robinmi01", "garubus01",
                                                "embiijo01"
                                                }}
    };
    // testLeague.showPlayer("bridgmi01");

    std::cout << "my team: " << testLeague.teamSetPlayerPlacement(0, myPlacement) << std::endl;
    std::cout << "his team: " << testLeague.teamSetPlayerPlacement(1, figoPlacement) << std::endl;

    testLeague.showTeamPlayers(0);
    testLeague.showTeamPlayers(1);

    Match::Match newMatch("fff321755", "figo", &testLeague);
    
    // newMatch.createWeekRosterBaseOnMonday();
    // newMatch.simulate();
    // newMatch.showResults();

    // std::cout << "\n\n\n\nStupidOptimizer\n\n";
    // Optimizer::StupidOptimizer optimizer(&newMatch);
    // newMatch.applyOptimizer(theDayPoint, &optimizer);
    // newMatch.showResults();

    std::cout << "\n\n\n\nGreedyOptimizer\n\n";
    Optimizer::GreedyOptimizer greedyOptimizer(&newMatch);
    newMatch.applyOptimizer(theDayPoint, &greedyOptimizer);
    newMatch.showResults();

    std::cout << "\n\nStreamOptimizer\n\n";
    testLeague.teamAddPlayerToWatchList(0, "bookede01");
    testLeague.teamAddPlayerToWatchList(0, "davisan02");
    testLeague.teamAddPlayerToWatchList(0, "bolbo01");


    Optimizer::StreamOptimizer streamOptimzer(&newMatch);
    newMatch.applyOptimizer(theDayPoint, &streamOptimzer);
    newMatch.showResults();
    
    return 0;
}