#include <iostream>

#include "league.h"

int main() {
    
    League::League testLeague;
    
    testLeague.load_data();
    testLeague.showAthlete("lavinza01");
    testLeague.showAthlete("bridgmi01");
    std::cout << "Athlete Cnt:" << testLeague.getAthleteNum() << std::endl;
    

    return 0;
}
