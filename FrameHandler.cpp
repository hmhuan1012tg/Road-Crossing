//File "FrameHandler.cpp"

#include "FrameHandler.h"

FrameHandler::FrameHandler(){
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++){
			if (i % 4 == 0 || j == 0 || j == MAP_WIDTH - 1)
				s_temp[i * MAP_WIDTH + j] = s_next[i * MAP_WIDTH + j] = Symbol::Border;
			else
				s_temp[i * MAP_WIDTH + j] = s_next[i * MAP_WIDTH + j] = Symbol::Black;
			s_current[i * MAP_WIDTH + j] = Symbol::Black;
		}

	m_lock_level = 0;
}

FrameHandler& FrameHandler::get_handler(){
	static FrameHandler handler;
	return handler;
}

void FrameHandler::fill(int x, int y){
	s_temp[y*MAP_WIDTH + x] = Symbol::White;
}

void FrameHandler::clear(int x, int y){
	s_temp[y*MAP_WIDTH + x] = Symbol::Black;
}

void FrameHandler::lock(){
	m_lock_level++;
}

void FrameHandler::unlock(){
	m_lock_level = m_lock_level == 0 ? 0 : (m_lock_level - 1);
}

void FrameHandler::render(){
	if (m_lock_level == 0)
		memcpy(s_next, s_temp, MAP_HEIGHT * MAP_WIDTH);
	for (int i = 0; i < MAP_HEIGHT; i++)
		for (int j = 0; j < MAP_WIDTH; j++)
			if (s_next[i * MAP_WIDTH + j] != s_current[i* MAP_WIDTH + j]){
				Symbol s = s_next[i * MAP_WIDTH + j];
				goToXY(j, i);
				if (s == Symbol::Black)
					cout << " ";
				else if (s == Symbol::Border)
					cout << "*";
				else{
					setColor(ColorCode_MenuChoice);
					cout << " ";
					setColor(ColorCode_White);
				}
				s_current[i * MAP_WIDTH + j] = s;
			}
}