//File "Lane.cpp"

#include "Lane.h"

Lane::Lane(int y){
	int num = rand() % MAX_OBSTACLE + 1;
	vector<int> start_x;
	start_x.reserve((MAP_WIDTH - 2) / 4);
	for (int i = 0; i < (MAP_WIDTH - 2) / 4; i++)
		start_x.push_back(i);
	random_shuffle(start_x.begin(), start_x.end());
	m_obstacles.reserve(num);
	int type = rand() % 4;
	Direction dir = Direction(rand() % 2);
	for (int i = 0; i < num; i++){
		if (type == 0)
			m_obstacles.emplace_back(new Bird(start_x[i] * 4 + 1, y, dir));
		if (type == 1)
			m_obstacles.emplace_back(new Car(start_x[i] * 4 + 1, y, dir));
		if (type == 2)
			m_obstacles.emplace_back(new Truck(start_x[i] * 4 + 1, y, dir));
		if (type == 3)
			m_obstacles.emplace_back(new Dinosaur(start_x[i] * 4 + 1, y, dir));
	}
	
	m_traffic_light = false;
}

Lane::~Lane(){
	for (int i = 0; i < m_obstacles.size(); i++)
		delete m_obstacles[i];
}

void Lane::draw_to_buffer(){
	for (int i = 0; i < m_obstacles.size(); i++)
		m_obstacles[i]->draw_to_buffer();
}
void Lane::clear_from_buffer(){
	for (int i = 0; i < m_obstacles.size(); i++)
		m_obstacles[i]->clear_from_buffer();
}

void Lane::switch_light(){
	m_traffic_light = !m_traffic_light;
}

void Lane::move(){
	if (m_traffic_light)
		return;
	for (int i = 0; i < m_obstacles.size(); i++)
		m_obstacles[i]->move();
}

bool Lane::collide_with(const PhysicBody& p){
	for (int i = 0; i < m_obstacles.size(); i++)
		if (m_obstacles[i]->collide_with(p))
			return true;
	return false;
}