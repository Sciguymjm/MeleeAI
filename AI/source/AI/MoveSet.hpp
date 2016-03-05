#ifndef MOVE_SET_HPP
#define MOVE_SET_HPP

#include "../Controller.hpp"

class MoveSet {
public:
	MoveSet(Controller*);
	~MoveSet();

	void UpA();
	void UpB();
	void UpTilt();
	void SideB(char);
	void DoubleJump();
	void HoldStick(int);
	void ReleaseStick();
	void LedgeDash(int, int);
	void HitTech();
	void WaveDash(char);
	void Shine();
	void JCShine(bool);
	void Multishine(int);
	void WaveShine(char);
	void ShortHop();
	void SHNair();
	void Grab();
	void JCGrab();
	void Throw(char);
private:
	Controller* m_controller;
};

#endif
