#ifndef SRC_MATHUTILITY_H__
#define SRC_MATHUTILITY_H__

#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace MathUtility
{
    /**
    * @brief Generate a random float between 0 and 1
    *
    * @return float
    */
    float RandomFloat();

    /**
    * @brief Lerps between two points
    *
    * @param a
    * @param b
    * @param step
    * @return float
    */
    float Lerp(float a, float b, float step);

};

#endif  // SRC_MATHUTILITY_H__