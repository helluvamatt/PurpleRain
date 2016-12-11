#pragma once

#include "Drop.h"

struct _PurpleRain
{
	Drop** Drops;
	int Count;
	int ScreenHeight;
	int ScreenWidth;
};

#define PurpleRain struct _PurpleRain
#define PPurpleRain PurpleRain*

void CreatePurpleRain(PPurpleRain obj, int count, int screenHeight, int screenWidth, int color);
void DestroyPurpleRain(PPurpleRain obj);
void AnimatePurpleRain(PPurpleRain obj);
PDrop GetDrop(PPurpleRain obj, int index);
