#include "roster.h"

namespace Roster {

    Roster::Roster() {}

    bool Roster::isInRoster(Athlete::Athlete* athlete) {
        return (
            pgRoster.count(athlete) || sgRoster.count(athlete) ||
            gRoster.count(athlete) || sfRoster.count(athlete) ||
            pfRoster.count(athlete) || fRoster.count(athlete) ||
            utilRoster.count(athlete) || bench.count(athlete)
        );
    }

    int Roster::getTotalLimit() {
        return sgLimit + pgLimit + gLimit + sfLimit + pfLimit + fLimit + utilLimit;
    }

    int Roster::getTotalPlayers() {
        return (
            pgRoster.size() + sgRoster.size() +
            gRoster.size() + sfRoster.size() +
            pfRoster.size() + fRoster.size() +
            utilRoster.size() + bench.size()
        );
    }

    bool Roster::addToBench(Athlete::Athlete* athlete) {
        
        if (this->getTotalLimit() <= this->getTotalPlayers()) {
            return false;
        }
        
        if (dropFromEverySpot(athlete)) {
            std::cout << "Player already in the roster, moved to bench" << std::endl;
        }

        bench.insert(athlete);

        return true;
        
    }

    bool Roster::dropFromEverySpot(Athlete::Athlete* athlete) {
        if (pgRoster.count(athlete)) {
            pgRoster.erase(athlete);
            return true;
        }
        if (sgRoster.count(athlete)) {
            sgRoster.erase(athlete);
            return true;
        }
        if (gRoster.count(athlete)) {
            gRoster.erase(athlete);
            return true;
        }
        if (sfRoster.count(athlete)) {
            sfRoster.erase(athlete);
            return true;
        }
        if (pfRoster.count(athlete)) {
            pfRoster.erase(athlete);
            return true;
        }
        if (fRoster.count(athlete)) {
            fRoster.erase(athlete);
            return true;
        }
        if (utilRoster.count(athlete)) {
            utilRoster.erase(athlete);
            return true;
        }
        if (bench.count(athlete)) {
            bench.erase(athlete);
            return true;
        }
        return false;
    }

}