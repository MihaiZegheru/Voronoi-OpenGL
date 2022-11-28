#include <voronoiseed.h>

VoronoiSeed::VoronoiSeed() {
	m_position = glm::vec2(0, 0);
	m_color = glm::vec4(0, 0, 0, 1);
}

VoronoiSeed::VoronoiSeed(glm::vec2 position) {
	m_position = position;
	m_color = glm::vec4(0, 0, 0, 1);
}

VoronoiSeed::VoronoiSeed(glm::vec2 position, glm::vec4 color) {
	m_position = position;
	m_color = color;
}

VoronoiSeed::~VoronoiSeed() {

}

void VoronoiSeed::Tick(float deltaTime) {

}