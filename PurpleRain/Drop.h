#pragma once

#include "Utils.h"

struct _Drop
{
	float X;
	float Y;
	float Z;
	float Len;
	float Yspeed;
	int Color;
};

#define Drop struct _Drop
#define PDrop Drop*

void CreateDrop(PDrop d, int screenWidth, int color);
void DropFall(PDrop d, int screenHeight);
float DropGetThickness(PDrop d);