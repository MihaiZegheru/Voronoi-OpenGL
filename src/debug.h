#ifndef SRC_DEBUG_H__
#define SRC_DEBUG_H__

#include <string>
#include <glm/glm.hpp>

static class Debug
{
public:
	static void Log(std::string msg);
	static void Log(char* msg);
	static void Log(int msg);
	static void Log(float msg);
	static void Log(double msg);
	static void Log(glm::vec3 msg);
	static void LogError(char* msg);
	static void LogError(std::string msg);
};


#endif  // SRC_DEBUG_H__
