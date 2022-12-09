#ifndef MATCH_H
#define MATCH_H

#include <chrono>

#include "team.h"
#include "gamelog.h"
#include "league.h"

namespace Optimizer {
    class BaseOptimizer;
    class StupidOptimizer;
    class GreedyOptimizer;
    class StreamOptimizer;
}

namespace Match {

    class Match {

        public:
            Match(Team::Team*, Team::Team*, League::League*);

            Match(std::string, std::string, League::League*);

            bool simulate();
            bool simulate(std::map<std::chrono::sys_days, Roster::Roster>, Team::Team*);
            void showResults();
            void createWeekRosterBaseOnMonday();
            void applyOptimizer(std::chrono::sys_days, Optimizer::BaseOptimizer*);
            void applyOptimizer(std::chrono::sys_days, Optimizer::BaseOptimizer*, Optimizer::BaseOptimizer*);
            double getForecastScore(std::chrono::sys_days, Roster::Roster, Optimizer::GreedyOptimizer*);
            double getScore(std::unordered_map<std::string, double>, std::unordered_map<std::string, double>);


        private:
            Team::Team *myTeam, *oppoTeam;
            GameLog::GameLog myResult, oppoResult;
            League::League* league;
            int myBudget, oppoBudget;

        friend class Optimizer::StupidOptimizer;
        friend class Optimizer::GreedyOptimizer;
        friend class Optimizer::StreamOptimizer;

    };
    
}

#endif
