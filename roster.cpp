#include "roster.h"

namespace Roster {

    Roster::Roster() {}

    Roster::Roster(int benchSpot, int pgLimit, int sgLimit, int sfLimit, int pfLimit, int cLimit, int gLimit, int fLimit, int utilLimit) {
                        
        int args[9] {benchSpot, pgLimit, sgLimit, sfLimit, pfLimit, cLimit, gLimit, fLimit, utilLimit};
        
        for (int i = 0; i < 9; ++i){
            playerPlacement[positionTitle[i]] = std::unordered_set<Player::Player*>();
            positionQuota[positionTitle[i]] = args[i];
        }
        
    }

    // Roster::Roster(const Roster& rhs) {}

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

    bool Roster::placePlayer(Player::Player* player, std::string position, bool force = true) {
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

    bool canPlace(Player::Player* player, std::string position) {
        
        std::unordered_set<std::string> availability {"BN", "UTIL"};

        // aviable positions
        for (auto& playerPosition: player->getPositions()) {
            availability.insert(playerPosition);
            if (playerPosition == "PG" || playerPosition == "SG") {
                availability.insert("G");
            }
            if (playerPosition == "SF" || playerPosition == "PF") {
                availability.insert("F");
            }
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

}