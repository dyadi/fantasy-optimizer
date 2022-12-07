#ifndef GAMELOG_H
#define GAMELOG_H

#include <string>
#include <unordered_map>

namespace GameLog {

    class GameLog {

        public:
            GameLog();

            GameLog(int, int, int, int, int, int, int, int, int, int, int, int, int);
            
            GameLog operator+(const GameLog&);

            GameLog& operator+=(const GameLog&);

            std::unordered_map<std::string, double> getStats();

            void showGameLog();


        private:
            int fg;
            int fga;
            int fg3;
            int fg3a;
            int ft;
            int fta;

            int orb;
            int drb;
            
            int ast;
            int stl;
            int blk;
            int tov;
            int pf;

    };
}

#endif