#include "athlete.h"

namespace Athlete {
    
    Athlete::Athlete() {}

    Athlete::Athlete(std::string palyer_id, std::string palyer_name) : palyer_id(palyer_id), palyer_name(palyer_name) {}

    void Athlete::addGameLog(std::chrono::time_point<std::chrono::system_clock> date, GameLog::GameLog gamelog) {
        date2gamelog[date] = gamelog;
    }

}