#include "match.h"

#include <iomanip>
#include "utils/date.h"

#include "optimizer.h"

using date::operator<<;

namespace Match {

    Match::Match(Team::Team* myTeam, Team::Team* oppoTeam, League::League* league) : myTeam(myTeam), oppoTeam(oppoTeam), league(league), myBudget(league->weeklyBudget), oppoBudget(league->weeklyBudget) {}
    
    Match::Match(std::string myTeamName, std::string oppoTeamName, League::League* league) : league(league), myBudget(league->weeklyBudget), oppoBudget(league->weeklyBudget) {
        for(auto& team : league->teamList) {
            if(team.getName() == myTeamName) {
                myTeam = &team;
            }
            if(team.getName() == oppoTeamName) {
                oppoTeam = &team;
            }
            // myTeam = &league->teamList[i];
        }

    }

    void Match::showResults() {
        auto myFinalStats = myResult.getStats();
        auto oppoFinalStats = oppoResult.getStats();

        std::cout << "===Match=Show=Result===" << std::endl;
        std::cout << "\t" << myTeam->getName() << "\t" << oppoTeam->getName() << std::endl;
        for (auto& [cat, _]:myFinalStats) {
            if (league->categories[cat]) {
                if (cat != "tov" && cat != "to") {
                    if (myFinalStats[cat] > oppoFinalStats[cat]) {
                        std::cout << std::setprecision(3) << cat << "\t" << myFinalStats[cat] << " v\t\t" << oppoFinalStats[cat] << std::endl;
                    } else if ((myFinalStats[cat] < oppoFinalStats[cat])) {
                        std::cout << std::setprecision(3) << cat << "\t" << myFinalStats[cat] << "\t\t" << oppoFinalStats[cat] << " v" << std::endl;
                    } else {
                        std::cout << std::setprecision(3) << cat << "\t" << myFinalStats[cat] << "\t\t" << oppoFinalStats[cat] << std::endl;

                    }
                } else {
                    if (myFinalStats[cat] < oppoFinalStats[cat]) {
                        std::cout << std::setprecision(3) << cat << "\t" << myFinalStats[cat] << " v\t\t" << oppoFinalStats[cat] << std::endl;
                    } else if (myFinalStats[cat] > oppoFinalStats[cat]) {
                        std::cout << std::setprecision(3) << cat << "\t" << myFinalStats[cat] << "\t\t" << oppoFinalStats[cat] << " v" << std::endl;
                    } else {
                        std::cout << std::setprecision(3) << cat << "\t" << myFinalStats[cat] << "\t\t" << oppoFinalStats[cat] << std::endl;
                    }

                }
                
            }
        }


    }

    void Match::createWeekRosterBaseOnMonday() {

        std::chrono::sys_days monday = league->currDate - (date::weekday{league->currDate} - date::Monday);
        std::chrono::sys_days sunday = monday + std::chrono::days{6};

        for (auto currDay = monday + std::chrono::days{1}; currDay <= sunday; currDay += std::chrono::days{1}) {
            myTeam->copyRoster(currDay, monday);
            oppoTeam->copyRoster(currDay, monday);
        }

    }

    bool Match::simulate() {
        
        std::chrono::sys_days monday = league->currDate - (date::weekday{league->currDate} - date::Monday);
        std::chrono::sys_days sunday = monday + std::chrono::days{6};

        // ensure every day has a roster
        for (auto currDay = monday; currDay <= sunday; currDay += std::chrono::days{1}) {
            if (!myTeam->dailyRoster.count(currDay) || !oppoTeam->dailyRoster.count(currDay)) {
                return false;
            }
        }

        myResult.clear();
        oppoResult.clear();

        // sum up everdays stats
        for (auto currDay = monday; currDay <= sunday; currDay += std::chrono::days{1}) {
            myResult += myTeam->getDailySum(currDay);
            oppoResult += oppoTeam->getDailySum(currDay);
        }

        // showResults();
        
        return true;

    }

