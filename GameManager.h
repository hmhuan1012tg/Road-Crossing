//File "GameManager.h"

#pragma once

#include "Player.h"
#include "Lane.h"

class GameManager{
private:
	int m_lane_num;
	vector<Lane*> m_lanes;

	static const int MIN_SPEED = 5;
	vector<int> m_speed_per_frame;

	static const int MAX_INTERVAL = 20;
	static const int MIN_INTERVAL = 10;
	vector<int> m_traffic_interval;

	unsigned long long m_frame_count;
	unsigned long long m_max_frame;

	Player* p_player;
	bool m_game_over;
public:
	GameManager();
	~GameManager();

	Player* get_player();
	bool game_over() const;

	void start();
	void update();
	void stop();
};