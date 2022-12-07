#ifndef MATCH_H
#define MATCH_H

#include <chrono>

#include "team.h"
#include "gamelog.h"
#include "league.h"


namespace Match {

    class Match {
        public:
            Match(Team::Team*, Team::Team*, League::League*);

            Match(std::string, std::string, League::League*);

            bool simulate();
            void showResults();
            void createWeekRosterBaseOnModay();

        private:
            Team::Team *myTeam, *oppoTeam;
            GameLog::GameLog myResult, oppoResult;
            League::League* league;

    };
    
}

#endif
