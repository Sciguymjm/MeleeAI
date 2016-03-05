#ifndef AI_HPP
#define AI_HPP

#include "../GameState.hpp"
#include "MoveSet.hpp"

#include <random>
#include <exception>

class ActionInterruptedException : public std::exception {};

class AI {
public:
    bool CoinFlip(double);
    bool IsOffStage();
    bool InHitstun();
    bool InHitlag();
    bool InAir();
    bool IsStanding();
    bool PlayerNear();
    double PlayerDistance();
    double LedgeDistance();
    void WaitForHitstun();
    bool TechSituation();
    double StageLimit();
    void WaitAndReact(int);
    bool OnLedge();
    bool IsNearLedge();
    int NearWhatLedge();
    int StageSide();
    double Xcoord();
    double Ycoord();
    double Uniform(double,double);

    AI(Controller*);
    ~AI();
    
public:
    MoveSet* m_move_set;
    GameState* m_game_state;
    std::default_random_engine* m_generator;
};

#endif
