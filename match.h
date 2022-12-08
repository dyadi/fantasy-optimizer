#ifndef MATCH_H
#define MATCH_H

#include <chrono>

#include "team.h"
#include "gamelog.h"
#include "league.h"

namespace Optimizer {
    class BaseOptimizer;
    class StupidOptimizer;
}

namespace Match {

    class Match {

        public:
            Match(Team::Team*, Team::Team*, League::League*);

            Match(std::string, std::string, League::League*);

            bool simulate();
            bool simulate(std::map<std::chrono::sys_days, Roster::Roster>);
            void showResults();
            void createWeekRosterBaseOnModay();
            void applyOptimizer(std::chrono::sys_days, Optimizer::BaseOptimizer*);

        private:
            Team::Team *myTeam, *oppoTeam;
            GameLog::GameLog myResult, oppoResult;
            League::League* league;

        friend class Optimizer::StupidOptimizer;

    };
    
}

#endif
