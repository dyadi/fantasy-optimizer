#include "optimizer.h"

namespace Optimizer {

    BaseOptimizer::BaseOptimizer() {}
    
    StupidOptimizer::StupidOptimizer(Match::Match* match) {
        this->match = match;
    }

    std::map<std::chrono::sys_days, Roster::Roster> StupidOptimizer::StupidOptimizer::getOptimalRoster(std::chrono::sys_days startDate) {
        
        std::chrono::sys_days monday = startDate - (date::weekday{startDate} - date::Monday);
        std::chrono::sys_days sunday = monday + std::chrono::days{6};

        // generate stupid player placement
        Roster::Roster stupidPlacement = match->myTeam->dailyRoster[startDate];
        match->myTeam->dailyRoster[startDate].showRoster();
        std::cout << "Size is " << match->myTeam->dailyRoster[startDate].playerPlacement["BN"].size() << std::endl;
        for (auto& player : match->myTeam->dailyRoster[startDate].playerPlacement["BN"]) {
            std::cout << "hihihhih" << std::endl;
            for (auto& pos : stupidPlacement.positionTitle) {
                std::cout << "pos is " << pos << std::endl;
                auto res = stupidPlacement.placePlayer(player, pos, false);
                std::cout << "res is " << res << std::endl;
                if (stupidPlacement.placePlayer(player, pos, false)) {
                    std::cout << "Placed: " << player->getInfo()["playerId"] << std::endl;
                    break;
                }
            }
        }

        for (auto currDay = monday; currDay < startDate; currDay += std::chrono::days{1}) {
            optimalRoster[currDay] = match->myTeam->dailyRoster[currDay];
        }

        for (auto currDay = startDate; currDay <= sunday; currDay += std::chrono::days{1}) {
            optimalRoster[currDay] = stupidPlacement;
        }

        return optimalRoster;

    };

}