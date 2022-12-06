#include <vector>
#include <unordered_map>
#include <string>


#include "player.h"
#include "athelete.h"


class League {
    public:
        League();

    private:
        // call by constructor, load data
        void load_data();

        std::vector<Player> player_list;
        std::unordered_map<std::string, Athelete> id2athelete_map;

        int weekly_buget;
        
};