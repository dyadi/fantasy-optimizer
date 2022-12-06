#include <iostream>

#include "athlete.h"


namespace Athlete {
    
    Athlete::Athlete() {}

    Athlete::Athlete(std::string palyer_id, std::string palyer_name) : palyer_id(palyer_id), palyer_name(palyer_name) {}

    void Athlete::addGameLog(std::chrono::time_point<std::chrono::system_clock> date, GameLog::GameLog gamelog) {
        date2gamelog[date] = gamelog;
    }

    void Athlete::addPosition(std::string pos) {
        positions.insert(pos);
    }

    void Athlete::showInfo(){
        std::cout << "========================" << "\n";
        std::cout << "Palyer_ID\t" << palyer_id << "\n";
        std::cout << "Palyer_Name\t" << palyer_name << "\n";
        std::cout << "Palyer_Position\t";
        for (auto pos: positions){
            std::cout << pos << " ";
        }
        std::cout << "\n";

        std::cout << "GameLog Length\t" << date2gamelog.size() << "\n";

        std::cout << std::endl;

    }

}