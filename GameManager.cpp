//File "GameManager.cpp"

#include "GameManager.h"

GameManager::GameManager(){
	m_lane_num = (MAP_HEIGHT - 1) / 4 - 1;
	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < m_lane_num; i++){
		m_lanes.emplace_back(new Lane(1, i));
		
		int speed = rand() % MIN_SPEED + 1;
		int trf_intvl = rand() % (MAX_INTERVAL - MIN_INTERVAL) + MIN_INTERVAL;
		
		m_speed_per_frame.push_back(speed);
		m_traffic_interval.push_back(trf_intvl);
		
		m_max_frame.push_back(speed * trf_intvl);
		m_frame_count.push_back(0);
	}

	p_player = new Player(rand() % (MAP_WIDTH - 6) + 2, MAP_HEIGHT - 4);
	m_game_over = m_is_paused = false;
	m_level = 1;

	p_load_ver = p_reset_ver = nullptr;
}

GameManager::GameManager(const GameManager& gm) {
	m_lane_num = gm.m_lane_num;
	for (auto i = gm.m_lanes.begin(); i != gm.m_lanes.end(); i++)
		m_lanes.emplace_back(new Lane(*(*i)));

	m_speed_per_frame = gm.m_speed_per_frame;
	m_traffic_interval = gm.m_traffic_interval;
	
	m_frame_count = gm.m_frame_count;
	m_max_frame = gm.m_max_frame;
	
	m_game_over = gm.m_game_over;
	m_is_paused = gm.m_is_paused;
	m_level = gm.m_level;
	p_player = new Player(*(gm.p_player));

	p_load_ver = gm.p_load_ver;
	p_reset_ver = gm.p_reset_ver;
}

GameManager::~GameManager(){
	for (int i = 0; i < m_lane_num; i++)
		delete m_lanes[i];
	delete p_player;
}

GameManager& GameManager::operator=(const GameManager& gm) {
	for (int i = 0; i < m_lane_num; i++)
		if(m_lanes[i])
			delete m_lanes[i];
	m_lanes.clear();

	if(p_player)
		delete p_player;

	if (p_load_ver != gm.p_load_ver && p_load_ver != &gm && p_load_ver)
		delete p_load_ver;
	if (p_reset_ver != gm.p_reset_ver && p_reset_ver != &gm && p_reset_ver)
		delete p_reset_ver;

	m_lane_num = gm.m_lane_num;
	for (auto i = gm.m_lanes.begin(); i != gm.m_lanes.end(); i++)
		m_lanes.emplace_back(new Lane(*(*i)));

	m_speed_per_frame = gm.m_speed_per_frame;
	m_traffic_interval = gm.m_traffic_interval;

	m_frame_count = gm.m_frame_count;
	m_max_frame = gm.m_max_frame;

	m_game_over = gm.m_game_over;
	m_is_paused = gm.m_is_paused;
	m_level = gm.m_level;
	p_player = new Player(*(gm.p_player));

	p_load_ver = gm.p_load_ver;
	p_reset_ver = gm.p_reset_ver;

	return *this;
}

Player* GameManager::get_player(){
	return p_player;
}

bool GameManager::game_over() const{
	return m_game_over;
}

bool GameManager::is_paused() const {
	return m_is_paused;
}

int GameManager::menu() {
	goToXY(MENU_X, MENU_Y);
	cout << "Road Crossing";
	
	int choice = 0;
	const char *msg[3] = { "Start New Game", "Load Saved Game", "Quit" };

	while (true) {
		if (_kbhit()) {
			char c = _getch();
			if (c == 'w')
				choice = (choice + 2) % 3;
			if (c == 's')
				choice = (choice + 1) % 3;
			if (c == 13)
				break;
		}

		for (int i = 0; i < 3; i++) {
			goToXY(MENU_X, MENU_Y + 2 * (i + 1));
			if (i == choice)
				setColor(ColorCode_MenuChoice);
			cout << msg[i];
			if (i == choice)
				setColor(ColorCode_White);
		}
	}

	system("cls");

	return choice;
}

void GameManager::init(){
	for (int i = 0; i < m_lane_num; i++)
		m_lanes[i]->draw_to_buffer();
	p_player->draw_to_buffer();
	p_reset_ver = new GameManager(*this);
}

void GameManager::loop(){
	while (!m_game_over){
		for (int i = 0; i < m_lane_num; i++){
			m_frame_count[i] = (m_frame_count[i] + 1) % m_max_frame[i];
			if (m_frame_count[i] % m_traffic_interval[i] == 0)
				m_lanes[i]->switch_light();
			m_lanes[i]->clear_from_buffer();
			if (m_frame_count[i] % m_speed_per_frame[i] == 0)
				m_lanes[i]->move();
			if (m_lanes[i]->collide_with(*p_player))
				m_game_over = true;
			m_lanes[i]->draw_to_buffer();
		}
		FrameHandler::get_handler().render();	

		goToXY(MAP_WIDTH / 2, MAP_HEIGHT + 3);
		cout << p_player->get_point();

		Sleep(16);
	}
}

void GameManager::level_up() {
	m_level++;
	FrameHandler::get_handler().lock();
	for (int i = 0; i < m_lane_num; i++)
		if (m_lanes[i])
			delete m_lanes[i];
	m_lanes.clear();

	srand(static_cast<unsigned int>(time(0)));
	for (int i = 0; i < m_lane_num; i++) {
		m_lanes.emplace_back(new Lane(m_level, i));

		int speed = rand() % MIN_SPEED + 1;
		int trf_intvl = rand() % (MAX_INTERVAL - MIN_INTERVAL) + MIN_INTERVAL;

		m_speed_per_frame.push_back(speed);
		m_traffic_interval.push_back(trf_intvl);

		m_max_frame.push_back(speed * trf_intvl);
		m_frame_count.push_back(0);
	}
	FrameHandler::get_handler().unlock();
}

void GameManager::run() {
	while (menu() != 0) {
		goToXY(MENU_X, MENU_Y);
		cout << "Choose again";
		goToXY(MENU_X, MENU_Y + 2);
		cout << "Press any key to return to menu";
		_getch();
		system("cls");
	}

	thread t([&] { init(); loop(); });

	int prev_point = p_player->get_point();
	while (!m_game_over) {
		if (_kbhit()) {
			char c = _getch();
			if (c == 'd')
				p_player->move_right();
			if (c == 'a')
				p_player->move_left();
			if (c == 'w')
				p_player->move_up();
			if (c == 's')
				p_player->move_down();
			if (c == 'r')
				reset(t.native_handle());
			if (c == 'p') {
				if (m_is_paused)
					resume(t.native_handle());
				else
					pause(t.native_handle());
			}
		}
		if (p_player->get_point() - prev_point == 1) {
			pause(t.native_handle());
			level_up();
			prev_point = p_player->get_point();
			resume(t.native_handle());
		}
	}

	t.join();
}

void GameManager::pause(HANDLE t){
	if (!m_is_paused) {
		pauseGame(t);
		m_is_paused = true;
	}
}

void GameManager::resume(HANDLE t) {
	if (m_is_paused) {
		resumeGame(t);
		m_is_paused = false;
	}
}

void GameManager::reset(HANDLE t) {
	pause(t);
	bool pre_paused = false;
	if (p_reset_ver) {
		pre_paused = p_reset_ver->m_is_paused;
		*this = *p_reset_ver;
	}
	if (!pre_paused)
		m_is_paused = true;
	resume(t);
	init();
}