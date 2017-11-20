//File "Lane.h"

#pragma once

#include "Obstacle.h"
#include "TrafficLight.h"
#include <vector>
#include <ctime>
#include <algorithm>

class Lane{
private:
	vector<Obstacle*> m_obstacles;
	vector<int> m_start;
	
	TrafficLight* m_traffic_light;
	Direction m_dir;
	int m_order;

	bool m_move_lock;
	int m_frame_per_move;
	int m_frame_count;
	static const int MAX_FRAME_PER_MOVE = 8;
	static const int MIN_FRAME_PER_MOVE = 2;
public:
	Lane(int, int);
	Lane(const Lane& lane);
	~Lane();

	Lane& operator=(const Lane& lane);

	void draw_to_buffer();
	void clear_from_buffer();

	void move();
	bool collide_with(const PhysicBody&);
};