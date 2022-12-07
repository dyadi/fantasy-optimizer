#ifndef ATHLETE_H
#define ATHLETE_H

#include <vector>
#include <string>
#include <chrono>
#include <map>
#include <unordered_set>

#include "gamelog.h"

namespace Athlete {
    
    class Athlete {

        public:
            Athlete();

            Athlete(std::string, std::string);

            void showInfo();

            void addPosition(std::string);

            void addGameLog(std::chrono::sys_days, GameLog::GameLog);

            int getGameLogSize();

            // getAccGameLog();

            // getWeekGameLog();

        private:
            std::string palyer_id;
            std::string palyer_name;
            std::unordered_set<std::string> positions;
            std::map<std::chrono::sys_days, GameLog::GameLog> date2gamelog;

    };

}

#endif