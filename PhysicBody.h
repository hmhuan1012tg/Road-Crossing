//File "PhysicBody.h"

#pragma once

#include "FrameHandler.h"

class PhysicBody{
protected:
	int m_pivot_x;
	int m_pivot_y;
public:
	PhysicBody(int, int);
	virtual ~PhysicBody();

	virtual void draw_to_buffer() = 0;
	virtual void clear_from_buffer() = 0;

	bool collide_with(const PhysicBody& p) const;

	void move_right();
	void move_left();
};