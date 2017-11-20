//File "Lane.cpp"

#include "Lane.h"

Lane::Lane(int level, int order){
	m_order = order;

	m_start.reserve((MAP_WIDTH - 4) / 4 - 1);
	for (int i = 0; i < (MAP_WIDTH - 4) / 4 - 1; i++)
		m_start.push_back(i);
	random_shuffle(m_start.begin(), m_start.end());

	m_obstacles.reserve(level);
	int type = rand() % 4;
	m_dir = Direction(rand() % 2);
	m_traffic_light = nullptr;
	if (type == 0) {
		for (int i = 0; i < level; i++)
			m_obstacles.push_back(new Bird(m_start[i] * 4 + 2, 1 + 4 * order, m_dir));
	}
	else if (type == 1) {
		for (int i = 0; i < level; i++)
			m_obstacles.push_back(new Dinosaur(m_start[i] * 4 + 2, 1 + 4 * order, m_dir));
	}
	else if (type == 2) {
		for (int i = 0; i < level; i++)
			m_obstacles.push_back(new Truck(m_start[i] * 4 + 2, 1 + 4 * order, m_dir));
		m_traffic_light = new TrafficLight(m_dir == Direction::Left ? 1 : MAP_WIDTH - 2, 1 + 4 * order);
	}
	else {
		for (int i = 0; i < level; i++)
			m_obstacles.push_back(new Car(m_start[i] * 4 + 2, 1 + 4 * order, m_dir));
		m_traffic_light = new TrafficLight(m_dir == Direction::Left ? 1 : MAP_WIDTH - 2, 1 + 4 * order);
	}
	
	m_move_lock = true;
	m_frame_count = 0;
	m_frame_per_move = rand() % (MAX_FRAME_PER_MOVE - MIN_FRAME_PER_MOVE) + MIN_FRAME_PER_MOVE;
}

Lane::Lane(const Lane& lane) {
	m_order = lane.m_order;
	m_dir = lane.m_dir;
	m_start = lane.m_start;
	m_traffic_light = lane.m_traffic_light ? new TrafficLight(*lane.m_traffic_light): nullptr;
	for (auto i = lane.m_obstacles.begin(); i != lane.m_obstacles.end(); i++) {
		m_obstacles.push_back((*i)->clone());
	}
	m_move_lock = lane.m_move_lock;
	m_frame_count = lane.m_frame_count;
	m_frame_per_move = lane.m_frame_per_move;
}

Lane::~Lane(){
	clear_from_buffer();
	for (unsigned int i = 0; i < m_obstacles.size(); i++)
		delete m_obstacles[i];
	if (m_traffic_light)
		delete m_traffic_light;
}

Lane& Lane::operator=(const Lane& lane) {
	for (unsigned int i = 0; i < m_obstacles.size(); i++)
		if(m_obstacles[i])
			delete m_obstacles[i];
	m_obstacles.clear();
	if (m_traffic_light)
		delete m_traffic_light;

	m_dir = lane.m_dir;
	m_order = lane.m_order;
	m_start = lane.m_start;
	m_traffic_light = lane.m_traffic_light ? new TrafficLight(*lane.m_traffic_light) : nullptr;
	for (auto i = lane.m_obstacles.begin(); i != lane.m_obstacles.end(); i++) {
		m_obstacles.push_back((*i)->clone());
	}
	m_move_lock = lane.m_move_lock;
	m_frame_count = lane.m_frame_count;
	m_frame_per_move = lane.m_frame_per_move;

	return *this;
}

void Lane::draw_to_buffer(){
	Symbol s = m_traffic_light ? Symbol::Red : Symbol::Green;
	int y = m_order * 4 + 1;
	if (m_traffic_light)
		m_traffic_light->draw_to_buffer();
	for (unsigned int i = 0; i < m_obstacles.size(); i++)
		m_obstacles[i]->draw_to_buffer();
	m_frame_count++;
	if (m_frame_count == m_frame_per_move) {
		m_frame_count = 0;
		m_move_lock = false;
	}
}
void Lane::clear_from_buffer(){
	int y = m_order * 4 + 1;
	if (m_traffic_light)
		m_traffic_light->clear_from_buffer();
	for (unsigned int i = 0; i < m_obstacles.size(); i++)
		m_obstacles[i]->clear_from_buffer();
}

void Lane::move(){
	if ((m_traffic_light && m_traffic_light->is_red()) || m_move_lock)
		return;
	for (unsigned int i = 0; i < m_obstacles.size(); i++)
		m_obstacles[i]->move();
	m_move_lock = true;
}

bool Lane::collide_with(const PhysicBody& p){
	for (unsigned int i = 0; i < m_obstacles.size(); i++)
		if (m_obstacles[i]->collide_with(p))
			return true;
	return false;
}