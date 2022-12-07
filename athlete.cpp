#include <iostream>

#include "athlete.h"
#include "utils/date.h"


namespace Athlete {
    
    Athlete::Athlete() {}

    Athlete::Athlete(std::string palyer_id, std::string palyer_name) : palyer_id(palyer_id), palyer_name(palyer_name) {}

    void Athlete::addGameLog(std::chrono::sys_days date, GameLog::GameLog gamelog) {

        // if(palyer_id == "bridgmi01" && date2gamelog.count(date)){
        //     std::cout << "already in" << palyer_id << std::endl;
        //     date2gamelog[date].showGameLog();
        //     gamelog.showGameLog();
        //     std::cout << palyer_id << " game played " << date2gamelog.size() << std::endl;
        //     throw 50;
        // }

        date2gamelog[date] = gamelog;
        // if (palyer_id == "bridgmi01") {
        //     std::cout << palyer_id << " game played " << date2gamelog.size() << std::endl;
        // }
        
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

    int Athlete::getGameLogSize(){
        return date2gamelog.size();
    }

}