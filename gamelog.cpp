#include <iostream>

#include "gamelog.h"

namespace GameLog {
    GameLog::GameLog() : fg(0), fga(0), fg3(0), fg3a(0), ft(0), fta(0), orb(0), drb(0), ast(0), stl(0), blk(0), tov(0), pf(0) {}
    
    GameLog::GameLog(double fg, double fga, double fg3, double fg3a, double ft, double fta, double orb, double drb, double ast, double stl, double blk, double tov, double pf) :
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
        
    }

    void GameLog::showGameLog(){
        std::cout << "fg" << "\t" <<  "fga" << "\t" <<  "fg3" << "\t" <<  "fg3a" << "\t" <<  "ft" << "\t" <<  "fta" << "\t" <<  "orb" << "\t" <<  "drb" << "\t" <<  "ast" << "\t" <<  "stl" << "\t" <<  "blk" << "\t" <<  "tov" << "\t" <<  "pf" << std::endl;
        std::cout << fg << "\t" <<  fga << "\t" <<  fg3 << "\t" <<  fg3a << "\t" <<  ft << "\t" <<  fta << "\t" <<  orb << "\t" <<  drb << "\t" <<  ast << "\t" <<  stl << "\t" <<  blk << "\t" <<  tov << "\t" <<  pf << std::endl;
    }

    void GameLog::clear() {
        fg = 0;
        fga = 0;
        fg3 = 0;
        fg3a = 0;
        ft = 0;
        fta = 0;
        orb = 0;
        drb = 0;
        ast = 0;
        stl = 0;
        blk = 0;
        tov = 0;
        pf = 0;
    }

    void GameLog::devideAll(int divisor) {
        if (divisor == 0) {
            throw 1;
        }
        fg /= divisor;
        fga /= divisor;
        fg3 /= divisor;
        fg3a /= divisor;
        ft /= divisor;
        fta /= divisor;
        orb /= divisor;
        drb /= divisor;
        ast /= divisor;
        stl /= divisor;
        blk /= divisor;
        tov /= divisor;
        pf /= divisor;
    }
}