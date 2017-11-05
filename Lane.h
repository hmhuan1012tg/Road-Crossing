//File "Lane.h"

#pragma once

#include "Obstacle.h"
#include <vector>
#include <ctime>
#include <algorithm>

enum class ObstacleType{
	Bird, Dinosaur, Car, Truck,
};

class Lane{
private:
	vector<Obstacle*> m_obstacles;
	vector<int> m_start;
	bool m_traffic_light;
	ObstacleType m_type;
	Direction m_dir;
	int m_order;
public:
	Lane(int, int);
	Lane(const Lane& lane);
	~Lane();

	Lane& operator=(const Lane& lane);

	void draw_to_buffer();
	void clear_from_buffer();

	void switch_light();

	void move();
	bool collide_with(const PhysicBody&);
};