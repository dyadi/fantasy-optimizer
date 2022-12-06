#include <vector>
#include <string>
#include <chrono>
#include <map>

#include "gamelog.h"

class Athelete {

    public:
        Athelete();

        getAccGameLog();

    private:
        std::string id;
        std::map<std::chrono::time_point<std::chrono::system_clock>, GameLog> date2gamelog;

};