#ifndef SRC_VORONOISEED_H__
#define SRC_VORONOISEED_H__

#include <glm/glm.hpp>

static class VoronoiSeed
{
public:
	VoronoiSeed();
	VoronoiSeed(glm::vec2 position);
	VoronoiSeed(glm::vec2 position, glm::vec4 color);
	~VoronoiSeed();

	inline glm::vec2 GetPosition() { return m_position; }
	inline void SetPosition(glm::vec2 position) { m_position = position; }

	inline glm::vec4 GetColor() { return m_color; }
	inline void SetColor(glm::vec4 color) { m_color = color; }

	inline glm::vec2 GetVelocity() { return m_velocity; }
	inline void SetVelocity(glm::vec2 velocity) { m_velocity = velocity; }

	inline void SetMovementBounds(glm::vec2 movementBounds) { m_movementBounds = movementBounds; }

	/**
	* @brief Called once every frame
	* 
	* @param deltaTime
	* @return * Tick 
	*/
	void Tick(double deltaTime);

	void HandleMovement(double deltaTime);

private:
	glm::vec2 m_position;
	glm::vec4 m_color;

	glm::vec2 m_velocity;

	glm::vec2 m_movementBounds;
};


#endif  // SRC_VORONOISEED_H__
