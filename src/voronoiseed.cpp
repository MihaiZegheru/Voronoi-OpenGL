#include <voronoiseed.h>

#include <window.h>


VoronoiSeed::VoronoiSeed() {
	m_position = glm::vec2(0, 0);
	m_color = glm::vec4(0, 0, 0, 1);
	m_velocity = glm::vec2(0);
	m_movementBounds = glm::vec2(0, 0);
}

VoronoiSeed::VoronoiSeed(glm::vec2 position) {
	m_position = position;
	m_color = glm::vec4(0, 0, 0, 1);
	m_velocity = glm::vec2(0);
	m_movementBounds = glm::vec2(0, 0);
}

VoronoiSeed::VoronoiSeed(glm::vec2 position, glm::vec4 color) {
	m_position = position;
	m_color = color;
	m_velocity = glm::vec2(0);
	m_movementBounds = glm::vec2(0, 0);
}

VoronoiSeed::~VoronoiSeed() {

}

void VoronoiSeed::Tick(double deltaTime) {
	HandleMovement(deltaTime);
}

void VoronoiSeed::HandleMovement(double deltaTime) {
	glm::vec2 newPosition = m_position + m_velocity * (float)deltaTime;

	if (0 > newPosition.x || newPosition.x > m_movementBounds.x) {
		m_velocity.x *= -1.f;
	}

	if (0 > newPosition.y || newPosition.y > m_movementBounds.y) {
		m_velocity.y *= -1.f;
	}

	m_position = newPosition;
}