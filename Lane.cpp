//File "Lane.cpp"

#include "Lane.h"

Lane::Lane(int level, int order){
	m_order = order;
	m_start.reserve((MAP_WIDTH - 4) / 4 - 1);
	for (int i = 0; i < (MAP_WIDTH - 4) / 4 - 1; i++)
		m_start.push_back(i);
	random_shuffle(m_start.begin(), m_start.end());
	m_obstacles.reserve(level);
	m_type = ObstacleType(rand() % 4);
	m_dir = Direction(rand() % 2);
	for (int i = 0; i < level; i++){
		if (m_type == ObstacleType::Bird)
			m_obstacles.emplace_back(new Bird(m_start[i] * 4 + 2, 1 + 4 * order, m_dir));
		if (m_type == ObstacleType::Car)
			m_obstacles.emplace_back(new Car(m_start[i] * 4 + 2, 1 + 4 * order, m_dir));
		if (m_type == ObstacleType::Truck)
			m_obstacles.emplace_back(new Truck(m_start[i] * 4 + 2, 1 + 4 * order, m_dir));
		if (m_type == ObstacleType::Dinosaur)
			m_obstacles.emplace_back(new Dinosaur(m_start[i] * 4 + 2, 1 + 4 * order, m_dir));
	}
	
	m_traffic_light = false;
}

Lane::Lane(const Lane& lane) {
	m_order = lane.m_order;
	m_dir = lane.m_dir;
	m_start = lane.m_start;
	m_traffic_light = lane.m_traffic_light;
	m_type = lane.m_type;
	for (auto i = lane.m_obstacles.begin(); i != lane.m_obstacles.end(); i++) {
		if (m_type == ObstacleType::Bird)
			m_obstacles.emplace_back(new Bird((*i)->get_x(), (*i)->get_y(), (*i)->get_dir()));
		if (m_type == ObstacleType::Car)
			m_obstacles.emplace_back(new Car((*i)->get_x(), (*i)->get_y(), (*i)->get_dir()));
		if (m_type == ObstacleType::Truck)
			m_obstacles.emplace_back(new Truck((*i)->get_x(), (*i)->get_y(), (*i)->get_dir()));
		if (m_type == ObstacleType::Dinosaur)
			m_obstacles.emplace_back(new Dinosaur((*i)->get_x(), (*i)->get_y(), (*i)->get_dir()));
	}
}

Lane::~Lane(){
	clear_from_buffer();
	for (unsigned int i = 0; i < m_obstacles.size(); i++)
		delete m_obstacles[i];
}

Lane& Lane::operator=(const Lane& lane) {
	for (unsigned int i = 0; i < m_obstacles.size(); i++)
		if(m_obstacles[i])
			delete m_obstacles[i];
	m_obstacles.clear();

	m_dir = lane.m_dir;
	m_order = lane.m_order;
	m_start = lane.m_start;
	m_traffic_light = lane.m_traffic_light;
	m_type = lane.m_type;
	for (auto i = lane.m_obstacles.begin(); i != lane.m_obstacles.end(); i++) {
		if (m_type == ObstacleType::Bird)
			m_obstacles.emplace_back(new Bird((*i)->get_x(), (*i)->get_y(), (*i)->get_dir()));
		if (m_type == ObstacleType::Car)
			m_obstacles.emplace_back(new Car((*i)->get_x(), (*i)->get_y(), (*i)->get_dir()));
		if (m_type == ObstacleType::Truck)
			m_obstacles.emplace_back(new Truck((*i)->get_x(), (*i)->get_y(), (*i)->get_dir()));
		if (m_type == ObstacleType::Dinosaur)
			m_obstacles.emplace_back(new Dinosaur((*i)->get_x(), (*i)->get_y(), (*i)->get_dir()));
	}

	return *this;
}

void Lane::draw_to_buffer(){
	Symbol s = m_traffic_light ? Symbol::Red : Symbol::Green;
	int y = m_order * 4 + 1;
	if (m_dir == Direction::Left)
		FrameHandler::get_handler().fill(1, y, s);
	else
		FrameHandler::get_handler().fill(MAP_WIDTH - 2, y, s);
	for (unsigned int i = 0; i < m_obstacles.size(); i++)
		m_obstacles[i]->draw_to_buffer();
}
void Lane::clear_from_buffer(){
	int y = m_order * 4 + 1;
	if (m_dir == Direction::Left)
		FrameHandler::get_handler().fill(1, y, Symbol::Border);
	else
		FrameHandler::get_handler().fill(MAP_WIDTH - 2, y, Symbol::Border);
	for (unsigned int i = 0; i < m_obstacles.size(); i++)
		m_obstacles[i]->clear_from_buffer();
}

void Lane::switch_light(){
	m_traffic_light = !m_traffic_light;
}

void Lane::move(){
	if (m_traffic_light)
		return;
	for (unsigned int i = 0; i < m_obstacles.size(); i++)
		m_obstacles[i]->move();
}

bool Lane::collide_with(const PhysicBody& p){
	for (unsigned int i = 0; i < m_obstacles.size(); i++)
		if (m_obstacles[i]->collide_with(p))
			return true;
	return false;
}