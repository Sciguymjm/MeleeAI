#include "../Global.hpp"
#include "OffensiveAI.hpp"
#include "../GameState.hpp"
#include <iostream>

OffensiveAI::OffensiveAI(Controller* controller) :
		AI(controller) {
	selected = false;
	m_recovery_bot = new RecoveryFox(controller);
	m_ledge_bot = new LedgeBot(controller);
	m_di_bot = new DIBot(controller);
	m_tech_bot = new TechBot(controller);
	m_controller = controller;
}

OffensiveAI::~OffensiveAI() {
	delete m_recovery_bot;
	delete m_ledge_bot;
	delete m_di_bot;
	delete m_tech_bot;
}

void OffensiveAI::MakeMove() {
	WaitForTrigger();
	if (OnLedge()) {
		std::cout << "Getting up!\n";
		m_ledge_bot->GetUp();
	} else if (IsOffStage()) {
		WaitForHitstun();
		try {
			std::cout << "Recovering!\n";
			m_recovery_bot->Recover();
		} catch (ActionInterruptedException e) {
		}
	} else if (TechSituation()) {
		std::cout << "Teching!\n";
		m_tech_bot->Tech();
	} else if (CoinFlip(0.01) && PlayerDistance() < 20 && !InAir()) {
		std::cout << "Flipped 0.05, flipping again.\n";
		if (abs(m_game_state->p1_y - Ycoord()) <= 10) {
			if (CoinFlip(0.5) && LedgeDistance() > 5) {
				m_controller->Stick(0.2,
						Xcoord() < m_game_state->p1_x ? 0 : 180); // pivot to grab
				GLOBAL_WAIT_FRAMES(3);
				m_move_set->ReleaseStick();
				m_move_set->JCGrab(); // state: 212 - Miss / 216 - grab
				std::cout << "Grab state:" << m_game_state->p2_action_state
						<< "\n";
				if (m_game_state->p2_action_state == 216) { // Successful grab
					m_move_set->Throw('U');

					GLOBAL_WAIT_FRAMES(5);
					if (PlayerDistance() < 20) {
						if (CoinFlip(0.5)) {
							std::cout << "UpA!\n";
							m_move_set->UpA();
						} else {
							std::cout << "UpAir!\n";
							m_controller->Press('X');
							GLOBAL_WAIT_FRAMES(10);
							m_controller->Release('X');
							GLOBAL_WAIT_FRAMES(10);
							m_move_set->UpA();
							GLOBAL_WAIT_FRAMES(40);
						}
					}
				}
			} else {
				m_move_set->ReleaseStick();
				std::cout << "SHNAIRing!\n";
				m_move_set->SHNair();
				m_move_set->HoldStick(Xcoord() < m_game_state->p1_x ? 0 : 180);
				GLOBAL_WAIT_FRAMES(20);
				m_move_set->ReleaseStick();
			}
		} else if (abs(m_game_state->p1_y - Ycoord()) <= 20) { // up tilt
			m_move_set->UpTilt();
		}
	} else if (PlayerDistance() < 10 && !InAir()) {
		// GLOBAL_WAIT_FRAMES(4);
		std::cout << "Waveshining!\n";
		m_move_set->WaveShine(Xcoord() < m_game_state->p1_x ? 'R' : 'L');
		GLOBAL_WAIT_FRAMES(6)
	} else if (IsNearLedge() && !InAir() && !IsOffStage() && Ycoord() > -1) {
		std::cout << "Wavedashing away from ledge!" << "LD:" << LedgeDistance()
				<< " | Y:" << Ycoord() << "\n";
		// GLOBAL_WAIT_FRAMES(20)
		if (NearWhatLedge() == 1)
			m_move_set->WaveDash('L');
		else
			m_move_set->WaveDash('R');
	}
}

void OffensiveAI::WaitForTrigger() {
	while (!TriggerEvents()) {
		if (m_game_state->p2_action_state == 0x0D) { //respawning
			m_move_set->HoldStick(270); //fast fall, TODO: put in moveset
			WaitAndReact(20);
			m_move_set->ReleaseStick();
		} else if (!InAir()) {
			m_move_set->HoldStick(Xcoord() < m_game_state->p1_x ? 0 : 180); // move toward player

		}
//		else if (CoinFlip(0.05) && !TriggerEvents() && m_game_state->p2_action_state == 14 && m_game_state->p2_in_air == 0) // 14 = standing
//		{
//			if (!IsNearLedge())
//				m_move_set->WaveDash(CoinFlip(0.5));
//			else if (NearWhatLedge() == 1)
//				m_move_set->WaveDash(false);
//			else
//				m_move_set->WaveDash(true);
//		}
		GLOBAL_WAIT_FRAMES(1)
	}
}

bool OffensiveAI::TriggerEvents() {
	return IsOffStage() || OnLedge() || PlayerDistance() < 20 || IsNearLedge();
}

void OffensiveAI::SelectCharacter() {
	std::cout << "Moving up...\n";
	m_controller->Stick(1, 100);
	std::cout << "Waiting...\n";
	GLOBAL_SLEEP(4 * 112)
	std::cout << "Stopping...\n";
	m_controller->Stick(0, 100);
	GLOBAL_SLEEP(32)
	m_controller->Press('A');
	std::cout << "Done.\n";
	GLOBAL_SLEEP(32)
	m_controller->Release('A');
}
