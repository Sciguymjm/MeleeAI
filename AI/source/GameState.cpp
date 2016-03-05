#include "Global.hpp"
#include "GameState.hpp"

#include <string>
#include <sstream>
GameState* GameState::m_instance = nullptr;

GameState* GameState::Instance() {
    if (m_instance == nullptr) {
        m_instance = new GameState();
    }
    return m_instance;
}  

void GameState::WaitFrames(int n) {
    for (int i = 0; i < n; i++) {
        WaitFrame();
    }
}

void GameState::WaitFrame() {
    GameState* gs = GameState::Instance();
    int cur_frame = gs->frame_count;

    while (cur_frame == gs->frame_count) {
        GLOBAL_SLEEP(4)
    }
}

std::string GameState::GetString() {
	GameState* gs = GameState::Instance();
	std::stringstream fmt;
	fmt << "Stocks: "
			<< gs->p1_stocks
			<< " "
			<< gs->p2_stocks
			<< " | Percents: "
			<< gs->p1_percent
			<< " "
			<< gs->p2_percent
			<< "\n"
			<< "State: "
			<< gs->p2_action_state
			<< " | Air: "
			<< gs->p2_in_air;
	return fmt.str();
}
