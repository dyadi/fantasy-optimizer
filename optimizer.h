#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <map>
#include <chrono>
#include "utils/date.h"

#include "match.h"
#include "roster.h"

namespace Optimizer {

    class BaseOptimizer {

        public:
            BaseOptimizer();
            virtual std::map<std::chrono::sys_days, Roster::Roster> getOptimalRoster(std::chrono::sys_days) = 0;

        protected:
            Match::Match* match;
            std::map<std::chrono::sys_days, Roster::Roster> optimalRoster;

    };

    class StupidOptimizer : public BaseOptimizer {

        public:
            StupidOptimizer(Match::Match*);
            std::map<std::chrono::sys_days, Roster::Roster> getOptimalRoster(std::chrono::sys_days);

    };

    class GreedyOptimizer : public BaseOptimizer {

        public:
            std::map<std::chrono::sys_days, Roster::Roster> getOptimalRoster(std::chrono::sys_days);

    };

}

#endif