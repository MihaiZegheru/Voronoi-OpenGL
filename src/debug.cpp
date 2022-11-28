#include <debug.h>

#include <iostream>


void Debug::Log(std::string msg)
{
	std::cout << "Debug::LOG: " << msg << std::endl;
}

void Debug::Log(char* msg)
{
	std::cout << "Debug::LOG: " << msg << std::endl;
}

void Debug::Log(int msg)
{
	std::cout << "Debug::LOG: " << msg << std::endl;
}

void Debug::Log(float msg)
{
	std::cout << "Debug::LOG: " << msg << std::endl;
}

void Debug::Log(double msg)
{
	std::cout << "Debug::LOG: " << msg << std::endl;
}

void Debug::Log(glm::vec3 msg)
{
	std::cout << "Debug::LOG: (" << msg.x << ", " << msg.y <<  ", " << msg.z << ")" << std::endl;
}

void Debug::LogError(char* msg)
{
	std::cout <<  "\033[1;31m" << "Debug::ERROR: " << msg << "\033[0m\n";
}

void Debug::LogError(std::string msg)
{
	std::cout << "\033[1;31m" << "Debug::ERROR: " << msg << "\033[0m\n";
}