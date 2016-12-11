#include "Utils.h"

float map(float val, float valMin, float valMax, float mappedMin, float mappedMax)
{
	if (val < valMin) return mappedMin;
	if (val > valMax) return mappedMax;
	return (val - valMin) * ((mappedMax - mappedMin) / (valMax - valMin)) + mappedMin;
}

int randi(int min, int max)
{
	return rand() % (max - min) + min;
}

float randfx(float min, float max)
{
	// TODO C4244: RAND_MAX is defined as SHORT_MAX on this platform giving 15 bits of int precision, which fits in a 32-bit float
	return map((float)rand(), 0, RAND_MAX, min, max);
}

float randf()
{
	return randfx(0, 1);
}