// File "TrafficLight.h"

#pragma once

#include "FrameHandler.h"

class TrafficLight {
private:
	int m_x, m_y;
	bool m_is_green;

	// Number of frames past before switching to red light
	static const int MAX_LIGHT_FRAME = 500;
	static const int MIN_LIGHT_FRAME = 300;
	int m_green_frames;
	int m_red_frames;
	int m_frame_count;
public:
	TrafficLight(int x, int y) : m_x(x), m_y(y) {
		m_green_frames = rand() % (MAX_LIGHT_FRAME - MIN_LIGHT_FRAME) + MIN_LIGHT_FRAME;
		m_red_frames = m_green_frames / 3;
		m_frame_count = 0;
	}

	void draw_to_buffer();
	void clear_from_buffer();

	bool is_green() { return m_is_green; }
	bool is_red() { return !m_is_green; }
};