#include "optimizer.h"

#include "utils/date.h"

using date::operator<<;


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
        std::cout << "Size is " << match->myTeam->dailyRoster[startDate].playerPlacement["BN"].size() << std::endl;
        for (auto& player : match->myTeam->dailyRoster[startDate].playerPlacement["BN"]) {
            for (auto& pos : stupidPlacement.positionTitle) {
                if (pos == "BN") {
                    continue;
                }
                auto res = stupidPlacement.placePlayer(player, pos, false);
                if (stupidPlacement.placePlayer(player, pos, false)) {
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