#include "../Global.hpp"
#include "DefensiveAI.hpp"
#include "../GameState.hpp"
#include <iostream>

DefensiveAI::DefensiveAI(Controller* controller) :
		AI(controller) {
	selected = false;
	m_recovery_bot = new RecoveryFox(controller);
	m_ledge_bot = new LedgeBot(controller);
	m_di_bot = new DIBot(controller);
	m_tech_bot = new TechBot(controller);
	m_controller = controller;
}

DefensiveAI::~DefensiveAI() {
	delete m_recovery_bot;
	delete m_ledge_bot;
	delete m_di_bot;
	delete m_tech_bot;
}

void DefensiveAI::MakeMove() {
	GLOBAL_WAIT_FRAMES(30);
	m_move_set->Multishine(30);
	WaitForTrigger();
	if (OnLedge()) {
		m_ledge_bot->GetUp();
	} else if (InHitlag()) {
		m_di_bot->DI();
	} else if (IsOffStage()) {
		WaitForHitstun();
		try {
			m_recovery_bot->Recover();
		} catch (ActionInterruptedException e) {
		}
	} else if (TechSituation()) {
		m_tech_bot->Tech();
	} else if (PlayerNear() && m_game_state->p2_action_state == 14 && m_game_state->p2_in_air == 0)
	{
		m_move_set->WaveDash(Xcoord() > m_game_state->p1_x);
	}
	return;
}

void DefensiveAI::WaitForTrigger() {
	while (!TriggerEvents()) {
		std::cout << "P1 Action State: " << m_game_state->p2_action_state << "\n";
		if (m_game_state->p2_action_state == 0x0D) { //respawning
			m_move_set->HoldStick(270); //fast fall, TODO: put in moveset
			WaitAndReact(20);
			m_move_set->ReleaseStick();
		}
		else if (CoinFlip(0.05) && !TriggerEvents() && m_game_state->p2_action_state == 14 && m_game_state->p2_in_air == 0) // 14 = standing
		{
			if (!IsNearLedge())
				m_move_set->WaveDash(CoinFlip(0.5) ? 'R' : 'L');
			else if (NearWhatLedge() == 1)
				m_move_set->WaveDash('L');
			else
				m_move_set->WaveDash('R');
		}
		GLOBAL_WAIT_FRAMES(1)
	}
}

bool DefensiveAI::TriggerEvents() {
	return IsOffStage() || OnLedge() || InHitstun() || InHitlag() || PlayerNear();
}

void DefensiveAI::SelectCharacter() {
	std::cout << "Moving up...\n";
	m_controller->Stick(1, 100);
	std::cout << "Waiting...\n";
	GLOBAL_SLEEP(4 * 112)
	std::cout << "Stopping...\n";
	m_controller->Stick(0, 100);
	m_controller->Press('A');
	std::cout << "Done.\n";
	GLOBAL_SLEEP(16)
	m_controller->Release('A');
}
