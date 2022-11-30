#include <utility/mathutility.h>

float MathUtility::RandomFloat() {
    return (float)rand() / RAND_MAX;
}

float MathUtility::Lerp(float a, float b, float step)
{
    return (float)(a * (1.0 - step) + (b * step));
}