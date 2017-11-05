//File "Player.h"

#pragma once

#include "PhysicBody.h"

class Player : public PhysicBody{
private:
	int m_point;
public:
	Player(int, int);
	virtual ~Player();

	int get_point();

	virtual void draw_to_buffer() override;
	virtual void clear_from_buffer() override;

	void move_left();
	void move_right();
	void move_up();
	void move_down();
};