//File "Player.cpp"

#include "Player.h"

void Player::draw_to_buffer(){
	FrameHandler& handle = FrameHandler::get_handler();
	int tmp_x[] = { 0, 2, 1, 0, 2 };
	int tmp_y[] = { 0, 0, 1, 2, 2 };
	for (int i = 0; i < 5; i++)
		handle.fill(m_pivot_x + tmp_x[i], m_pivot_y + tmp_y[i]);
}

void Player::clear_from_buffer(){
	FrameHandler& handle = FrameHandler::get_handler();
	int tmp_x[] = { 0, 2, 1, 0, 2 };
	int tmp_y[] = { 0, 0, 1, 2, 2 };
	for (int i = 0; i < 5; i++)
		handle.clear(m_pivot_x + tmp_x[i], m_pivot_y + tmp_y[i]);
}

Player::Player(int x, int y) : PhysicBody(x, y), m_point(0){}

Player::~Player(){
	clear_from_buffer();
}

int Player::get_point() {
	return m_point;
}

void Player::move_left(){
	FrameHandler::get_handler().lock();
	clear_from_buffer();
	PhysicBody::move_left();
	draw_to_buffer();
	FrameHandler::get_handler().unlock();
}

void Player::move_right(){
	FrameHandler::get_handler().lock();
	clear_from_buffer();
	PhysicBody::move_right();
	draw_to_buffer();
	FrameHandler::get_handler().unlock();
}

void Player::move_up(){
	FrameHandler::get_handler().lock();
	clear_from_buffer();
	if (m_pivot_y == 1) {
		m_pivot_y = MAP_HEIGHT - 4;
		m_point++;
	}
	else
		m_pivot_y -= 4;
	draw_to_buffer();
	FrameHandler::get_handler().unlock();
}

void Player::move_down(){
	FrameHandler::get_handler().lock();
	clear_from_buffer();
	if (m_pivot_y == MAP_HEIGHT - 4)
		m_pivot_y = 1;
	else
		m_pivot_y += 4;
	draw_to_buffer();
	FrameHandler::get_handler().unlock();
}