//File "GameManager.cpp"

#include "GameManager.h"

GameManager::GameManager(){
	m_lane_num = (MAP_HEIGHT - 1) / 4 - 1;
	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < m_lane_num; i++){
		m_lanes.emplace_back(new Lane(1 + 4 * i));
		m_speed_per_frame.push_back(rand() % MIN_SPEED + 1);
		m_traffic_interval.push_back(rand() % (MAX_INTERVAL - MIN_INTERVAL) + MIN_INTERVAL);
	}

	int temp = MAX_INTERVAL < MIN_SPEED ? MIN_SPEED : MAX_INTERVAL;
	m_max_frame = 1;
	for (int i = 2; i < temp; i++)
		m_max_frame *= i;
	m_frame_count = 0;

	p_player = new Player(rand() % (MAP_WIDTH - 4) + 1, MAP_HEIGHT - 4);
	m_game_over = false;
}

GameManager::~GameManager(){
	for (int i = 0; i < m_lane_num; i++)
		delete m_lanes[i];
	delete p_player;
}

Player* GameManager::get_player(){
	return p_player;
}

bool GameManager::game_over() const{
	return m_game_over;
}

void GameManager::start(){
	for (int i = 0; i < m_lane_num; i++)
		m_lanes[i]->draw_to_buffer();
}

void GameManager::update(){
	while (!m_game_over){
		m_frame_count = (m_frame_count + 1) % m_max_frame;
		for (int i = 0; i < m_lane_num; i++){
			if (m_frame_count % m_traffic_interval[i] == 0)
				m_lanes[i]->switch_light();
			m_lanes[i]->clear_from_buffer();
			if (m_frame_count % m_speed_per_frame[i] == 0)
				m_lanes[i]->move();
			if (m_lanes[i]->collide_with(*p_player)){
				m_game_over = true;
				break;
			}
			m_lanes[i]->draw_to_buffer();
		}
		FrameHandler::get_handler().render();
		Sleep(50);
	}
}

void GameManager::stop(){
	m_game_over = true;
}