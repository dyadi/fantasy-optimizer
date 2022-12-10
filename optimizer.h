#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <map>
#include <set>
#include <chrono>
#include "utils/date.h"

#include "player.h"
#include "match.h"
#include "roster.h"

namespace Optimizer {

    class BaseOptimizer {

        public:
            BaseOptimizer();
            virtual std::map<std::chrono::sys_days, Roster::Roster> getOptimalRoster(std::chrono::sys_days, Team::Team*) = 0;

        protected:
            Match::Match* match;    

    };

    class StupidOptimizer : public BaseOptimizer {

        public:
            StupidOptimizer(Match::Match*);
            std::map<std::chrono::sys_days, Roster::Roster> getOptimalRoster(std::chrono::sys_days, Team::Team*);

    };

    class GreedyOptimizer : public BaseOptimizer {

        public:
            GreedyOptimizer(Match::Match*);
            std::map<std::chrono::sys_days, Roster::Roster> getOptimalRoster(std::chrono::sys_days, Team::Team*);
            std::map<std::chrono::sys_days, Roster::Roster> getOptimalRosterForecast(std::chrono::sys_days, Roster::Roster);

    };

    class StreamOptimizer : public BaseOptimizer {

        public:
            StreamOptimizer(Match::Match*);
            std::map<std::chrono::sys_days, Roster::Roster> getOptimalRoster(std::chrono::sys_days, Team::Team*);
            Player::Player* getOptimalStreamer(std::chrono::sys_days startDate, Team::Team* team, std::string playerDrop);
            
    };
}

#endif