#include "../Global.hpp"
#include "MoveSet.hpp"
#include "../PipeController.hpp"
#include <unistd.h>

//TODO: Have moves return the number of frames they waited

MoveSet::MoveSet(Controller* controller) {
	m_controller = controller;
}

MoveSet::~MoveSet() {
	delete m_controller;
}

void MoveSet::UpB() {
	m_controller->Stick(1, 90);
	GLOBAL_WAIT_FRAMES(1)
	m_controller->Press('B');
	GLOBAL_WAIT_FRAMES(1)
	m_controller->Release('B');
	m_controller->Stick(0, 0);
}

void MoveSet::SideB(char dir) {
	if (dir == 'R') {
		m_controller->Stick(1, 0);
	} else {
		m_controller->Stick(1, 180);
	}
	m_controller->Press('B');
	GLOBAL_WAIT_FRAMES(1)
	m_controller->Release('B');
	m_controller->Stick(0, 0);
}

void MoveSet::UpA() {
	m_controller->Stick(1, 90);
	GLOBAL_WAIT_FRAMES(1)
	m_controller->Press('A');
	GLOBAL_WAIT_FRAMES(1)
	m_controller->Release('A');
	m_controller->Stick(0, 0);
}

void MoveSet::UpTilt() {
	m_controller->Stick(0.5, 90);
	GLOBAL_WAIT_FRAMES(1)
	m_controller->Press('A');
	GLOBAL_WAIT_FRAMES(1)
	m_controller->Release('A');
	m_controller->Stick(0, 0);
}

void MoveSet::DoubleJump() {
	m_controller->Press('X');
	GLOBAL_WAIT_FRAMES(1)
	m_controller->Release('X');
}

void MoveSet::HoldStick(int dir) {
	m_controller->Stick(1, dir);
}

void MoveSet::ReleaseStick() {
	m_controller->Stick(0, 0);
}

void MoveSet::LedgeDash(int id, int deg) {
	m_controller->Stick(1, 270);
	GLOBAL_WAIT_FRAMES(2)
	m_controller->Stick(0, 0);
	m_controller->Press('X');
	GLOBAL_WAIT_FRAMES(2)
	m_controller->Release('X');
	GLOBAL_WAIT_FRAMES(3)
	m_controller->Stick(1, deg);
	m_controller->Press('L');
	GLOBAL_WAIT_FRAMES(2)
	m_controller->Stick(0, 0);
	m_controller->Release('L');
}

void MoveSet::HitTech() {
	m_controller->Press('L');
	GLOBAL_WAIT_FRAMES(1)
	m_controller->Release('L');
}

void MoveSet::WaveDash(char dir) {
	m_controller->Press('X');
	GLOBAL_WAIT_FRAMES(4);
	switch (dir) {
	case 'L':
		m_controller->Stick(1, 205);
		break;
	case 'R':
		m_controller->Stick(1, 335);
		break;
	case 'D':
		m_controller->Stick(1, 270);
		break;
	}
	m_controller->Press('L');
	GLOBAL_WAIT_FRAMES(2)
	m_controller->Release('X');
	m_controller->Release('L');
	m_controller->Stick(0, 0);
	GLOBAL_WAIT_FRAMES(8)
	// 10 frame lag total
	// std::cout << "Wavedashed.\n";
}

void MoveSet::Shine() {

}

void MoveSet::JCShine(bool fullhop) {
	Shine(); // one frame delay          : 1
	GLOBAL_WAIT_FRAMES(3); //            : 2-4
	m_controller->Press('X'); //         : 4
	GLOBAL_WAIT_FRAMES(fullhop ? 4 : 1)
	//: 5
	m_controller->Release('X'); //       : 5
}

void MoveSet::Multishine(int count) {
	for (int x = 0; x < count; x++) {
		JCShine(false); //      : 1-5
		GLOBAL_WAIT_FRAMES(2); //: 6-7
		Shine(); //             : 7-8
		GLOBAL_WAIT_FRAMES(3); //: 9-11
	}
}

void MoveSet::WaveShine(char dir) {
	m_controller->Stick(1, 270);
	m_controller->Press('B');
	GLOBAL_WAIT_FRAMES(5);
	m_controller->Release('B');
	WaveDash(dir);
}

void MoveSet::ShortHop() {
	m_controller->Press('X');
	GLOBAL_WAIT_FRAMES(2);
	m_controller->Release('X');
}

void MoveSet::SHNair() {
	ShortHop();
	GLOBAL_WAIT_FRAMES(1);
	m_controller->Press('A');
	GLOBAL_WAIT_FRAMES(1);
	m_controller->Release('A');
}

void MoveSet::Grab() {
	m_controller->Press('Z');
	GLOBAL_WAIT_FRAMES(10)
	m_controller->Release('Z');
	GLOBAL_WAIT_FRAMES(20)
}

void MoveSet::JCGrab() {
	m_controller->Press('X');
	GLOBAL_WAIT_FRAMES(2)
	m_controller->Press('Z');
	GLOBAL_WAIT_FRAMES(10)
	m_controller->Release('X');
	m_controller->Release('Z');
	GLOBAL_WAIT_FRAMES(20)
}

void MoveSet::Throw(char dir) {
	switch (dir) {
	case 'U':
		m_controller->Stick(1, 90);
		break;
	case 'L':
		m_controller->Stick(1, 180);
		break;
	case 'R':
		m_controller->Stick(1, 0);
		break;
	case 'D':
		m_controller->Stick(1, 270);
	}
	GLOBAL_WAIT_FRAMES(20)
	m_controller->Stick(0, 0);
}
