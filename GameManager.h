//File "GameManager.h"

#pragma once

#include "Player.h"
#include "Lane.h"
#include <thread>

class GameManager{
private:
	int m_lane_num;
	vector<Lane*> m_lanes;

	Player* p_player;
	bool m_game_over;
	bool m_is_paused;
	int m_level;

	GameManager* p_reset_ver;
	GameManager* p_load_ver;

	Player* get_player();
	bool game_over() const;
	bool is_paused() const;

	int menu();

	void init();
	void loop();

	void level_up(HANDLE);

	void pause(HANDLE);
	void resume(HANDLE);
	void reset(HANDLE);
public:
	GameManager();
	GameManager(const GameManager&);
	~GameManager();

	GameManager& operator=(const GameManager&);

	void run();
};