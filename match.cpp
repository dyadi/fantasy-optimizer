#include "match.h"

#include <iomanip>
#include "utils/date.h"

#include "optimizer.h"


using date::operator<<;

namespace Match {

    Match::Match(Team::Team* myTeam, Team::Team* oppoTeam, League::League* league) : myTeam(myTeam), oppoTeam(oppoTeam), league(league) {}
    
    Match::Match(std::string myTeamName, std::string oppoTeamName, League::League* league) : league(league) {
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
                std::cout << std::setprecision(4) << cat << "\t" << myFinalStats[cat] << "\t\t" << oppoFinalStats[cat] << std::endl;
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

        auto myResult = optimizer->getOptimalRoster(startDate, myTeam);
        auto oppoResult = optimizer->getOptimalRoster(startDate, oppoTeam);
        for (auto& [dt, ros]: myResult) {
            std::cout << dt;
            ros.showRoster();
        }
        for (auto& [dt, ros]: oppoResult) {
            std::cout << dt;
            ros.showRoster();
        }
        simulate(myResult, myTeam);
        simulate(oppoResult, oppoTeam);

    }


}