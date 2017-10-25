//File "Player.h"

#pragma once

#include "PhysicBody.h"

class Player : public PhysicBody{
public:
	Player(int, int);
	virtual ~Player();

	int get_y();

	virtual void draw_to_buffer() override;
	virtual void clear_from_buffer() override;

	void move_left();
	void move_right();
	void move_up();
	void move_down();
};