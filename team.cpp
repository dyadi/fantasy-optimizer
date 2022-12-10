#include "team.h"
#include "roster.h"
#include <iostream>

namespace Team {
    
    Team::Team(std::string teamName) : teamName(teamName) {}

    std::string Team::getName(){
        return teamName;
    }

    bool Team::addPlayer(std::chrono::sys_days date, Player::Player* player) {
        
        if (!dailyRoster.count(date)){
            Roster::Roster newRoster;
            dailyRoster[date] = newRoster;
        }
        
        if (dailyRoster[date].isInRoster(player)) {
            return false;
        }
        
        return dailyRoster[date].addToBench(player);
    }

    bool Team::dropPlayer(std::chrono::sys_days date, Player::Player* player) {
        
        if (!dailyRoster.count(date)){
            std::cout << "Can't drop aththlete, no roster in that date." << std::endl;
            return false;
        }

        return dailyRoster[date].dropFromEverySpot(player);

    }

    void Team::addPlayerToWatchList(Player::Player* player) {
        watchList.insert(player);
    }

    void Team::dropPlayerFromWatchList(Player::Player* player) {
        watchList.erase(player);
    }

    std::unordered_set<Player::Player*> Team::getWatchList() {
        return watchList;
    }

    bool Team::placePlayerToDate(std::chrono::sys_days date, Player::Player* player, std::string position, bool force = true) {
        return dailyRoster[date].placePlayer(player, position, force);
    }
    
    bool Team::swapPlayerPlacementToDate(std::chrono::sys_days date, Player::Player* playerReplacer, Player::Player* playerReplacee, bool force = true) {
        return dailyRoster[date].swapPlayerPlacement(playerReplacer, playerReplacee, force);
    }

    bool Team::setPlayerPlacementToDate(std::chrono::sys_days date, std::unordered_map<std::string, std::unordered_set<Player::Player*>> newPlacement) {
        return dailyRoster[date].setPlayerPlacement(newPlacement);
    }

    Roster::Roster& Team::getRoster(std::chrono::sys_days date){
        assert(dailyRoster.count(date));
        return dailyRoster[date];
    }

    GameLog::GameLog Team::getDailySum(std::chrono::sys_days date){
        return dailyRoster[date].getSum(date);
    }

    GameLog::GameLog Team::getDailySum(std::chrono::sys_days date, std::map<std::chrono::sys_days, Roster::Roster> optimalRoster){
        return optimalRoster[date].getSum(date);
    }

    GameLog::GameLog Team::getDailySumForecast(std::chrono::sys_days date, std::map<std::chrono::sys_days, Roster::Roster> optimalRoster){
        return optimalRoster[date].getSumForecast(date);
    }

    bool Team::copyRoster(std::chrono::sys_days toDate, std::chrono::sys_days fromDate){
        if (!dailyRoster.count(fromDate)) {
            std::cout << "Can't copy from a date not in dailyRoster" << std::endl;
            return false;
        }
        
        dailyRoster[toDate] = dailyRoster[fromDate];

        return true;
    }

}
