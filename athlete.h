#include <vector>
#include <string>
#include <chrono>
#include <map>

#include "gamelog.h"

namespace Athlete {
    
    class Athlete {

        public:
            Athlete(std::string);
            void addGameLog(std::chrono::time_point<std::chrono::system_clock>, GameLog::GameLog);

            // getAccGameLog();

            // getWeekGameLog();


        private:
            std::string id;
            std::map<std::chrono::time_point<std::chrono::system_clock>, GameLog::GameLog> date2gamelog;

    };
}