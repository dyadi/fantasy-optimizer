#include "match.h"

#include "utils/date.h"

#include "optimizer.h"

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
        
        std::cout << "My team:" << myTeam->getName() << std::endl;
        myResult.showGameLog();
        
        std::cout << "Opponent team:" << oppoTeam->getName() << std::endl;
        oppoResult.showGameLog();

        //To do, show score and winner

    }

    void Match::createWeekRosterBaseOnModay() {

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

    bool Match::simulate(std::map<std::chrono::sys_days, Roster::Roster> optimalRoster) {
        
        std::chrono::sys_days monday = league->currDate - (date::weekday{league->currDate} - date::Monday);
        std::chrono::sys_days sunday = monday + std::chrono::days{6};

        // ensure every day has a roster
        for (auto currDay = monday; currDay <= sunday; currDay += std::chrono::days{1}) {
            if (!optimalRoster.count(currDay) || !oppoTeam->dailyRoster.count(currDay)) {
                return false;
            }
        }

        myResult.clear();
        oppoResult.clear();

        // sum up everdays stats
        for (auto currDay = monday; currDay <= sunday; currDay += std::chrono::days{1}) {
            myResult += optimalRoster[currDay].getSum(currDay);
            oppoResult += oppoTeam->getDailySum(currDay);
        }

        // showResults();
        
        return true;

    }

    void Match::applyOptimizer(std::chrono::sys_days startDate, Optimizer::BaseOptimizer* optimizer) {

        auto result = optimizer->getOptimalRoster(startDate);
        for (auto& [dt, ros]: result) {
            ros.showRoster();
        }
        simulate(result);

    }


}