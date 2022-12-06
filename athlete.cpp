#include "athlete.h"

namespace Athlete {
    
    Athlete::Athlete(std::string id) : id(id) {}

    void Athlete::addGameLog(std::chrono::time_point<std::chrono::system_clock> date, GameLog::GameLog gamelog) {
        date2gamelog[date] = gamelog;
    }


}