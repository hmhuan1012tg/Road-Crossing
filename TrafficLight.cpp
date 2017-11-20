// File "TrafficLight.cpp"

#include "TrafficLight.h"

void TrafficLight::draw_to_buffer() {
	if (m_is_green)
		FrameHandler::get_handler().fill(m_x, m_y, Symbol::Green);
	else
		FrameHandler::get_handler().fill(m_x, m_y, Symbol::Red);
	m_frame_count++;
	if (m_is_green && m_frame_count == m_green_frames) {
		m_frame_count = 0;
		m_is_green = false;
	}
	else if (!m_is_green && m_frame_count == m_red_frames) {
		m_frame_count = 0;
		m_is_green = true;
	}
}

void TrafficLight::clear_from_buffer() {
	FrameHandler::get_handler().fill(m_x, m_y, Symbol::Border);
}