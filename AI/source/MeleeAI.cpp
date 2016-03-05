#include "Global.hpp"
#include "GameState.hpp"
#include "MemReader.hpp"
#include "PipeController.hpp"
#include "AI/AI.hpp"

#include "AI/OffensiveAI.hpp"
#include <iostream>
#include <thread>

int main(int argc, const char* argv[]) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " /path/to/dolphin-emu\n";
	} else {
		std::thread mem_reader_thread = MemReader::Init(argv[1]);
		PipeController* controller = new PipeController(argv[1]);
		OffensiveAI* ai = new OffensiveAI(controller);
		GameState* game_state = GameState::Instance();
		//controller->Stick(0, 0);
		GLOBAL_SLEEP(4)
		if (game_state->p1_stocks == 0 && game_state->p2_stocks == 0)
			ai->SelectCharacter();
		while (1) {
			//TODO: check for pause here as well, need to add mem address for that
			while (!game_state->in_game) {
				GLOBAL_WAIT_FRAMES(1)
			}
			ai->MakeMove();
		}
	}
}
