#include <iostream>
#include "utils/date.h"

#include "league.h"

int main() {
    
    League::League testLeague("2020-12-24");
    
    testLeague.loadData();
    // testLeague.showAthlete("lavinza01");
    // testLeague.showAthlete("bridgmi01");

    testLeague.addTeam("dyadi");
    testLeague.addTeam("fff321755");
    
    testLeague.showTeams();
    
    testLeague.teamAddAthlete(0, "lavinza01");
    testLeague.teamAddAthlete(1, "bridgmi01");

    testLeague.showTeamPlayers(0);
    testLeague.showTeamPlayers(1);

    return 0;
}
