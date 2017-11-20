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

	Direction get_dir() { return m_dir; }

	virtual Obstacle* clone() = 0;

	void move();
};

class Dinosaur : public Obstacle{
public:
	Dinosaur(int, int, Direction);
	virtual ~Dinosaur();

	virtual void draw_to_buffer() override;
	virtual void clear_from_buffer() override;

	virtual Obstacle* clone() override {
		return new Dinosaur(*this);
	}
};

class Bird : public Obstacle{
public:
	Bird(int, int, Direction);
	virtual ~Bird();

	virtual void draw_to_buffer() override;
	virtual void clear_from_buffer() override;
	
	virtual Obstacle* clone() override {
		return new Bird(*this);
	}
};

class Car : public Obstacle{
public:
	Car(int, int, Direction);
	virtual ~Car();

	virtual void draw_to_buffer() override;
	virtual void clear_from_buffer() override;

	virtual Obstacle* clone() override {
		return new Car(*this);
	}
};

class Truck : public Obstacle{
public:
	Truck(int, int, Direction);
	virtual ~Truck();

	virtual void draw_to_buffer() override;
	virtual void clear_from_buffer() override;

	virtual Obstacle* clone() override {
		return new Truck(*this);
	}
};