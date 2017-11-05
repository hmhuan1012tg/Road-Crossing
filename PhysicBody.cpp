//File "PhysicBody.cpp"

#include "PhysicBody.h"

PhysicBody::PhysicBody(int x, int y) : m_pivot_x(x), m_pivot_y(y){}

PhysicBody::~PhysicBody(){}

bool PhysicBody::collide_with(const PhysicBody& p) const{
	return abs(m_pivot_x - p.m_pivot_x) < 3 && m_pivot_y == p.m_pivot_y;
}

void PhysicBody::move_right(){
	m_pivot_x = (m_pivot_x - 1) % (MAP_WIDTH - 6) + 2;
}

void PhysicBody::move_left(){
	m_pivot_x = (m_pivot_x + MAP_WIDTH - 9) % (MAP_WIDTH - 6) + 2;
}