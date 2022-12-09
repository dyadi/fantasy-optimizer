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

    std::map<std::chrono::sys_days, Roster::Roster> GreedyOptimizer::getOptimalRosterForecast(std::chrono::sys_days startDate, Roster::Roster proposedRoster) {

        std::map<std::chrono::sys_days, Roster::Roster> optimalRoster;

        std::chrono::sys_days monday = startDate - (date::weekday{startDate} - date::Monday);
        std::chrono::sys_days sunday = monday + std::chrono::days{6};

        auto currDateRoster = proposedRoster;

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
            
            // currDateRoster.showRoster();
            optimalRoster[currDay] = currDateRoster;
        }
        

        return optimalRoster;

    }

    StreamOptimizer::StreamOptimizer(Match::Match* match) {
        this->match = match;
    }

    Player::Player* StreamOptimizer::getOptimalStreamer(std::chrono::sys_days startDate, Team::Team* team, std::string playerIdToDrop) {
        
        Optimizer::GreedyOptimizer greedyOptimizer(match);

        auto playerDrop = &(match->league->idToPlayer[playerIdToDrop]);
        auto bestStreamer = playerDrop;
        
        double bestScore = match->getForecastScore(startDate, team->getRoster(startDate), &greedyOptimizer);

        // std::cout << bestStreamer->getInfo()["playerName"] << ":>>>" << bestScore << std::endl;

        for (auto& candidate : team->getWatchList()) {

            if (match->league->idToTeamNumber[candidate->getInfo()["playerId"]] != -1) {
                continue;
            }

            Roster::Roster replacedRoster = team->getRoster(startDate);
            replacedRoster.dropFromEverySpot(playerDrop);
            replacedRoster.addToBench(candidate);
            double score = match->getForecastScore(startDate, replacedRoster, &greedyOptimizer);
            // std::cout << candidate->getInfo()["playerName"] << ":>>>" << score << std::endl;
            
            if (score >= bestScore) {
                bestScore = score;
                bestStreamer = candidate;
            }
        
        }

        return bestStreamer;

    }

    std::map<std::chrono::sys_days, Roster::Roster> StreamOptimizer::getOptimalRoster(std::chrono::sys_days startDate, Team::Team* team) {
        
        Optimizer::GreedyOptimizer greedyOptimizer(match);

        std::map<std::chrono::sys_days, Roster::Roster> optimalRoster;

        std::chrono::sys_days monday = startDate - (date::weekday{startDate} - date::Monday);
        std::chrono::sys_days sunday = monday + std::chrono::days{6};

        for (auto currDay = monday; currDay < startDate; currDay += std::chrono::days{1}) {
            optimalRoster[currDay] = team->dailyRoster[currDay];
        }

        auto currDateRoster = team->dailyRoster[startDate];

        std::unordered_map<Player::Player*, std::chrono::sys_days> addedToRoster;
        std::unordered_map<Player::Player*, std::chrono::sys_days> dropFromRosterWaiver;

        for (auto currDay = startDate; currDay <= sunday; currDay += std::chrono::days{1}) {

            
            // clear waiver constrain
            std::unordered_map<Player::Player*, std::chrono::sys_days> newDropFromRosterWaiver;
            for (auto& [player, waiverDate]: dropFromRosterWaiver) {
                if (waiverDate > currDay) {
                    newDropFromRosterWaiver[player] = waiverDate;
                } else {
                    team->addPlayerToWatchList(player);
                }
            }
            dropFromRosterWaiver = newDropFromRosterWaiver;

            // do greedy if no enough budget
            if ((team == match->myTeam && match->myBudget == 0) || (team == match->oppoTeam && match->oppoBudget == 0)) {
                // auto greedyOptimalRoster = greedyOptimizer.getOptimalRoster(currDay, team);
                auto greedyOptimalRoster = greedyOptimizer.getOptimalRosterForecast(currDay, currDateRoster);
                for (; currDay <= sunday; currDay += std::chrono::days{1}) {
                    optimalRoster[currDay] = greedyOptimalRoster[currDay];
                }
                break;
            }

            // find player to drop (player with lowest score)
            Player::Player* playerToDrop = nullptr;
            for (auto& [player, dateAdded]: addedToRoster) {
                if (!playerToDrop || player->getAvgStats()["score"] < playerToDrop->getAvgStats()["score"]) {
                    playerToDrop = player;
                }
            }
            for (auto& [_, placement] : currDateRoster.playerPlacement) {
                for (auto player : placement) {
                    if (!playerToDrop || player->getAvgStats()["score"] < playerToDrop->getAvgStats()["score"]) {
                        playerToDrop = player;
                    }
                }
            }

            // get optimal streamer
            auto optimalStreamer = getOptimalStreamer(currDay, team, playerToDrop->getInfo()["playerId"]);

            if (optimalStreamer == playerToDrop) {
                // do nothing
                // std::cout << "optimalStreamer == playerToDrop\n";
            } else {
                // replace player
                // std::cout << "optimalStreamer != playerToDrop\n";
                std::cout << "Date: " << currDay << "\tDrop: " << playerToDrop->getInfo()["playerName"] <<  "\tAdd: " <<  optimalStreamer->getInfo()["playerName"] << "\n";

                dropFromRosterWaiver[playerToDrop] = currDay + std::chrono::days{match->league->waiverDelay};
                addedToRoster[optimalStreamer] = currDay;
                team->dropPlayerFromWatchList(optimalStreamer);

                currDateRoster.dropFromEverySpot(playerToDrop);
                currDateRoster.addToBench(optimalStreamer);
                if (team == match->myTeam) {
                    match->myBudget -= 1;
                }
                if (team == match->oppoTeam) {
                    match->oppoBudget -= 1;
                }
            }

            // do greedy optimization
            currDateRoster = greedyOptimizer.getOptimalRosterForecast(currDay, currDateRoster)[currDay];

            optimalRoster[currDay] = currDateRoster;
        }

        for (auto& [player, waiverDate]: dropFromRosterWaiver) {
            team->addPlayerToWatchList(player);
        }

        return optimalRoster;

    }

}