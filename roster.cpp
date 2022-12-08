#include "roster.h"

namespace Roster {

    Roster::Roster() {
        
        int defaultArgs[9] {3, 1, 1, 1, 1, 2, 1, 1, 2};

        for (int i = 0; i < 9; ++i){
            playerPlacement[positionTitle[i]] = std::unordered_set<Player::Player*>();
            positionQuota[positionTitle[i]] = defaultArgs[i];
        }
        
    }

    Roster::Roster(int benchSpot, int pgLimit, int sgLimit, int sfLimit, int pfLimit, int cLimit, int gLimit, int fLimit, int utilLimit) {
                        
        int args[9] {benchSpot, pgLimit, sgLimit, sfLimit, pfLimit, cLimit, gLimit, fLimit, utilLimit};
        
        for (int i = 0; i < 9; ++i){
            playerPlacement[positionTitle[i]] = std::unordered_set<Player::Player*>();
            positionQuota[positionTitle[i]] = args[i];
        }
        
    }

    // Roster::Roster(const Roster& rhs) {
    //     playerPlacement = rhs.playerPlacement;
    //     positionQuota = rhs.positionQuota;
    //     positionTitle = rhs.positionTitle;
    // }

    bool Roster::isInRoster(Player::Player* player) {
        for (auto& [_, pp] : playerPlacement) {
            if (pp.count(player)) {
                return true;
            }
        }
        return false;
    }

    bool Roster::addToBench(Player::Player* player) {
        
        if (playerPlacement["BN"].count(player)) {
            return true;
        }

        if (getTotalPlayer() >= getTotalLimit()) {
            return false;
        }
        
        if (dropFromEverySpot(player)) {
            std::cout << "Player already in the roster, moved to bench" << std::endl;
        }

        playerPlacement["BN"].insert(player);

        return true;
        
    }

    void Roster::placeAllToBench() {
        for (auto& [key, placement] : playerPlacement) {
            if (key != "BN") {
                for (auto player : placement) {
                    playerPlacement["BN"].insert(player);
                }
                placement.clear();
            }
        }
    }

    bool Roster::placePlayer(Player::Player* player, std::string position, bool force = true) {

        // std::cout << position << " <<<"<< std::endl;

        if (position == "BN") {
            return addToBench(player);
        }

        if (!isInRoster(player)) {
            return false;
        }
        if (!canPlace(player, position)) {
            return false;
        }
        if (playerPlacement[position].count(player)) {
            return true;
        }
        if (!force && playerPlacement[position].size() >= positionQuota[position]) {
            return false;
        }
        // can place
        // remove from other positions
        dropFromEverySpot(player);
        // remove one player of this position if full
        if (playerPlacement[position].size() >= positionQuota[position]) {
            addToBench(*playerPlacement[position].begin());
        }
        // add to this position
        playerPlacement[position].insert(player);
        return true;
    }

    bool Roster::swapPlayerPlacement(Player::Player* playerReplacer, Player::Player* playerReplacee, bool force = true) {

        if (!isInRoster(playerReplacer) || !isInRoster(playerReplacee)) {
            return false;
        }

        // find position placement of player
        std::string targetPosition, originPosition;
        for (auto& [position, positionSpot]: playerPlacement) {
            if (positionSpot.count(playerReplacee)) {
                targetPosition = position; 
            }
            if (positionSpot.count(playerReplacer)) {
                originPosition = position;
            }
        }
        
        if (targetPosition == originPosition) {
            return true;
        }
        
        // check player avaiblility to play in that position
        if (!canPlace(playerReplacer, targetPosition)) {
            return false;
        }

        if (!force && !canPlace(playerReplacee, originPosition)) {
            return false;
        }

        if (!canPlace(playerReplacee, originPosition)) {
            addToBench(playerReplacee);
        } else {
            playerPlacement[originPosition].insert(playerReplacee);
            playerPlacement[targetPosition].erase(playerReplacee);
        }

        playerPlacement[targetPosition].insert(playerReplacer);
        playerPlacement[originPosition].erase(playerReplacer);
        
        return true;

    }

    bool Roster::setPlayerPlacement(std::unordered_map<std::string, std::unordered_set<Player::Player*>> newPlacement) {
        
        //check if avaible for placement
        for (auto& [pos, playerSet] : newPlacement) {
            if (pos == "BN") {
                continue;
            }
            if (playerSet.size() > positionQuota[pos]) {
                std::cout << "Can't set Player Roster, over quota: " << pos << " " << positionQuota[pos] << std::endl;
                return false;
            }
            for (auto& p:playerSet) {
                if (!canPlace(p, pos)) {
                    return false;
                }
            }
        }

        //placing
        for (auto& [pos, playerSet] : newPlacement) {
            for (auto& p:playerSet) {
                addToBench(p);
                if (!placePlayer(p, pos, false)) {
                    std::cout << "error in setPlayerPlacement" << std::endl;
                    throw 1;
                }
            }
        }
        
        return true;

    }

    bool Roster::dropFromEverySpot(Player::Player* player) {
        bool res = false;

        for (auto& [_, pp] : playerPlacement) {
            if (pp.count(player)) {
                pp.erase(player);
                res = true;
            }
        }
        
        return res;
    }

    void Roster::dropAll() {
        int cnt = 0;
        for (auto& [_, pp] : playerPlacement) {
            pp.clear();
        }
        std::cout << "Drop All: " << cnt << std::endl;
    }

    bool Roster::canPlace(Player::Player* player, std::string position) {
        
        std::unordered_set<std::string> availability {"BN", "UTIL"};

        // available positions
        for (auto& playerPosition: player->getPositions()) {
            availability.insert(playerPosition);
            if (playerPosition == "PG" || playerPosition == "SG") {
                availability.insert("G");
            }
            if (playerPosition == "SF" || playerPosition == "PF") {
                availability.insert("F");
            }
        }

        if (!availability.count(position)) {
            // std::cout << "Can't place in such position." << std::endl;
        }
        
        return (bool) availability.count(position);
    }

    int Roster::getTotalLimit() {
        int limit = 0;
        for (auto& [_, pq] : positionQuota) {
            limit += pq;
        }
        return limit;
    }

    int Roster::getTotalPlayer() {
        int players = 0;
        for (auto& [_, pp] : playerPlacement) {
            players += pp.size();
        }
        return players;
    }

    void Roster::showRoster() {
        std::cout << "==========Show=Roster==========" << std::endl;

        // std::map<std::string, std::unordered_set<Player::Player*>> orderedplayerPlacement;

        // for (auto&[pos, playerSet]:playerPlacement) {
        //     orderedplayerPlacement[pos] = playerSet;
        // }

        for (auto&[pos, playerSet]:playerPlacement) {
            for (auto player:playerSet) {
                std::cout << pos << "\t" << player->getInfo()["playerName"] << std::endl;
            }
        }
        std::cout << std::endl;
    }

    GameLog::GameLog Roster::getSum(std::chrono::sys_days date) {
        GameLog::GameLog gamelog;
        
        for (auto& [key, placement] : playerPlacement) {
            if (key != "BN") {
                for (auto& player : placement) {
                    if (player->willPlay(date)) {
                        gamelog += player->getGameLog(date);
                    }
                }
            }
        }

        return gamelog;
    }

}