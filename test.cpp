#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "utils/date.h"

#include "league.h"
#include "match.h"
#include "optimizer.h"

int main() {

    // choose the time
    std::string currDate = "2022-10-24";
    std::istringstream iss {"2022-10-24"};
    std::chrono::sys_days theDayPoint;
    iss >> date::parse("%F", theDayPoint);
    
    // create a league
    League::League testLeague(currDate);
    
    // add teams
    testLeague.addTeam("Frank's Team");
    testLeague.addTeam("Figo");
    
    // setup rosters
    std::unordered_map<std::string, std::unordered_set<std::string>> myPlacement{
        {"BN", std::unordered_set<std::string>{"poolejo01", "maxeyty01", "claxtni01",
                                                "antetgi01", "butleji01", "huntede01",
                                                "brookdi01", "portemi01", "willigr01",
                                                "adebaba01", "westbru01", "anunoog01",
                                                "strusma01", 
                                                }}
    };

    
    std::unordered_map<std::string, std::unordered_set<std::string>> figoPlacement{
        {"BN", std::unordered_set<std::string>{"paulch01", "jacksre01", "simonan01",
                                                "georgpa01", "haywago01", "valanjo01",
                                                "herroty01", "hartjo01", "carusal01",
                                                "porteke02", "robinmi01", "garubus01",
                                                "embiijo01"
                                                }}
    };
    // setup my team's roster for current date
    std::cout << "my team: " << testLeague.teamSetPlayerPlacement(0, myPlacement) << std::endl;
    // setup opponent's team's roster for current date
    std::cout << "his team: " << testLeague.teamSetPlayerPlacement(1, figoPlacement) << std::endl;


    testLeague.showTeamPlayers(0);
    testLeague.showTeamPlayers(1);

    // create a match, and copy the roster to ever day in the week
    Match::Match newMatch("Frank's Team", "Figo", &testLeague);
    newMatch.createWeekRosterBaseOnMonday();

    // newMatch.simulate();
    // newMatch.showResults();

    // using stupid Otimizer for both teams
    std::cout << "\n\n\n\nStupidOptimizer\n\n";
    Optimizer::StupidOptimizer optimizer(&newMatch);
    newMatch.applyOptimizer(theDayPoint, &optimizer);
    newMatch.showResults();

    // using Greedy Otimizer for both teams
    std::cout << "\n\n\n\nGreedyOptimizer\n\n";
    Optimizer::GreedyOptimizer greedyOptimizer(&newMatch);
    newMatch.applyOptimizer(theDayPoint, &greedyOptimizer);
    newMatch.showResults();

    // using Stream Optimizer for our team, and Greedy Optimizer for opponent's team
    std::cout << "\n\nStreamOptimizer\n\n";

    // added to streamer candidate to watch list
    testLeague.teamAddPlayerToWatchList(0, "nesmiaa01");
    testLeague.teamAddPlayerToWatchList(0, "jacksis01");
    testLeague.teamAddPlayerToWatchList(0, "kesslwa01");
    // testLeague.teamAddPlayerToWatchList(0, "mathube01");
    // testLeague.teamAddPlayerToWatchList(0, "walkelo01");
    // testLeague.teamAddPlayerToWatchList(0, "carteje01");
    // testLeague.teamAddPlayerToWatchList(0, "davisan02");
    Optimizer::StreamOptimizer streamOptimzer(&newMatch);
    newMatch.applyOptimizer(theDayPoint, &streamOptimzer, &greedyOptimizer);
    newMatch.showResults();
    
    return 0;
}