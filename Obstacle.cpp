//File "Obstacle.cpp"

#include "Obstacle.h"

/*---------------------------------Obstacle----------------------------------------*/
Obstacle::Obstacle(int x, int y, Direction dir) : PhysicBody(x, y), m_dir(dir){}

Obstacle::~Obstacle(){}

void Obstacle::move(){
	if (m_dir == Direction::Left)
		move_left();
	else
		move_right();
}

/*----------------------------------Dinosaur---------------------------------------*/
void Dinosaur::draw_to_buffer(){
	FrameHandler& handle = FrameHandler::get_handler();
	int tmp_x[2][5] = { { 0, 0, 1, 1, 2 }, { 2, 2, 1, 1, 0 } };
	int tmp_y[2][5] = { { 0, 1, 1, 2, 2 }, { 0, 1, 1, 2, 2 } };
	int choice = (int)m_dir;
	for (int i = 0; i < 5; i++)
		handle.fill(m_pivot_x + tmp_x[choice][i], m_pivot_y + tmp_y[choice][i]);
}

void Dinosaur::clear_from_buffer(){
	FrameHandler& handle = FrameHandler::get_handler();
	int tmp_x[2][5] = { { 0, 0, 1, 1, 2 }, { 2, 2, 1, 1, 0 } };
	int tmp_y[2][5] = { { 0, 1, 1, 2, 2 }, { 0, 1, 1, 2, 2 } };
	int choice = (int)m_dir;
	for (int i = 0; i < 5; i++)
		handle.clear(m_pivot_x + tmp_x[choice][i], m_pivot_y + tmp_y[choice][i]);
}

Dinosaur::Dinosaur(int x, int y, Direction dir) : Obstacle(x, y, dir){}

Dinosaur::~Dinosaur(){}

/*----------------------------------Bird---------------------------------------*/
void Bird::draw_to_buffer(){
	FrameHandler& handle = FrameHandler::get_handler();
	int tmp_x[] = { 0, 2, 1 };
	int tmp_y[] = { 0, 0, 1 };
	for (int i = 0; i < 3; i++)
		handle.fill(m_pivot_x + tmp_x[i], m_pivot_y + tmp_y[i]);
}

void Bird::clear_from_buffer(){
	FrameHandler& handle = FrameHandler::get_handler();
	int tmp_x[] = { 0, 2, 1 };
	int tmp_y[] = { 0, 0, 1 };
	for (int i = 0; i < 3; i++)
		handle.clear(m_pivot_x + tmp_x[i], m_pivot_y + tmp_y[i]);
}

Bird::Bird(int x, int y, Direction dir) : Obstacle(x, y, dir){}

Bird::~Bird(){}

/*----------------------------------Car---------------------------------------*/
void Car::draw_to_buffer(){
	FrameHandler& handle = FrameHandler::get_handler();
	int tmp_x[] = { 1, 0, 1, 2 };
	int tmp_y[] = { 1, 2, 2, 2 };
	for (int i = 0; i < 4; i++)
		handle.fill(m_pivot_x + tmp_x[i], m_pivot_y + tmp_y[i]);
}

void Car::clear_from_buffer(){
	FrameHandler& handle = FrameHandler::get_handler();
	int tmp_x[] = { 1, 0, 1, 2 };
	int tmp_y[] = { 1, 2, 2, 2 };
	for (int i = 0; i < 4; i++)
		handle.clear(m_pivot_x + tmp_x[i], m_pivot_y + tmp_y[i]);
}

Car::Car(int x, int y, Direction dir) : Obstacle(x, y, dir){}

Car::~Car(){}

/*----------------------------------Truck---------------------------------------*/
void Truck::draw_to_buffer(){
	FrameHandler& handle = FrameHandler::get_handler();
	int tmp_x[2][5] = { { 1, 2, 0, 1, 2 }, { 0, 1, 0, 1, 2 } };
	int tmp_y[2][5] = { { 1, 1, 2, 2, 2 }, { 1, 1, 2, 2, 2 } };
	int choice = (int)m_dir;
	for (int i = 0; i < 5; i++)
		handle.fill(m_pivot_x + tmp_x[choice][i], m_pivot_y + tmp_y[choice][i]);
}

void Truck::clear_from_buffer(){
	FrameHandler& handle = FrameHandler::get_handler();
	int tmp_x[2][5] = { { 1, 2, 0, 1, 2 }, { 0, 1, 0, 1, 2 } };
	int tmp_y[2][5] = { { 1, 1, 2, 2, 2 }, { 1, 1, 2, 2, 2 } };
	int choice = (int)m_dir;
	for (int i = 0; i < 5; i++)
		handle.clear(m_pivot_x + tmp_x[choice][i], m_pivot_y + tmp_y[choice][i]);
}

Truck::Truck(int x, int y, Direction dir) : Obstacle(x, y, dir){}

Truck::~Truck(){}