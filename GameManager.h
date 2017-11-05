//File "GameManager.h"

#pragma once

#include "Player.h"
#include "Lane.h"
#include <thread>

class GameManager{
private:
	int m_lane_num;
	vector<Lane*> m_lanes;

	static const int MIN_SPEED = 5;
	vector<int> m_speed_per_frame;

	static const int MAX_INTERVAL = 300;
	static const int MIN_INTERVAL = 200;
	vector<int> m_traffic_interval;

	vector<int> m_frame_count;
	vector<int> m_max_frame;

	Player* p_player;
	bool m_game_over;
	bool m_is_paused;
	int m_level;

	GameManager* p_reset_ver;
	GameManager* p_load_ver;
public:
	GameManager();
	GameManager(const GameManager&);
	~GameManager();

	GameManager& operator=(const GameManager&);

	Player* get_player();
	bool game_over() const;
	bool is_paused() const;

	int menu();

	void init();
	void loop();

	void level_up();

	void run();
	void pause(HANDLE);
	void resume(HANDLE);
	void reset(HANDLE);
};