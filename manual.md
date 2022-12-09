# Manual

The test.cpp it the best practice of how to use Fantasy Optimizer

## choose the time and create a league

``` c++
std::string currDate = "2022-10-24";
League::League testLeague(currDate);
```

## add teams
``` c++
testLeague.addTeam("Frank's Team");
testLeague.addTeam("Figo");
```

## add roster info to currDate
``` c++
// set every player to the bench
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

testLeague.teamSetPlayerPlacement(0, myPlacement);
testLeague.teamSetPlayerPlacement(1, figoPlacement);
```

## create a matchup and copy the roster to whole week
``` c++
Match::Match newMatch("Frank's Team", "Figo", &testLeague);
newMatch.createWeekRosterBaseOnMonday();
```

## addd free agents to my watchlist
``` c++
testLeague.teamAddPlayerToWatchList(0, "nesmiaa01");
testLeague.teamAddPlayerToWatchList(0, "jacksis01");
testLeague.teamAddPlayerToWatchList(0, "kesslwa01");
```

## find the best roster by our optimizer
``` c++
Optimizer::GreedyOptimizer greedyOptimizer(&newMatch); // my optimizer
Optimizer::StreamOptimizer streamOptimzer(&newMatch); // opponents's pptimizer
newMatch.applyOptimizer(theDayPoint, &streamOptimzer, &greedyOptimizer);
```

## show result prediction
``` c++
newMatch.showResults();
```