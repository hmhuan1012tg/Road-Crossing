//File "Obstacle.h"

#pragma once

#include "PhysicBody.h"

enum class Direction{
	Left, Right,
};

class Obstacle : public PhysicBody{
protected:
	Direction m_dir;
public:
	Obstacle(int, int, Direction);
	virtual ~Obstacle();

	void move();
};

class Dinosaur : public Obstacle{
public:
	Dinosaur(int, int, Direction);
	virtual ~Dinosaur();

	virtual void draw_to_buffer() override;
	virtual void clear_from_buffer() override;
};

class Bird : public Obstacle{
public:
	Bird(int, int, Direction);
	virtual ~Bird();

	virtual void draw_to_buffer() override;
	virtual void clear_from_buffer() override;
};

class Car : public Obstacle{
public:
	Car(int, int, Direction);
	virtual ~Car();

	virtual void draw_to_buffer() override;
	virtual void clear_from_buffer() override;
};

class Truck : public Obstacle{
public:
	Truck(int, int, Direction);
	virtual ~Truck();

	virtual void draw_to_buffer() override;
	virtual void clear_from_buffer() override;
};