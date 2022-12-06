#include <vector>
#include <unordered_map>
#include <string>


// #include "player.h"
#include "athlete.h"

namespace League {

    class League {
        public:
            League();
            void load_data();
            void showAthlete(std::string);
            int getAthleteNum();

        private:
            // call by constructor, load data
            

            // std::vector<Player> player_list;
            std::unordered_map<std::string, Athlete::Athlete> id2athlete_map;

            int weekly_buget;
            
    };
}
