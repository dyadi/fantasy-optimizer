#include "gamelog.h"

namespace GameLog {
    GameLog::GameLog() : fg(0), fga(0), fg3(0), fg3a(0), ft(0), fta(0), orb(0), drb(0), ast(0), stl(0), blk(0), tov(0), pf(0) {}
    
    GameLog::GameLog(int fg, int fga, int fg3, int fg3a, int ft, int fta, int orb, int drb, int ast, int stl, int blk, int tov, int pf) :
        fg(fg), fga(fga), fg3(fg3), fg3a(fg3a), ft(ft), fta(fta), orb(orb), drb(drb), ast(ast), stl(stl), blk(blk), tov(tov), pf(pf) {}

    GameLog GameLog::operator+(const GameLog& rhs) {
        GameLog res(
            fg + rhs.fg,
            fga + rhs.fga,
            fg3 + rhs.fg3,
            fg3a + rhs.fg3a,
            ft + rhs.ft,
            fta + rhs.fta,
            orb + rhs.orb,
            drb + rhs.drb,
            ast + rhs.ast,
            stl + rhs.stl,
            blk + rhs.blk,
            tov + rhs.tov,
            pf + rhs.pf
        );
        
        return res;
    }

    GameLog& GameLog::operator+=(const GameLog& rhs) {
        this->fg += rhs.fg;
        this->fga += rhs.fga;
        this->fg3 += rhs.fg3;
        this->fg3a += rhs.fg3a;
        this->ft += rhs.ft;
        this->fta += rhs.fta;

        this->orb += rhs.orb;
        this->drb += rhs.drb;
        
        this->ast += rhs.ast;
        this->stl += rhs.stl;
        this->blk += rhs.blk;
        this->tov += rhs.tov;
        this->pf += rhs.pf;
        
        return *this;
    }

    std::unordered_map<std::string, double> GameLog::getStats(){
        
        std::unordered_map<std::string, double> ret;

        ret["fgm"] = (double) fg;
        ret["fgpct"] = (double) fg / fga;
        ret["ftm"] = (double) ft / fta;
        ret["ftpct"] = (double) ft / fta;
        ret["3pm"] = (double) fg3;
        ret["3ppct"] = (double) fg3 / fg3a;

        ret["pts"] = fg * 2.0 + fg3 + ft;
        ret["astovr"] = (double) ast / tov;
        ret["drb"] = (double) drb;
        ret["orb"] = (double) orb;
        ret["trb"] = (double) orb + drb;
        ret["ast"] = (double) ast;
        ret["stl"] = (double) stl;
        ret["blk"] = (double) blk;
        ret["tov"] = (double) tov;
        
        ret["dd"] = ((ret["pts"] >= 10.0) + (ret["trb"] >= 10.0) + (ret["ast"] >= 10.0) + (ret["blk"] >= 10.0) + (ret["stl"] >= 10.0) >= 1.5) ? 1.0 : 0.0;
        
        return ret;

        // const std::string cata[16] = {
        //     "fgm",
        //     "fgpct",
        //     "ftm",
        //     "ftpct",
        //     "3pm",
        //     "3ppct",
        //     "pts",
        //     "astovr",
        //     "drb",
        //     "orb",
        //     "trb",
        //     "ast",
        //     "stl",
        //     "blk",
        //     "tov",
        //     "dd"
        // }
    }
}