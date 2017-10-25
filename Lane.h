//File "Lane.h"

#pragma once

#include "Obstacle.h"
#include <vector>
#include <ctime>
#include <algorithm>

class Lane{
private:
	vector<Obstacle*> m_obstacles;
	bool m_traffic_light;

	static const int MAX_OBSTACLE = 7;
public:
	Lane(int);
	~Lane();

	void draw_to_buffer();
	void clear_from_buffer();

	void switch_light();

	void move();
	bool collide_with(const PhysicBody&);
};