    bool Match::simulate(std::map<std::chrono::sys_days, Roster::Roster> optimalRoster, Team::Team* team) {
        
        std::chrono::sys_days monday = league->currDate - (date::weekday{league->currDate} - date::Monday);
        std::chrono::sys_days sunday = monday + std::chrono::days{6};

        // ensure every day has a roster
        for (auto currDay = monday; currDay <= sunday; currDay += std::chrono::days{1}) {
            if (!optimalRoster.count(currDay)) {
                return false;
            }
        }

        if(team->getName() == myTeam->getName()) {
            myResult.clear();
            for (auto currDay = monday; currDay <= sunday; currDay += std::chrono::days{1}) {
                myResult += optimalRoster[currDay].getSum(currDay);
        
            }
        }

        if (team->getName() == oppoTeam->getName()) {
            oppoResult.clear();
            for (auto currDay = monday; currDay <= sunday; currDay += std::chrono::days{1}) {
                oppoResult += optimalRoster[currDay].getSum(currDay);
            }
        }

        if (team->getName() != myTeam->getName() && team->getName() != oppoTeam->getName()) {
            return false;
        }
        
        return true;

    }

    void Match::applyOptimizer(std::chrono::sys_days startDate, Optimizer::BaseOptimizer* optimizer) {

        auto myOptimalRoster = optimizer->getOptimalRoster(startDate, myTeam);
        // std::cout << "My optimization done\n";
        auto oppoOptimalRoster = optimizer->getOptimalRoster(startDate, oppoTeam);
        // std::cout << "Oppo optimization done\n";
        for (auto& [dt, ros]: myOptimalRoster) {
            std::cout << dt;
            ros.showRoster();
        }
        // for (auto& [dt, ros]: oppoOptimalRoster) {
        //     std::cout << dt;
        //     ros.showRoster();
        // }
        simulate(myOptimalRoster, myTeam);
        simulate(oppoOptimalRoster, oppoTeam);

    }

    void Match::applyOptimizer(std::chrono::sys_days startDate, Optimizer::BaseOptimizer* myOptimizer, Optimizer::BaseOptimizer* oppoOptimizer) {

        auto myOptimalRoster = myOptimizer->getOptimalRoster(startDate, myTeam);
        auto oppoOptimalRoster = oppoOptimizer->getOptimalRoster(startDate, oppoTeam);
        for (auto& [dt, ros]: myOptimalRoster) {
            std::cout << dt;
            ros.showRoster();
        }
        // for (auto& [dt, ros]: oppoOptimalRoster) {
        //     std::cout << dt;
        //     ros.showRoster();
        // }
        simulate(myOptimalRoster, myTeam);
        simulate(oppoOptimalRoster, oppoTeam);

    }

    double Match::getForecastScore(std::chrono::sys_days startDate, Roster::Roster proposedRoster, Optimizer::GreedyOptimizer* optimizer) {
        

        std::chrono::sys_days monday = league->currDate - (date::weekday{league->currDate} - date::Monday);
        std::chrono::sys_days sunday = monday + std::chrono::days{6};

        GameLog::GameLog currResult;
        
        for (auto currDay = monday; currDay < startDate; currDay += std::chrono::days{1}) {
            currResult += myTeam->getRoster(currDay).getSum(currDay);
        }

        auto forecastDailyRoster = optimizer->getOptimalRosterForecast(startDate, proposedRoster);

        for (auto currDay = startDate; currDay <= sunday; currDay += std::chrono::days{1}) {
            currResult += myTeam->getDailySumForecast(currDay, forecastDailyRoster);
        }

        auto oppoOptimalRoster = optimizer->getOptimalRoster(startDate, oppoTeam);

        GameLog::GameLog oppoResultForecase;
        for (auto currDay = monday; currDay <= sunday; currDay += std::chrono::days{1}) {
            oppoResultForecase += oppoOptimalRoster[currDay].getSumForecast(currDay);
        }
        
        auto proposedStatsForecast = currResult.getStats();
        auto oppoStatsForecast = oppoResultForecase.getStats();

        // currResult.showGameLog();
        // oppoResult.showGameLog();
        return getScore(proposedStatsForecast, oppoStatsForecast);

    }

    double Match::getScore(std::unordered_map<std::string, double> myStats, std::unordered_map<std::string, double> oppoStats) {
        
        double score = 0;
        for(auto& [cat, _]: myStats) {
            double diffpct = (myStats[cat] - oppoStats[cat]) / (std::max(myStats[cat],oppoStats[cat]) + 0.001);
            diffpct = std::min(std::max(diffpct, -0.2), 0.2);
            score += diffpct;
        }

        return score;
    }
}