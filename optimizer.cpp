#include "optimizer.h"

#include "utils/date.h"

using date::operator<<;

namespace Optimizer {

    BaseOptimizer::BaseOptimizer() {}
    
    StupidOptimizer::StupidOptimizer(Match::Match* match) {
        this->match = match;
    }

    std::map<std::chrono::sys_days, Roster::Roster> StupidOptimizer::getOptimalRoster(std::chrono::sys_days startDate, Team::Team* team) {
        
        std::map<std::chrono::sys_days, Roster::Roster> optimalRoster;

        std::chrono::sys_days monday = startDate - (date::weekday{startDate} - date::Monday);
        std::chrono::sys_days sunday = monday + std::chrono::days{6};

        for (auto currDay = monday; currDay < startDate; currDay += std::chrono::days{1}) {
            optimalRoster[currDay] = team->dailyRoster[currDay];
        }

        // generate stupid player placement
        Roster::Roster stupidPlacement = team->dailyRoster[startDate];
        // std::cout << "Size is " << team->dailyRoster[startDate].playerPlacement["BN"].size() << std::endl;
        for (auto& player : team->dailyRoster[startDate].playerPlacement["BN"]) {
            for (auto& pos : stupidPlacement.positionTitle) {
                if (pos == "BN") {
                    continue;
                }
                if (stupidPlacement.placePlayer(player, pos, false)) {
                    break;
                }
            }
        }

        for (auto currDay = startDate; currDay <= sunday; currDay += std::chrono::days{1}) {
            optimalRoster[currDay] = stupidPlacement;
        }

        return optimalRoster;

    };

    GreedyOptimizer::GreedyOptimizer(Match::Match* match) {
        this->match = match;
    }

    std::map<std::chrono::sys_days, Roster::Roster> GreedyOptimizer::getOptimalRoster(std::chrono::sys_days startDate, Team::Team* team) {
        
        std::map<std::chrono::sys_days, Roster::Roster> optimalRoster;

        std::chrono::sys_days monday = startDate - (date::weekday{startDate} - date::Monday);
        std::chrono::sys_days sunday = monday + std::chrono::days{6};

        for (auto currDay = monday; currDay < startDate; currDay += std::chrono::days{1}) { 
            optimalRoster[currDay] = team->dailyRoster[currDay];
        }

        auto currDateRoster = team->dailyRoster[startDate];

        for (auto currDay = startDate; currDay <= sunday; currDay += std::chrono::days{1}) {
            
            auto cmp = [](Player::Player* p1, Player::Player* p2) {
                return p1->getAvgStats()["score"] > p2->getAvgStats()["score"];
            };

            std::set<Player::Player*, decltype(cmp)> currDayWillPlay;

            currDateRoster.placeAllToBench();
            
            for (auto& player : currDateRoster.playerPlacement["BN"]) {
                if (player->willPlay(currDay)) {
                    currDayWillPlay.insert(player);
                }
            }

            for (auto& player : currDayWillPlay){
                for (auto& pos : currDateRoster.positionTitle) {
                    if (pos == "BN") {
                        continue;
                    }
                    if (currDateRoster.placePlayer(player, pos, false)) {
                        break;
                    }
                }
            }

            optimalRoster[currDay] = currDateRoster;
        }

        return optimalRoster;

    }

}