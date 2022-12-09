#ifndef GAMELOG_H
#define GAMELOG_H

#include <string>
#include <unordered_map>

namespace GameLog {

    class GameLog {

        public:
            GameLog();

            GameLog(double, double, double, double, double, double, double, double, double, double, double, double, double);
            
            GameLog operator+(const GameLog&);

            GameLog& operator+=(const GameLog&);

            std::unordered_map<std::string, double> getStats();

            void showGameLog();

            void clear();

            void devideAll(int);

        private:
            double fg;
            double fga;
            double fg3;
            double fg3a;
            double ft;
            double fta;

            double orb;
            double drb;
            
            double ast;
            double stl;
            double blk;
            double tov;
            double pf;

            // std::unordered_map<std::string, int> coreStats;
            // std::string coreStatsTitle[13] = {"fg", "fga", "fg3", "fg3a", "ft", "fta", "orb", "drb", "ast", "stl", "blk", "tov", "pf"}

    };
}

#endif