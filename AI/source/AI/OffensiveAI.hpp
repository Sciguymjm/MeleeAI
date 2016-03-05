#ifndef OFFENSIVE_AI_HPP
#define OFFENSIVE_AI_HPP

#include "RecoveryBot/RecoveryBot.hpp"
#include "RecoveryBot/RecoveryFox.hpp"

#include "LedgeBot.hpp"
#include "TechBot.hpp"
#include "DIBot.hpp"

class OffensiveAI : public AI {
public:
	OffensiveAI(Controller*);
    ~OffensiveAI();

    void MakeMove();
    void WaitForTrigger();
    bool TriggerEvents();
    void SelectCharacter();

private:
    RecoveryBot* m_recovery_bot;
    LedgeBot* m_ledge_bot;
    DIBot* m_di_bot;
    TechBot* m_tech_bot;
	bool selected;
	Controller* m_controller;
};

#endif
