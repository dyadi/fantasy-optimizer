#ifndef TEAM_H
#define TEAM_H

#include <vector>
#include <string>
#include <chrono>
#include <variant>
#include <map>

#include "athlete.h"
#include "roster.h"

namespace Team {

    class Team {

        public:
            Team(std::string);
            std::string getName();
            bool addAthlete(std::chrono::sys_days, Athlete::Athlete*);
            bool dropAthlete(std::chrono::sys_days, Athlete::Athlete*);

        private:
            std::string teamName;
            std::map<std::chrono::sys_days, Roster::Roster> dailyRoster;

    };
}

#endif