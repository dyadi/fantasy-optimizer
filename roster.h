#ifndef ROSTER_H
#define ROSTER_H

#include <iostream>
#include <unordered_set>

#include "athlete.h"

namespace Roster {
    
    class Roster {

        public:
            Roster();
            bool isInRoster(Athlete::Athlete*);
            bool addToBench(Athlete::Athlete*);
            bool dropFromEverySpot(Athlete::Athlete*);
            int getTotalPlayers();
            int getTotalLimit();

        private:
            std::unordered_set<Athlete::Athlete*> pgRoster;
            std::unordered_set<Athlete::Athlete*> sgRoster;
            std::unordered_set<Athlete::Athlete*> gRoster;
            std::unordered_set<Athlete::Athlete*> sfRoster;
            std::unordered_set<Athlete::Athlete*> pfRoster;
            std::unordered_set<Athlete::Athlete*> fRoster;
            std::unordered_set<Athlete::Athlete*> utilRoster;
            std::unordered_set<Athlete::Athlete*> bench;

            int sgLimit;
            int pgLimit;
            int gLimit;
            int sfLimit;
            int pfLimit;
            int fLimit;
            int utilLimit;
            int benchSpot;

    };

}

#endif